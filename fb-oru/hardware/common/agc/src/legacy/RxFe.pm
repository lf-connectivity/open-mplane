package RxFe;

require CalConfig;
require Fpga;
require PointInterp;
require axisSyslog;
use Funcs;

require MultiCarrierUtils ;
our @ISA = qw{MultiCarrierUtils};


#
use Data::Dumper ;
#

my $ln10 = log(10);

my %defCfg = (
#
    atten => 6,
    temp => 43,
    nfp => 0,

	# BZ2888 - New default values defined in Bugzilla
    slope => -0.05,
	txTemp => 33,
	femTemp => 44,
#	femSlope => -0.0133,
);

our $FEM_SLOPE_DEFAULT = -0.0133 ;
our $SLOPE_DEFAULT = -0.05 ;

our $FPGA_NUM_CG_STEPS = 6 ;


# These are expected names of the bit calibration values in the rxcal file
# The attenBitLevels array defines the minimum FE level that a particular
# attenuation bit can be used. When assigning attenuation bits to attain
# a particular attenuation the right most attenBitName will be tried first
# so the attenBitLevels array prevents that bit from being used until the
# specified FE level has been reached.  For example, on C2G5, rxAtten10Db
# will only be used once FE level 1 has been reached.  Once FE level 1 is
# reached, the rxAtten10Db will be the first to be used.

my @attenBitNames = ("rxatten0b5", "rxatten1b0", "rxatten2b0", "rxatten4b0", "rxatten8b0", "rxatten16b0");
my @attenBitLevels = (0,0,0,0,0,0);



# These are the default values of each bit in dB
my %defaultAttenBitValues = (

    rxatten0b5 => 0.5,
    rxatten1b0 => 1,
    rxatten2b0 => 2,
    rxatten4b0 => 4,
    rxatten8b0 => 8,
    rxatten16b0 => 16

);

# These are the desired relative attenuation at each blocking level

my @desiredFeAttenLevels = (0, 17);


## Set the maximum number of supported FE levels
our $FE_LEVEL_BITS = 3 ;		# Number of bits used to store the FE level
our $FE_LEVEL_MAX = (1<<$FE_LEVEL_BITS)-1 ;

## Define how the CG table address bits are used:
## 2 bits used to determine which of the 4 elements is access
## FE level is mapped next
## Top bits used for the channel number
our $CG_ADDR_ELEM_BITS = 2 ;
our $CG_ADDR_ELEM_MASK = (1<<$CG_ADDR_ELEM_BITS)-1 ;
our $CG_ADDR_ELEM_SHIFT = 0 ;
our $CG_ADDR_LEVEL_BITS = $FE_LEVEL_BITS ;
our $CG_ADDR_LEVEL_MASK = (1<<$CG_ADDR_LEVEL_BITS)-1 ;
our $CG_ADDR_LEVEL_SHIFT = $CG_ADDR_ELEM_BITS + $CG_ADDR_ELEM_SHIFT ;
our $CG_ADDR_CHAN_BITS = 2 ;
our $CG_ADDR_CHAN_MASK = (1<<$CG_ADDR_CHAN_BITS)-1 ;
our $CG_ADDR_CHAN_SHIFT = $CG_ADDR_LEVEL_BITS + $CG_ADDR_LEVEL_SHIFT ;


# Assume config does not change to avoid reading the file every time we create a new RxFe
my $calCfg;
my $freqCal;

#-------------------------------------------------------------------------------------------------------------------
# If called with gainCtl = 0 then the desired attenuation at each FE level 
# are the ones defined in the desiredFeAttenLevels array.  If called with 
# gainCtl /= 0 then the noblockatten value in the update call is added to 
# the desiredFeAttenLevels to get the desired attenuations. 
#
# NOTE: The non-blocking attenuator was only used on Lundy, where there is only a single attenuator.
# Gigha and Etna have both the RF atten and the IF atten, so do NOT use this.
#
sub new
{
    my ($class, %args) = @_;

    my $self = {
		debug => $args{debug} || 0,
		verbose => $args{verbose} || 0,
		maxChan => $args{maxChan} || 1 * $args{maxChan} || 2,
		channels => {},
		fpga => new Fpga("/dev/fpga1"),
		rxDigGain => 0,
		currentFreq => 0,
		gainCtl => $args{gainCtl} || 0,
		rxPointAdjust => 0,
		updatedMultirat => 0,
		rxifatten => [],
    };

    my $man = $args{man};

    my @conf;
    if (!defined($calCfg)) {
		$calCfg = new CalConfig("/nandflash/config/rxcal", "chan", \%defCfg, [ 1 .. $self->{maxChan} ]);
    }
    $self->{conf} = $calCfg;

#
#$self->{debug} = 1 ;
#$self->{verbose} = 1 ;
print STDERR "RxFe::new() - ", Data::Dumper->Dump([$calCfg->{conf}],[qw/config/]) ;
#

    if ($man) {
		my $resp = $man->run_cmd("get", name => "rxDigGain");
		if (!$man->ok($resp)) {
		    axisSyslog::warning("Failed to get rxDigGain");
		} else {
		    $self->{rxDigGain} = $resp->{"rxDigGain"}->[0];
		    axisSyslog::log("fetched rxDigGain=", $self->{rxDigGain}) if ($self->{verbose});
		}
    }

    $self->{man} = $man;

    ## Set up gain reduction states if they've been specified
    my %cg;
    my $global_href = $self->{conf}->getHash('GLOBAL');
    my $max_cg=-1 ;
    foreach my $global (keys %$global_href)
    {
    	if ($global =~ /cg_{0,1}(\d+)/)
    	{
    		$cg{$1} = $global_href->{$global} ;
    		if ($max_cg < $1)
    		{
    			$max_cg = $1 ;
    		}
    	}
    }
    # BZ3430 - Need to provide enough steps to fill fpga table
    my $num_cg_steps = $max_cg+1 ;
    $cg{0} ||= 0 ;
    while ($num_cg_steps < $FPGA_NUM_CG_STEPS)
    {
    	if ($num_cg_steps > 0)
    	{
    		$cg{$num_cg_steps} = $cg{$num_cg_steps-1} + 6 ;
    	} 
    	++$num_cg_steps ;
    }
    if (scalar keys %cg)
    {
    	@desiredFeAttenLevels = () ;
    	foreach my $cg_idx (sort {$a <=> $b} keys %cg)
    	{
    		push @desiredFeAttenLevels, $cg{$cg_idx} ;
    	}
    }
#
print STDERR "RxFe::new() - (num CG=$num_cg_steps) desired attens = @desiredFeAttenLevels\n";
#
    
	## BZ3077 part 2 - If parameter not present in (old) cal files then we need to add 3dB
	if (!exists($global_href->{'rattenOffset'}))
	{
		$global_href->{'rattenOffset'} = 3 ;
	}

	## BZ3077 part 2 - If offset parameter is set to something other than 0, then offset the ratten_* values
	my $ratten_offset = $global_href->{'rattenOffset'} ;
	if ($ratten_offset != 0)
	{
		for (my $chan = 1; $chan <= $self->{maxChan}; $chan++) 
		{
		    my $cal = $self->{conf}->getHash($chan);
			foreach my $chan_var (keys %$cal)
			{
				next unless $chan_var =~ /^ratten_\d+/ ;
				
	#
	print STDERR "RxFe::new() - chan $chan applying $ratten_offset dB offset to $chan_var (was $cal->{$chan_var})\n";
	#
				# apply offset
				$cal->{$chan_var} += $ratten_offset ;
			}
		}
	}

	## BZ3077 - If femSlope is not present, then also force the use of the slope default
	for (my $chan = 1; $chan <= $self->{maxChan}; $chan++) 
	{
	    my $cal = $self->{conf}->getHash($chan);

		if (!exists($cal->{'femSlope'}))
		{
			$cal->{'femSlope'} = $FEM_SLOPE_DEFAULT ;
			$cal->{'slope'} = $SLOPE_DEFAULT ;
#
print STDERR "RxFe::new() - no femSlope, setting femSlope=$FEM_SLOPE_DEFAULT and slope=$SLOPE_DEFAULT for chan $chan\n";
#
		}
	}
	
	
	

    ## If present, the various temperatures will be read in as 1 line in the 
    ## rxcal file and the values be stored in the global area.
    ## To simplify the downstream code, copy some of the useful values into the
    ## per-antenna areas
    foreach my $temp (qw/txTemp femTemp/)
    {
		for (my $chan = 1; $chan <= $self->{maxChan}; $chan++) 
		{
		    my $cal = $self->{conf}->getHash($chan);

			my $tempVar = "${temp}${chan}" ;
			if (exists($global_href->{$tempVar}) && ($global_href->{$tempVar} =~ /\d+/))
			{
				$cal->{$temp} = $global_href->{$tempVar} ;
#
print STDERR "RxFe::new() - added $tempVar = $global_href->{$tempVar} to chan $chan\n";
#
			}
		}
    }
    
    ## If the temperature line is not present, then force the slope setting to the new default
	for (my $chan = 1; $chan <= $self->{maxChan}; $chan++) 
	{
	    my $cal = $self->{conf}->getHash($chan);
			
		my $tempVar = "txTemp${chan}" ;
		if ( !exists($global_href->{$tempVar}) )
		{
	    	$cal->{'slope'} = $defCfg{'slope'} ;
#
print STDERR "RxFe::new() - chan $chan forced default slope = $cal->{'slope'} since there is no temperature line\n";
#
    	}
	}

#
print STDERR "RxFe::new() - after grabbing temp info ", Data::Dumper->Dump([$self->{conf}],[qw/config/]) ;
#



    # load frequency calibration (if not already loaded)
    if (!defined($freqCal)) 
    {
		$freqCal = {};
		for (my $chan = 1; $chan <= $self->{maxChan}; $chan++) 
		{
		    my $cal = $self->{conf}->getHash($chan);
	
			## Ensure we have an attenuator bit value per freq
		    foreach my $atten_bit (@attenBitNames)
		    {
		    	# Create a top-level value
				if (!defined($cal->{$atten_bit}))
				{
					# set the top-level default (may or may not get used in the next bit)
					$cal->{$atten_bit} = $defaultAttenBitValues{$atten_bit} ;
				    axisSyslog::log("Missing config for $atten_bit ch=$chan, using default of $cal->{$atten_bit}");
				}
				
				# Ensure we have a valye per freq
				my $num_freqs = $cal->{'nfp'} ;
				foreach my $freq (0..$num_freqs-1)
				{
					my $var = "${atten_bit}_${freq}" ;

					if (!defined($cal->{$var}))
					{
						# copy the top-level default
						$cal->{$var} = $cal->{$atten_bit} ;
					    axisSyslog::log("Missing config for $var ch=$chan, using default of $atten_bit=$cal->{$atten_bit}");
					}
				}
		    }
			 
	
			## Create interpolators
		    my $pi = new PointInterp(n => "nfp", y => "ratten_", x => "freq_", config => $cal, onlyLogMissingPoints => $args{onlyLogMissingPoints});
		    $freqCal->{$chan} = $pi;
		    foreach(@attenBitNames)
		    {
				$pi = new PointInterp(n => "nfp", y => $_ . "_", x => "freq_", config => $cal, onlyLogMissingPoints => $args{onlyLogMissingPoints});
				$freqCal->{$chan}->{$_} = $pi;
		    }
		}
    }
    $self->{fcal} = $freqCal;

    bless $self, $class;

#
print STDERR "RxFe::new() - ", Data::Dumper->Dump([$freqCal],[qw/fcal/]) ;
#

    # Initialize the rxAttenBitValues with the default values
    for (my $chan = 1; $chan <= $self->{maxChan}; $chan++) {
		$self->{channels}->{$chan}->{rxAttenBitValues} = [];
		$self->updateRxAttenBitValues($chan, 0);
		foreach(@desiredFeAttenLevels) {
		    $self->{channels}->{$chan}->{rxFeAttenLevels}->{$_} = {};
		}
    }

    return $self;
}

sub cmd_debug { return shift->{debug}; } ;

sub rxDigGain { return shift->{rxDigGain}; }
sub rxPointAdjust { return shift->{rxPointAdjust}; }
sub digitalGain { return -6 + shift->{rxDigGain}; }

#-------------------------------------------------------------------------------------------------------------------
# Return the desired attenuation for the requested FE atten level
sub getDesiredAtten
{
    my ($self, $level) = @_;

#
axisSyslog::log("getDesiredAtten(level=$level) gainCtl=$self->{gainCtl}");
#

    # Return 0 dB if FE level outside the range of programmed levels
    # NOTE: level=0 now equates to whatever the first step defined in the rxcal file is 
    return 0 if (($level < 0) || ($level > scalar(@desiredFeAttenLevels))); 

	my $desiredAtten = $desiredFeAttenLevels[$level] ;
	return $desiredAtten ;
}



#-------------------------------------------------------------------------------------------------------------------
# Return the actual attenuation for the requested FE atten level & channel
sub getAttenCal
{
    my ($self, $chan, $level) = @_;

#
axisSyslog::log("getAttenCal(chan=$chan, level=$level) gainCtl=$self->{gainCtl}");
#

    # Return 0 dB if FE level outside the range of programmed levels
    # NOTE: level=0 now equates to whatever the first step defined in the rxcal file is 
    return 0 if (($level < 0) || ($level > scalar(@desiredFeAttenLevels))); 

    if ($self->{gainCtl})
    {
		# Use the actual attenuation for the chan/level stored in a
		# manager variable during the call to update
		my $feActualAttenName = "feActualAtten_" . $chan . "_" . $level;
		my $man = $self->{man};
		if ($man) {
		    my $resp = $man->run_cmd("get", name => $feActualAttenName);
		    if ($man->ok($resp)) {
				return $resp->{$feActualAttenName}->[0];
		    }
		    else {
				axisSyslog::warning("Failed to get FE Actual Attenuation for Chan $chan - Level $level");
		    }
		} 
    }
    else
    {
#
		## Etna

	    # Use the calibrated attenuation bit values to determine the
	    # correct attenuator setting to produce the desired attenuation
	    # for each attenuation level.
	    my $attenBitValues_href = $self->{channels}->{$chan}->{rxAttenBitValues};

		my $desiredAtten = $desiredFeAttenLevels[$level] ;
	    my $attenCtl = $self->calcAttenControl($desiredAtten, $attenBitValues_href, $level);
	    my $actualAtten = $self->calcAtten($attenCtl, $attenBitValues_href, 1);
		
		# Return the actual attenuator value based on the requested level
		return $actualAtten ;
#
#
    }

    return 0;
}

#-------------------------------------------------------------------------------------------------------------------
# Return any extra attenuation for an FE atten level.  This was done as
# a patch because Samsung needed to amend the original levels from 
# 0, 10 and 20 to 0, 8 and 15 dB.
sub getChannelCal
{
    my ($self, $chan, $level) = @_;
    $level = 0 if (!$level);
    if ($level == 0) {
	return 0;
    }
    if ($level == 1) {
	return 0;
    }
    if ($level == 2) {
	return 0;
    }
    return 0;
}


#-------------------------------------------------------------------------------------------------------------------
# For the original details on RxFe attenuation see: http://twiki.axisnt.co.uk/cgi-bin/twiki/view/Engineering/SwIfRxFeAttenControl
sub update
{
    my ($self, %args) = @_;

    my $chan = $args{chan};
    my $freq = $args{freq};
    my $temp = $args{temp};
    my $hyst = $args{hyst};
    
#    my $noBlockAtten = $args{noblockatten} || 0;
#    $self->{noBlockAtten} = $noBlockAtten;

    my $gain = $args{gain};
    if (defined($gain)) {
		$self->{rxDigGain} = $gain;
    }

    my $rxPointAdjust = $args{rxPointAdjust} ;
    if (defined($rxPointAdjust)) {
		$self->{rxPointAdjust} = $rxPointAdjust;
    }

	axisSyslog::log("RxFe update : gainCtl=$self->{gainCtl} : " . join(", ", map {"$_=$args{$_}"} keys %args) ) if ($self->{verbose});
	
	## Call method to update the multicarrier module. Done here because only PCL calls this function and we 
	## only want to update the multicarrier module once
	$self->updateMultiRAT() ;
	

    # Check if the RxFe module is being used for Rx gain control
    # in addition to blocking protection, meaning that the non-blocking
    # attenuation can be other than 0.

    if ($self->{gainCtl})
    {
		# If the frequency has changed update the actual attenuation
		# values for each bit of the attenuator on this channel
		if ($freq != $self->{currentFreq})
		{
		    $self->updateRxAttenBitValues($chan, $freq);
		    $self->{currentFreq} = $freq;
		}
    }

    # Use the calibrated attenuation bit values to determine the
    # correct attenuator setting to produce the desired attenuation
    # for each attenuation level.

    my $attenBitValues = $self->{channels}->{$chan}->{rxAttenBitValues};

    # BZ 1774 the peak to average on LTE is 3db less than WiMAX so we can increase the threshold by sqroot(2) (as its voltage rather than power)
    # Use -1 dBFs as the threshold on G3 units
    #
    my $threshold = 1834 * 2 * 2;
    my $prevAdc = 8191;

    my $feAttenLevel = 0;
    my $prevActualAtten = 0;
    my $noBlockActualAtten = 0;

    # For each of the FE atten levels calculate the attenuation control
    # value to best achieve the desired level.  Then based on the actual
    # attenuation of that control value calculate the gain compensation
    # to be applied for that attenuation and the ADC threshold that
    # would cause the FE level to return to the previous level and the

    foreach(@desiredFeAttenLevels)
    {
		my %rxFeAttenLevel;
		my $desiredAtten;
		my $attenCtl;
		my $actualAtten = 0;
	
	    $desiredAtten = $_;
	    
	    # adjust desired atten by the system offset
	    # As per Trevor's doc "Etna UL Gain Control Requirements Specification", positive gain decreases the attenuation
	    $desiredAtten -= $self->{rxPointAdjust} ;
	    
		if ($self->{gainCtl})
		{
			# Note: On Etna/Gigha $noBlockAtten=0
#		    $desiredAtten += $noBlockAtten ;
		    $attenCtl = $self->calcAttenControl($desiredAtten, $attenBitValues, $feAttenLevel);
		    $actualAtten = $self->calcAtten($attenCtl, $attenBitValues, 1);

#	

		    # For FE levels, store the actual attenuation for the 
		    # chan/level in a manager variable so it can be retrieved 
		    # by getAttenCal
			
			# NOTE: Now need to save the entry for level=0 because it may not be 0dB
			my $feActualAttenName = "feActualAtten_" . $chan . "_" . $feAttenLevel;
			my $man = $self->{man};
			if ($man) {
			    my $feActualAtten = $actualAtten - $noBlockActualAtten;
			    axisSyslog::log("Chan $chan - Level $feAttenLevel ($_ dB) : Desired=$desiredAtten, Total Atten=$actualAtten, Non-Blocking Atten=$noBlockActualAtten, FE Actual Atten=$feActualAtten") if ($self->{verbose});
			    $man->run_cmd("set", $feActualAttenName => $feActualAtten);
			} 
		}
		else
		{
		    $attenCtl = $self->calcAttenControl($desiredAtten, $attenBitValues, $feAttenLevel);
		    
#
		    $actualAtten = $self->calcAtten($attenCtl, $attenBitValues, 1);
#	
#	
		}
	
		axisSyslog::log("Channel $chan - Level $feAttenLevel : desiredAtten=$desiredAtten, attenCtl=$attenCtl, actualAtten=$actualAtten (noBlockActualAtten=$noBlockActualAtten)") if ($self->{verbose});
	
		if ($feAttenLevel)
		{
			$prevAdc = int($threshold / (exp($ln10 * ($actualAtten - $prevActualAtten + $hyst) / 20))) ;
		}
		axisSyslog::log(" + Level $feAttenLevel : threshold=$threshold, actualAtten=$actualAtten, prevActualAtten=$prevActualAtten, hyst=$hyst") if ($self->{verbose});
		$prevActualAtten = $actualAtten;

		$rxFeAttenLevel{attenCtl} = $attenCtl;
		$rxFeAttenLevel{actualAtten} = $actualAtten;
		$rxFeAttenLevel{nextAdc} = int($threshold);
		$rxFeAttenLevel{prevAdc} = $prevAdc;
		$rxFeAttenLevel{gain} = sprintf("%.1f", $self->digitalGain + $actualAtten - $noBlockActualAtten);
		
		my $digGain = $self->digitalGain() ;
		axisSyslog::log(" + Level $feAttenLevel : attenCtl=$rxFeAttenLevel{attenCtl}, nextAdc=$rxFeAttenLevel{nextAdc}, prevAdc=$rxFeAttenLevel{prevAdc}, gain=$rxFeAttenLevel{gain} (dig $digGain + act $actualAtten - noblock $noBlockActualAtten)") if ($self->{verbose});
	
		$self->{channels}->{$chan}->{rxFeAttenLevels}->{$_} = \%rxFeAttenLevel;
		$feAttenLevel++;
    }
}

#-------------------------------------------------------------------------------------------------------------------
# Calculate the next IF attenuator value based on temperature
sub temperatureCompensateIfAtten
{
    my ($self, $channel) = @_;
    
	my $txTempName = "txTemp${channel}" ;
	my $femTempName = "femTemp${channel}" ;
	
	## TEMPORARY WORKAROUND: txTemp1 is showing incorrect readings due to noise in the device, so use txTemp2 instead
	$txTempName = "txTemp2" ;
    my $cal2 = $self->{conf}->getHash(2);
    my $txTempCal = $cal2->{"txTemp"} ;

	## Get manager vars	
	my @args = (name => "$txTempName", name => "$femTempName") ;
	my $getdefault = 0 ;
	$self->{rxifatten_default} ||= [] ;
	if (!$self->{rxifatten_default}[$channel])
	{
		# not already worked out midband atten, so we need get also get the values
		# for that caclulation
		$getdefault = 1 ;
		push @args, (
			name => 'highFreq',
			name => 'lowFreq',
		) ;
	}
    my $resp = $self->{man}->run_cmd("get", @args) ;
    my $ok = $self->{man}->ok($resp) ;
    if (!$ok)
    {
		axisSyslog::log("RxFe temperatureCompensateIfAtten : unable to read manager variables") ;
    	return (0, 0) ;
    }
	my $txTempCurrent = $resp->{"$txTempName"}[0] ;
	my $femTempCurrent = $resp->{"$femTempName"}[0] || 0 ;
    
#
print STDERR "RxFe::temperatureCompensateIfAtten() - ", Data::Dumper->Dump([\@args, $resp],[qw/@args $resp/]) ;
#


	## Default attenuation is midband cal value	
	my $default_atten = 0 ;
	if ($getdefault)
	{
		my $high = $resp->{'highFreq'}[0] || 2370000 ;
		my $low = $resp->{'lowFreq'}[0]   || 2320000 ;
		my $midband_freq =  ($high - $low) / 2  + $low ;
	
		$default_atten = $self->getFreqAttenOffset($channel, $midband_freq) ;
		
		# save for next time
		$self->{rxifatten_default}[$channel] = $default_atten ;
	}	
	else
	{
		# use pre-calculated value
		$default_atten = $self->{rxifatten_default}[$channel] ;
	}
	
	
	## Calc temperature compensated value
    if (!defined($txTempCurrent))
    {
		axisSyslog::log("RxFe temperatureCompensateIfAtten : unable to read $txTempName") ;
    	return (0, 0) ;
    }
    my $cal = $self->{conf}->getHash($channel);
    my $slope = $cal->{"slope"} ;
#    my $txTempCal = $cal->{"txTemp"} ;	# TEMPORARY WORKAROUND: see above
    my $femSlope = $cal->{"femSlope"} ;
    my $femTempCal = $cal->{"femTemp"} ;
    
    ## From BZ2888: IFatten1 = IFatten1(calfile) + slope1 * (txTemp1current-txTemp1cal) + FEMslope1 * (femTemp1current-femTemp1cal)
    my $ifatten_float = $default_atten ;
    $ifatten_float += $slope * ($txTempCurrent - $txTempCal) ;
    $ifatten_float += $femSlope * ($femTempCurrent - $femTempCal) ; # optional: used if FEM slope not 0
    
    my $ifatten =  sprintf("%.3f", $ifatten_float);

	## check for change    
	my $changed = 0 ;
	if (!defined($self->{rxifatten}[$channel]) || "$self->{rxifatten}[$channel]" ne "$ifatten")
	{
		$changed = 1 ;
	}
    
	axisSyslog::log("RxFe temperatureCompensateIfAtten : chan=$channel rx if atten $self->{rxifatten}[$channel] => $ifatten : midband=$default_atten : tx temp=$txTempCurrent, slope=$slope, tx cal temp=$txTempCal : fem temp=$femTempCurrent, fem slope=$femSlope, fem cal temp=$femTempCal ") ;# if ($self->{verbose});
	$self->{rxifatten}[$channel] = "$ifatten" ;

	return ($ifatten, $changed) ;
}

#-------------------------------------------------------------------------------------------------------------------
# Dump the contents of the channel hash which is all the programming
# controls for all the channels
sub dump
{
    my ($self, $channels) = @_;

    $channels = $self->{channels} if (!defined($channels));
    for my $c (1 .. $self->{maxChan}) {
		for my $k (sort {$a <=> $b} (keys(%{$channels->{$c}->{rxFeAttenLevels}}))) {
		    axisSyslog::log("$c-$k: ", join(", ", map { "$_=$channels->{$c}->{rxFeAttenLevels}->{$k}->{$_}" } sort(keys(%{$channels->{$c}->{rxFeAttenLevels}->{$k}}))));
		}
    }
}

#-------------------------------------------------------------------------------------------------------------------
# return the atten offset based on the frequency
#
sub getFreqAttenOffset
{
    my ($self, $chan, $freq) = (@_);

#
print STDERR "RxFe::getFreqAttenOffset(chan=$chan, freq=$freq)\n" ;
#


    my $cal = $self->{fcal}->{$chan};
    return 0 if (!defined($cal));

    my $offset = $cal->interp($freq);
    $offset = 0 if (!defined($offset));
    axisSyslog::log("getFreqAttenOffset chan=$chan, freq=$freq, offset=$offset") if ($self->{verbose});
    return defined($offset) ? $offset : 0;
}

#-------------------------------------------------------------------------------------------------------------------
sub getCal
{
    my ($self, $chan) = @_;

    return $self->{conf}->getHash($chan);
}

#-------------------------------------------------------------------------------------------------------------------
# Write the contents of the channel hash into the FPGA.  See the
# FPGA SW interface documentation on the Twiki for details
sub updateFpga
{
    my ($self, $man) = @_;

    #axisSyslog::log("RxFe updateFpga") ;

    $self->{fpga}->write(0x0490, 0x0080, 0x00);
#   $man->run_cmd("set", "RxFeTableUpdate" => 0);
    for my $c (1 .. $self->{maxChan}) 
    {
		my $feAttenLevel = 0;
		foreach(sort {$a <=> $b} (keys(%{$self->{channels}->{$c}->{rxFeAttenLevels}}))) 
		{
			my $addr = $self->cg_addr($c, $feAttenLevel) ;
	
		    my $d = $self->{channels}->{$c}->{rxFeAttenLevels}->{$_};
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 0);
		    $self->{fpga}->write(0x04ac, 0xffff, $d->{attenCtl});
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 1);
		    $self->{fpga}->write(0x04ac, 0xffff, $d->{nextAdc});
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 2);
		    $self->{fpga}->write(0x04ac, 0xffff, $d->{prevAdc});
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 3);
		    $self->{fpga}->write(0x04ac, 0xffff, int($d->{gain} * 10));
	
	#
	my $int_gain = int($d->{gain} * 10) ;
	printf STDERR "RxFe::updateFpga : chan=$c, level=$_, addr=0x%08x : attenctl=$d->{attenCtl}, gain=$d->{gain} int=$int_gain (0x%04x), prevAdc=$d->{prevAdc}, nextAdc=$d->{nextAdc}\n", $addr, $int_gain ;
	#
	
		    $feAttenLevel++;
		    
		    ## Don't attempt to write too many levels
		    last if $feAttenLevel > $FE_LEVEL_MAX ;
	
		}
    }
    if (defined($self->{channels})) {
    axisSyslog::log("setting rxfe update bit") if ($self->{verbose});
    $self->{fpga}->write(0x0490, 0x0080, 0x80);
    $self->{fpga}->write(0x0490, 0x0080, 0x00);
    }

#    $man->run_cmd("set", "RxFeTableUpdate" => 1);
#    $man->run_cmd("set", "RxFeTableUpdate" => 0);

}

#-------------------------------------------------------------------------------------------------------------------
# Read the FE attenuation memory in the FPGA and write it
# into the channels hash
sub readFpga
{
    my ($self) = @_;

    $self->{fpga}->write(0x0490, 0x0080, 0x00);
    my %channels;
    for my $c (1 .. $self->{maxChan}) 
    {
		$channels{$c} = {};
		my $feAttenLevel = 0;
		foreach(sort {$a <=> $b} (keys(%{$self->{channels}->{$c}->{rxFeAttenLevels}}))) 
		{
			my $addr = $self->cg_addr($c, $feAttenLevel) ;
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 0);
		    my $attenCtl = $self->{fpga}->read(0x04ac, 0xffff);
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 1);
		    my $nextAdc = $self->{fpga}->read(0x04ac, 0xffff);
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 2);
		    my $prevAdc = $self->{fpga}->read(0x04ac, 0xffff);
	
		    $self->{fpga}->write(0x04aa, 0xffff, $addr | 3);
		    my $gain = $self->{fpga}->read(0x04ac, 0xffff);
		    # Gain min is 0x1fff; max is 0x0fff
		    if ($gain & 0x1000)
		    {
		    	# convert to -ve int
		    	$gain -= 0x2000 ;
		    }
		    # convert to dB
		    $gain = 1.0 * $gain / 10.0 ;
		    
		    my %d = (
				attenCtl => $attenCtl,
				nextAdc => $nextAdc,
				prevAdc => $prevAdc,
				gain => $gain
		    );
		    $channels{$c}->{rxFeAttenLevels}->{$_} = \%d;
		    $feAttenLevel++;

		    ## Don't attempt to read too many levels
		    last if $feAttenLevel > $FE_LEVEL_MAX ;
		}
    }
    return \%channels;
}

#-------------------------------------------------------------------------------------------------------------------
sub calcRssi
{
    my ($self, $ant, $fe, $adc, $rssi, $dpd) = @_;

    my $wideRssi = $adc > 0 ? 10 * log10($adc / 0x4000000) : -200;

	# for debug
	my $wide_eqn = "wide=$wideRssi" ;
	my $chan_eqn = "" ;

    my $chanRssi;
    if ($dpd) {
		$chanRssi = -200;
		$chan_eqn = "chan=$chanRssi" ;
    } else {
		my $extraChanAtten = $self->getChannelCal($ant, $fe);
		my $featten = $self->getAttenCal($ant, $fe);
		my $ddcGain = 8.6;
		my $rfAdcGain = 41;
		my $digGain = $self->rxDigGain ;
		my $desiredAtten0 = $self->getDesiredAtten(0) ;
		
		my $rxifattenOffset = 0 ;
		my $man = $self->{man};
		if ($man) 
		{
		    my $resp = $man->run_cmd("get", name => "RxIfAttenOffset${ant}");
		    if ($man->ok($resp)) 
		    {
				$rxifattenOffset = $resp->{"RxIfAttenOffset${ant}"}[0] ;
		    }
		    else 
		    {
				axisSyslog::warning("Failed to get RxIfAttenOffset for Chan $ant");
		    }
		}
		else
		{
			axisSyslog::warning("Unable to read RxIfAttenOffset for Chan $ant (no manager set)");
		}
		
	
		## Wide
		
		# for debug
		my $orig_wideRssi = $wideRssi ;
	
		$wideRssi -= $rfAdcGain;	# Remove nominal RF to ADC gain
		$wideRssi -= $rxifattenOffset ; # Remove offset between requested IF atten and actual
		$wideRssi += $featten;		# Put in the featten value
		
		$wideRssi -= $desiredAtten0 ; # remove the baseline atten that we cal to 
		$wideRssi += 3;             # Correct for peak v RMS (BZ3077 part 1)
		
		# for debug
		$wide_eqn = "adc=$adc ($orig_wideRssi - rfadc $rfAdcGain - IF offset $rxifattenOffset + feAtten $featten - rxcal[0] $desiredAtten0) +3" ;
	
		## Chan
		
	    $chanRssi = $rssi > 0 ? 10 * log10($rssi / 0x4000000) : 0;

		# for debug	
		my $orig_chanRssi = $chanRssi ;
	
		$chanRssi -= $ddcGain;		# Remove DDC gain
		$chanRssi -= $rfAdcGain;	# Remove nominal RF to ADC gain
		$chanRssi -= $rxifattenOffset ; # Remove offset between requested IF atten and actual
		$chanRssi += $featten;      # Put in the featten value (BZ2984)
		$chanRssi -= $desiredAtten0 ; # remove the baseline atten that we cal to 
		$chanRssi -= 6;             # Correct for the 6dB digital gain that gets applied after the channel RSSI measurement point (BZ2984)
		$chanRssi += 3;             # Correct for peak v RMS (BZ3077 part 1)

		$chanRssi += $extraChanAtten;
		
		# for debug
		$chan_eqn = "($orig_chanRssi - ddc $ddcGain - rfadc $rfAdcGain - IF offset $rxifattenOffset + featten $featten  - rxcal[0] $desiredAtten0 + extra $extraChanAtten -6 +3)" ;
    
    	## Debug to determine correct RSSI measure for Etna
	    axisSyslog::log("calcRssi(ant=$ant, fe=$fe, adc=$adc, rssi=$rssi) ",
	    	"wide=$wideRssi $wide_eqn ",
	    	"chan=$chanRssi $chan_eqn") ;
    }

    return ($wideRssi, $chanRssi, $wide_eqn, $chan_eqn);
}

#-------------------------------------------------------------------------------------------------------------------
# Calculate the control bits for a stepped attenuator based
# on the desired attenuation and the calibrated value of
# each of the bits
sub calcAttenControl
{
    my ($self, $desiredAtten, $attenBitValues, $feLevel) = @_;
    
    # Attenuation bit values are passed by reference
    my @attenBitValues = @{$attenBitValues};
    my $attenBits = scalar(@attenBitValues);

    # Find the highest attenuation control that does not exceed
    # the desired attenuation
    my $attenControl = 0;
    my $calculatedAtten = 0;
    
    for (my $attenBit = $attenBits - 1 ; $attenBit >= 0 ; $attenBit--)
    {
		# Find largest atten value to add in
		my $attenBitValue = $attenBitValues[$attenBit];
		if ((($calculatedAtten + $attenBitValue) < $desiredAtten) &&
		     ($attenBitLevels[$attenBit] <= $feLevel))
		{
		    $attenControl += (1 << $attenBit);
		    $calculatedAtten += $attenBitValue;
		    axisSyslog::log("Adding in bit $attenBit, total atten = $calculatedAtten") if $self->{debug};
		}
    }

    # Check to see whether the atten control found or the next step
    # up is closer to the desired attenuation, then return
    # 2**bits - chosen value because each atten bit is active low.
    my $maxAttenControl = (1 << $attenBits) - 1;
    my $lowSideDiff = $desiredAtten - $calculatedAtten;
    if ($attenControl < $maxAttenControl)
    {
		my $nextAttenControl = $attenControl + 1;
		my $highSideDiff = 
		    $self->calcAtten($nextAttenControl, $attenBitValues) - $desiredAtten;
		axisSyslog::log("lowAtten = $attenControl, highAtten = $nextAttenControl") if $self->{debug};
		axisSyslog::log("lowSideDiff = $lowSideDiff, highSideDiff = $highSideDiff") if $self->{debug};
		if ($highSideDiff < $lowSideDiff)
		{
		    return($maxAttenControl - $nextAttenControl);
		}
		else
		{
		    return($maxAttenControl - $attenControl);
		}
    }
    else
    {
		return($maxAttenControl - $attenControl);
    }
} 

#-------------------------------------------------------------------------------------------------------------------
# Calculate the actual attenuation for a stepped attenuator based
# on the control value and the calibrated value of each of the bits
# and whether or not the bits have already been inverted or not because
# the attenuation control for each bit of the real attenuator is active low.
sub calcAtten
{
    my ($self, $attenControl, $attenBitValues, $bitsInverted) = @_;

    # Attenuation bit values are passed by reference
    my @attenBitValues = @{$attenBitValues};
    my $attenBits = scalar(@attenBitValues);
    $attenControl = (1 << $attenBits) - 1 - $attenControl if ($bitsInverted);
    my $calculatedAtten = 0;
    for (my $attenBit = 0 ; $attenBit < $attenBits ; $attenBit++)
    {
		if ($attenControl & (1 << $attenBit))
		{
		    $calculatedAtten += $attenBitValues[$attenBit];
		    axisSyslog::log("Adding in bit $attenBit, total atten = $calculatedAtten") if $self->{debug};
		}
    }

    return($calculatedAtten);
}

#-------------------------------------------------------------------------------------------------------------------
sub updateRxAttenBitValues
{
    my ($self, $chan, $freq) = @_;

    # Retrive the calibrated atten  bit values vs. the 
    # new frequency and store them away for future use.  
    # If no cal information exists use the default atten 
    # bit values.  
 
    my @rxAttenBitValues;
    foreach(@attenBitNames)
    {
	my $cal = $self->{fcal}->{$chan}->{$_};
	if (!defined($cal))
	{
	    push(@rxAttenBitValues, $defaultAttenBitValues{$_});
	    next;
	}
	my $attenBitValue = $cal->interp($freq);
	if (!defined($attenBitValue))
	{
	    push(@rxAttenBitValues, $defaultAttenBitValues{$_});
	    next;
	}
	push(@rxAttenBitValues, $attenBitValue); 
    }
    axisSyslog::log("RxFe : Atten Bit Values for Chan $chan = @rxAttenBitValues") if $self->{verbose};

    # Store the new attenuation bit values by reference
    $self->{channels}->{$chan}->{rxAttenBitValues} = \@rxAttenBitValues;
}

#-------------------------------------------------------------------------------------------------------------------
sub updateMultiRAT
{
    my ($self) = @_;
    
    # skip if already updated
    return if $self->{updatedMultirat} ;

    $self->{updatedMultirat} = 1 ;

    axisSyslog::log("RxFe : Updated MultiRAT table") ;

	## Send the rxcal tables to the multi-carrier module
    for (my $chan = 1; $chan <= $self->{maxChan}; $chan++) 
    {
	    my $cal = $self->{fcal}->{$chan};
	    next if (!defined($cal));
	    
	    # get the PointInterp values in a format ready for sending to the multi-carrier code
	    my %rxcal_hash = $cal->to_hash('num' => 'num', 'x' => 'freqs', 'y' => 'attens') ;
	    
	    # send it
		my ($ok, $resp) = $self->send_multirat_cmd('rxcal', 
			'ant'		=> $chan,
			%rxcal_hash,
		) ;
    }
	
}

#-------------------------------------------------------------------------------------------------------------------
sub cg_addr
{
	my ($self, $chan, $feAttenLevel) = @_ ;

    my $chan_addr = (($chan - 1) & $CG_ADDR_CHAN_MASK) << $CG_ADDR_CHAN_SHIFT ;
    my $level_addr = ($feAttenLevel & $CG_ADDR_LEVEL_MASK) << $CG_ADDR_LEVEL_SHIFT ;
    my $addr = $chan_addr | $level_addr;

	return $addr ;	
}


1;
