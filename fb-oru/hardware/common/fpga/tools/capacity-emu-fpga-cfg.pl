#!/usr/bin/perl -w
#
# Create off-target fpga settings
#

use warnings;
use strict;

use Data::Dumper;
use Getopt::Long;
use Pod::Usage ;

	our $VERSION = "1.01" ;

	my $debug = 0;
	my $verbose = 0;
	my $help ;
	my $man ;

	my $capacityFile ;

	my $options = "" ;

	GetOptions(
		"debug=i" 		=> \$debug,
		"verbose=i" 	=> \$verbose,
		'man' 			=> \$man,

		'capacity=s'	=> \$capacityFile,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;
    pod2usage("$0: No arguments given.")  if (@ARGV == 0) ;

	## Read the capacity file
	my %info ;
	readCapacityFile($capacityFile, \%info) ;
	checkCapacityFile(\%info) ;

	if ($debug)
	{
		print Data::Dumper->Dump([\%info], [qw/%info/]) ;
	}

	## Create new config file
	createCfgFile($ARGV[0], \%info) ;


	exit 0 ;




#---------------------------------------------------------------------------------------------------------------
sub readCapacityFile
{
	my ($capacityFile, $info_href) = @_ ;

	open my $fh, "<$capacityFile" or die "Unable to read capacity file $capacityFile: $!" ;
	my $line ;
	my $fibre ;
	my ($chain_uldl, $chain) ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		print "<$line>\n" if $debug ;

		# Process fibre
		if (defined($fibre))
		{
			print "* * Process fibre $fibre\n" if $debug ;

			if ($line =~ /^\s*([^\.]+)[\.]+:\s*(\d+)/)
			{
				print "* * * $1 = $2\n" if $debug ;
				$info_href->{'fibres'}{$fibre}{$1} = $2 ;
				next ;
			}
		}

		# Process chain
		if (defined($chain))
		{
		#	  Type.................: 11
		#	  Num Streams..........: 12
		#	  Start IQ.............: 0
		#	  End IQ...............: 11
		#	  IQ 0 Antenna......: 0

			print "* * Process $chain_uldl chain $chain\n" if $debug ;

			if ($line =~ /^\s*IQ\s*(\d+)\s+Antenna[\.]+:\s*(\d+)/)
			{
				my ($iq, $ant) = ($1, $2) ;
				print "* * * ANT $1 = $2\n" if $debug ;
				$info_href->{'chains'}{$chain_uldl}{$chain}{'antennas'}{$iq} = $ant ;
				next ;
			}

			if ($line =~ /^\s*([^\.]+)[\.]+:\s*(\d+)/)
			{
				$info_href->{'chains'}{$chain_uldl}{$chain}{$1} = $2 ;
				print "* * * $1 = $2\n" if $debug ;
				next ;
			}
		}

		#	Num Fibres.............: 2
		#	Num TX Ant.............: 2
		#	Num RX Ant.............: 2
		#	Num DL Carriers........: 14
		#	Num UL Carriers........: 14
		#	Num DL Chains..........: 2
		#	Num UL Chains..........: 2
		#	Fibre 0
		#	  DL Streams...........: 6
		#	  DL Start IQ..........: 0
		#	  UL Streams...........: 6
		#	  UL Start IQ..........: 0
		#	Fibre 1
		#	  DL Streams...........: 8
		#	  DL Start IQ..........: 6
		#	  UL Streams...........: 8
		#	  UL Start IQ..........: 6
		#	UL Chain 0
		#	  Type.................: 11
		#	  Num Streams..........: 12
		#	  Start IQ.............: 0
		#	  End IQ...............: 11
		#	  IQ 0 Antenna......: 0
		#	  IQ 1 Antenna......: 1
		#	  IQ 2 Antenna......: 0
		#	  IQ 3 Antenna......: 1
		#	  IQ 4 Antenna......: 0
		#	  IQ 5 Antenna......: 1
		#	  IQ 6 Antenna......: 0
		#	  IQ 7 Antenna......: 1
		#	  IQ 8 Antenna......: 0
		#	  IQ 9 Antenna......: 1
		#	  IQ 10 Antenna......: 0
		#	  IQ 11 Antenna......: 1
		#	UL Chain 1
		#	  Type.................: 4
		#	  Num Streams..........: 2
		#	  Start IQ.............: 12
		#	  End IQ...............: 13
		#	  IQ 12 Antenna......: 0
		#	  IQ 13 Antenna......: 1
		#	DL Chain 0
		#	  Type.................: 11
		#	  Num Streams..........: 12
		#	  Start IQ.............: 0
		#	  End IQ...............: 11
		#	  IQ 0 Antenna......: 0
		#	  IQ 1 Antenna......: 1
		#	  IQ 2 Antenna......: 0
		#	  IQ 3 Antenna......: 1
		#	  IQ 4 Antenna......: 0
		#	  IQ 5 Antenna......: 1
		#	  IQ 6 Antenna......: 0
		#	  IQ 7 Antenna......: 1
		#	  IQ 8 Antenna......: 0
		#	  IQ 9 Antenna......: 1
		#	  IQ 10 Antenna......: 0
		#	  IQ 11 Antenna......: 1
		#	DL Chain 1
		#	  Type.................: 4
		#	  Num Streams..........: 2
		#	  Start IQ.............: 12
		#	  End IQ...............: 13
		#	  IQ 12 Antenna......: 0
		#	  IQ 13 Antenna......: 1

		if ($line =~ /^\s*Num ([^\.]+)[\.]+:\s*(\d+)/)
		{
			print "* NUM $1\n" if $debug ;

			$fibre = undef ;
			$chain = undef ;
			$chain_uldl = undef ;

			$info_href->{'num'} ||= {} ;
			$info_href->{'num'}{$1} = $2 ;
			next ;
		}

		if ($line =~ /^\s*Fibre\s*(\d+)/)
		{
			$fibre = $1 ;

			print "* FIBRE $fibre\n" if $debug ;

			$info_href->{'fibres'} ||= {} ;
			$info_href->{'fibres'}{$fibre} = {
			  'DL Streams' => undef,
			  'DL Start IQ' => undef,
			  'UL Streams' => undef,
			  'UL Start IQ' => undef,
			} ;
			$chain = undef ;
			$chain_uldl = undef ;
			next ;
		}

		if ($line =~ /^\s*(UL|DL)\s+Chain\s*(\d+)/)
		{
			$chain = $2 ;
			$chain_uldl = $1 ;

			print "* $chain_uldl CHAIN $chain\n" if $debug ;

			$info_href->{'chains'} ||= {} ;
			$info_href->{'chains'}{$chain_uldl} ||= {} ;
			$info_href->{'chains'}{$chain_uldl}{$chain} = {
			  'Type' => undef,
			  'Num Streams' => undef,
			  'Start IQ' => undef,
			  'End IQ' => undef,
			  'antennas' => {}
			} ;
			$fibre = undef ;
			next ;
		}

		# no match
		print "!RESET\n" if $debug ;
		$fibre = undef ;
		$chain = undef ;
		$chain_uldl = undef ;

	}
	close $fh ;
}

#---------------------------------------------------------------------------------------------------------------
sub checkCapacityFile
{
	my ($info_href) = @_ ;

	### Checks for missing information

	# Fix any missing 'End IQ'

		#           'chains' => {
		#                         'UL' => {
		#                                   '1' => {
		#                                            'antennas' => {
		#                                                            '13' => '1',
		#                                                            '12' => '0'
		#                                                          },
		#                                            'Start IQ' => '12',
		#                                            'Type' => '4',
		#                                            'Num Streams' => '2',
		#                                            'End IQ' => '13'
		#                                          },

	foreach my $uldl ('UL', 'DL')
	{
		foreach my $chain (keys %{$info_href->{'chains'}{$uldl}})
		{
			if (!defined($info_href->{'chains'}{$uldl}{$chain}{'End IQ'}))
			{
				$info_href->{'chains'}{$uldl}{$chain}{'End IQ'} =
					$info_href->{'chains'}{$uldl}{$chain}{'Start IQ'} +
					$info_href->{'chains'}{$uldl}{$chain}{'Num Streams'} -
					1 ;
			}
		}
	}

	# Fix any missing 'antennas'
	foreach my $uldl ('UL', 'DL')
	{
		my $ant = 0 ;
		foreach my $chain (sort {$a <=> $b} keys %{$info_href->{'chains'}{$uldl}})
		{
			if (scalar(keys %{$info_href->{'chains'}{$uldl}{$chain}{'antennas'}}) == 0)
			{
				for (my $iq=$info_href->{'chains'}{$uldl}{$chain}{'Start IQ'}; $iq <= $info_href->{'chains'}{$uldl}{$chain}{'End IQ'}; ++$iq)
				{
					$info_href->{'chains'}{$uldl}{$chain}{'antennas'}{$iq} = $ant ;
					$ant = $ant==0 ? 1 : 0 ;
				}
			}
		}
	}


}

#---------------------------------------------------------------------------------------------------------------
sub createCfgFile
{
	my ($outfile, $info_href) = @_ ;

	#	$%info = {
	#	           'num' => {
	#	                      'DL Carriers' => '14',
	#	                      'Fibres' => '2',
	#	                      'TX Ant' => '2',
	#	                      'DL Chains' => '2',
	#	                      'UL Chains' => '2',
	#	                      'UL Carriers' => '14',
	#	                      'RX Ant' => '2'
	#	                    },

	my $fibres = $info_href->{'num'}{'Fibres'} ;
	my $dlchains = $info_href->{'num'}{'DL Chains'} ;
	my $ulchains = $info_href->{'num'}{'UL Chains'} ;
	my $dlcarriers = $info_href->{'num'}{'DL Carriers'} ;
	my $ulcarriers = $info_href->{'num'}{'UL Carriers'} ;
	my $txants = $info_href->{'num'}{'TX Ant'} ;
	my $rxants = $info_href->{'num'}{'RX Ant'} ;

	my $carriers = $dlcarriers + $ulcarriers ;
	my $antennas = $txants > $rxants ? $txants : $rxants ;
	my $max_chains = $dlchains > $ulchains ? $dlchains : $ulchains ;

	open my $fh, ">$outfile" or die "Error: cannot write to file $outfile : $!" ;

	## Start
	print $fh <<HEAD ;
## Created by capacity-emu-fpga-cfg v$VERSION
##
## Default values to be loaded into FPGA emulator
##
## Value lines can be of the form:
##
##     address=0xXXXX value=0xXXXX
##
## or
##
##     <regname>=0xXXXX
##
## Also, the register name form can contain wildcards to set a block of same named registers
##
## Example, the following are equivalent:
##
##  StreamMask0 = 0x00ff
##  address=0x60000 value=0x00ff
##
## To set all StreamMaskN regs:
##
##  StreamMask. = 0x00ff
##

# Set fpga version register
address=0x0100 value=0x0001

#emu.log = log/fpga-emu.log
emu.debug = 0
emu.names = ../../../common/fpga/cfg/etna-regs.cfg

## Mod abs
address=0x40300 value=0x0000
address=0x41300 value=0x0000
#field=sfpModAbs[0] value=1
#field=sfpModAbs[1] value=1

# MSK demod sizes
address=0x50396 value=0x2
address=0x51396 value=0x2

# Status & SPI done
address=0x2 value=0x0180
address=0x4 value=0x0180

# FPGA features
field=Feature_NumBits value=18

field=Feature_RSSI_V2 value=1
field=Feature_DPD_V2_BIGMEM value=1
field=Feature_RAW_CPRI_IQ_Mapping value=0
field=Feature_DpdAdcAlarm value=1

field=Feature_dualBandRxVco value=1
field=Feature_DdcOutIqInvertEarly value=1
field=Feature_DdcOutIqInvertLate value=0
field=Feature_PowerMeasurementV2 value=1

field=Feature_Chbw3Bit value=1
field=Feature_BbPwrProgAlpha value=1
field=Feature_VLANTagging value=1
field=Feature_StaticDaisyChain value=1

field=Feature_ProgrammableCfrFinalClip value=1
field=Feature_CdcDelayBarrelShift value=1
field=Feature_CordicBasedRssi value=0
field=Feature_BbFiltersAmplitude value=1

field=Feature_CFR_Xilinx value=1
field=Feature_CPRI10GbpsCapable value=1

# Sizes
field=FpgaFibres value=$fibres
field=FpgaTxAntennas value=$txants
field=FpgaRxAntennas value=$rxants
field=FpgaDlCarriers value=$dlcarriers
field=FpgaUlCarriers value=$ulcarriers
field=NumDlRfChains value=$dlchains
field=NumUlRfChains value=$ulchains
field=DlTunerClocksPerSample value=8
field=UlTunerClocksPerSample value=8
field=dlTunerNcoBits value=24
field=ulTunerNcoBits value=24

## Waveforms
field=masterPlaybackEnable=0
field=masterCaptureEnable=0
field=dpdadcCaptureDone value=1
field=dpdadcCaptureDepth value=2

field=waveformModulePresent[0] value=1
field=waveformModulePresent[1] value=1
field=waveformModulePresent[2] value=0
field=waveformModulePresent[3] value=0
field=waveformModulePresent[4] value=1
field=waveformModulePresent[5] value=1
field=waveformModulePresent[6] value=0
field=waveformModulePresent[7] value=0
field=waveformModulePresent[8] value=1
field=waveformModulePresent[9] value=1
field=waveformModulePresent[10] value=1
field=waveformModulePresent[11] value=1
field=waveformModulePresent[12] value=0
field=waveformModulePresent[13] value=0
field=waveformModulePresent[14] value=0
field=waveformModulePresent[15] value=0
field=waveformModulePresent[16] value=1
field=waveformModulePresent[17] value=1
field=waveformModulePresent[18] value=0
field=waveformModulePresent[19] value=0
field=waveformModulePresent[20] value=1
field=waveformModulePresent[21] value=1

field=waveformModuleType[0] value=1
field=waveformModuleType[1] value=1
field=waveformModuleType[2] value=0
field=waveformModuleType[3] value=0
field=waveformModuleType[4] value=1
field=waveformModuleType[5] value=1
field=waveformModuleType[6] value=0
field=waveformModuleType[7] value=0
field=waveformModuleType[8] value=1
field=waveformModuleType[9] value=1
field=waveformModuleType[10] value=0
field=waveformModuleType[11] value=0
field=waveformModuleType[12] value=1
field=waveformModuleType[13] value=1
field=waveformModuleType[14] value=0
field=waveformModuleType[15] value=0
field=waveformModuleType[16] value=1
field=waveformModuleType[17] value=1
field=waveformModuleType[18] value=0
field=waveformModuleType[19] value=0
field=waveformModuleType[20] value=1
field=waveformModuleType[21] value=1

HEAD


	## OUTPUT ###################################################

	## Antennas

	print $fh "## Antennas\n\n" ;
	for (my $ant = 0; $ant < $antennas; ++$ant)
	{
		my $antdelay = 0x1234 + 11*$ant ;
		print $fh "# Ant $ant\n" ;
		print $fh <<ANT ;
field=antennaProcDelay[${ant}] value=$antdelay
ANT
	}

	## Fibres
	#           'fibres' => {
	#                         '0' => {
	#                                  'DL Streams' => '6',
	#                                  'DL Start IQ' => '0',
	#                                  'UL Start IQ' => '0',
	#                                  'UL Streams' => '6'
	#                                }
	#                       }

	print $fh "## Fibres\n\n" ;
	for (my $fibre = 0; $fibre < $fibres; ++$fibre)
	{
		my $dl_fibre_iqstreams = $info_href->{'fibres'}{$fibre}{'DL Streams'} ;
		my $ul_fibre_iqstreams = $info_href->{'fibres'}{$fibre}{'UL Streams'} ;


		my $addr = sprintf "0x%05x", 0x40030 + $fibre*0x01000 ;
		my $addr_cpri = sprintf "0x%05x", 0x4020c + $fibre*0x01000 ;

		# 18 bits
		my $r21 = 15580 + 2000*$fibre ;

		# 14 bit
		my $fifo = 0x3321 + 2*$fibre ;

		# 5 bit
		my $barrel = 0x13 + $fibre ;

		# 0..384399
		my $framediff = 384399 - 3 * $fibre ;

		# 0..384399
		my $framediffadj = 384380 - 5 * $fibre ;

		print $fh "# Fibre $fibre\n" ;
		print $fh <<FIBRE ;
field=dlFibreIqStreams[${fibre}] value=$dl_fibre_iqstreams
field=ulFibreIqStreams[${fibre}] value=$ul_fibre_iqstreams

# OBSAI Fibre status register
#
#0x30 	Sfp_Los 	0 	R 	Asserted when there is no received optical signal detected.
#0x30 	Los_Defect 	1 	R 	Asserted when receiver cannot decode valid data bytes.
#0x30 	Mframe_Sync 	2 	R 	Asserted when RP3 frame timing has been recovered.
#0x30 	Tx_Sync 	3 	R 	Asserted when the transmitter state machine reached the FRAME_TX state.
#0x30 	Sync_Status 	7..4 	R 	Indicates the receiver state. 0x8=>UNSYNC, 0x4=>WAIT_FOR_K28.7_IDLES, 0x2=>WAIT_FOR_FRAME_SYNC_T, 0x1=>FRAME_SYNC.
#0x30 	An_Status 	10..8 	R 	Indicates the result of auto-negotiation process. 000=>0.768, 001=>1.536, 010=>3.072, 100=>6.144, 111=>Failed.
#0x30 	An_Complete 	11 	R 	Asserted when auto-negotiation process has completed.
#0x30 	Sync_Stat_Change 	12 	R 	Not used.
#
# States
#
# An_Comlpete  An_Status  Sync_Status  Tx_Sync  Mframe_Sync  Los_Defect  Sfp_Los
# 11           10..8      7..4         3        2            1           0
# -----------------------------------------------------------------------------------
# 0            111        1000         0        0            1           1        Disconnected						0x0783
# 0            111        1000         0        0            1           0        Connected							0x0782
# 0            111        1000         0        0            0           0        Connected	UNSYNC					0x0780
# 1            010        1000         0        0            0           0        Connected	An						0x0a80
# 1            010        0100         0        0            0           0        Connected	WAIT_FOR_K28.7_IDLES	0x0a40
# 1            010        0010         0        0            0           0        Connected	WAIT_FOR_FRAME_SYNC_T	0x0a20
# 1            010        0001         0        1            0           0        Connected	FRAME_SYNC				0x0a14
# 1            010        0001         1        1            0           0        Running                			0x0a1c
#
address=$addr value=0x0783

# CPRI Fibre status register
#
#0x20C 	Stat_Code 	3..0 	R 	N/A 	The current state of the core. Notable states are 0x0 (which indicates the core is in reset), 0x1 (which indicates that sync has begun and is failing due to LOS or LOF conditions), and 0xF (which indicates the core is fully operational).
#0x20C 	Stat_Alarm 	7 	R 	N/A 	High if the SDI or Reset bits are set, if the local LOS, LOF, or RAI bits are set, or if the remote LOS, LOF, or RAI bits are set.
#0x20C 	MGT_PLL_Lock 	8 	R 	N/A 	High if the MGT PLL is locked.
#0x20C 	MGT_Tx_Clock_Lock 	9 	R 	N/A 	High if the MGT Tx clock generation is locked.
#0x20C 	MGT_Rx_Clock_Lock 	10 	R 	N/A 	High if the MGT Rx clock generation is locked. In the case where there is no Rx clock generation circuitry, the MGT_PLL_Lock will be used.
#0x20C 	SFP_LOS 	11 	R 	N/A 	High if the LOS signal from the SFP is active.
#0x20C 	LOS 	12 	R 	N/A 	High if the CPRI core has found a Loss Of Signal condition. This occurs if there is a loss of light from the SFP or if 16 8B/10B errors occur within a hyperframe.
#0x20C 	LOF 	13 	R 	N/A 	High if the CPRI core has found a Loss Of Frame condition. This occurs if the CPRI core cannot achieve or loses hyperframe sync.
#
address=$addr_cpri value=0x3880

field=R21Lo[${fibre}]  value=$r21
field=R21Hi[${fibre}]  value=0
field=CDCFIFODelay[${fibre}]  value=$fifo
field=BarrelShift[${fibre}]  value=$barrel
field=Framediff[${fibre}]  value=$framediff
field=FramediffAdjust[${fibre}]  value=$framediffadj


FIBRE

		printf $fh "# Fibre control - disable Tx \naddress=0x%05x value=0x4806\n\n\n", 0x40010 + $fibre*0x01000 ;
	}



	## RF Chain
	print $fh "## Chains\n\n" ;
	my $processing = 0x1234 ;
	for (my $chain = 0; $chain < $max_chains; ++$chain)
	{
		#           'chains' => {
		#                         'UL' => {
		#                                   '1' => {
		#                                            'antennas' => {
		#                                                            '13' => '1',
		#                                                            '12' => '0'
		#                                                          },
		#                                            'Start IQ' => '12',
		#                                            'Type' => '4',
		#                                            'Num Streams' => '2',
		#                                            'End IQ' => '13'
		#                                          },

		my $dliqs = $chain >= $dlchains ? 0 : $info_href->{'chains'}{'DL'}{$chain}{'Num Streams'} ;
		my $uliqs = $chain >= $ulchains ? 0 : $info_href->{'chains'}{'UL'}{$chain}{'Num Streams'} ;

		my $dltype = $chain >= $dlchains ? 0 : $info_href->{'chains'}{'DL'}{$chain}{'Type'} ;
		my $ultype = $chain >= $ulchains ? 0 : $info_href->{'chains'}{'UL'}{$chain}{'Type'} ;

		my $dlproc = $processing+7;
		my $ulproc = $processing-5;
		$processing += 17 ;

		print $fh "# Chain $chain\n" ;

		print $fh <<CHAIN ;
field=DlType[$chain] value=$dltype
field=DlIqStreams[$chain] value=$dliqs
field=ResultingDlProcessing[$chain] value=$dlproc
field=UlType[$chain] value=$ultype
field=UlIqStreams[$chain] value=$uliqs
field=ResultingUlProcessing[$chain] value=$ulproc

CHAIN

	}



	## Fibre IQ


	print $fh "## ## Fibre IQ Stream\n\n" ;
	my $iqstream = 0 ;
	for (my $fibre = 0; $fibre < $fibres; ++$fibre)
	{
		# UL should be same as DL!
		my $dl_fibre_iqstreams = $info_href->{'fibres'}{$fibre}{'DL Streams'} ;
		my $ul_fibre_iqstreams = $info_href->{'fibres'}{$fibre}{'UL Streams'} ;

		# Just use UL
		my $start_iq = $info_href->{'fibres'}{$fibre}{'UL Start IQ'} ;
		my $num_dbm_iqstreams = $ul_fibre_iqstreams/4 ;

		print $fh "# Fibre $fibre\n" ;
		for (my $fibre_iq=0; $fibre_iq < $ul_fibre_iqstreams; ++$fibre_iq)
		{
			my $iq = $start_iq + $fibre_iq ;

			print $fh "field=FibrePath\[$iqstream\] value=$fibre\n" ;
			print $fh "field=FibreIQType\[$iqstream\] value=1\n" ;
			print $fh "field=FibreIQStream\[$iqstream\] value=$iq\n" ;

			my $dbm_supported = $iqstream >= $fibres*$ul_fibre_iqstreams-$num_dbm_iqstreams ? 1 : 0 ;
			print $fh "field=DBMSupported\[$iqstream\] value=$dbm_supported\n" ;

			my $ulDelayActual = 0x7658 + 3 * $iqstream ;
			print $fh "field=UlDelayActual\[$iqstream\] value=$ulDelayActual\n" ;

			print $fh "\n" ;

			++$iqstream ;
		}
	}


	## RF Chain IQ

	print $fh "## ## RF Chain IQ Stream\n\n" ;
	for (my $chain = 0; $chain < $max_chains; ++$chain)
	{
		if ($chain < $dlchains)
		{
		#                                            'antennas' => {
		#                                                            '13' => '1',
		#                                                            '12' => '0'
		#                                                          },
		#                                            'Start IQ' => '12',
		#                                            'Type' => '4',
		#                                            'Num Streams' => '2',
		#                                            'End IQ' => '13'

			my $dliqs = $info_href->{'chains'}{'DL'}{$chain}{'Num Streams'} ;
			my $dltype = $info_href->{'chains'}{'DL'}{$chain}{'Type'} ;
			my $dliq = $info_href->{'chains'}{'DL'}{$chain}{'Start IQ'} ;
			my $dliqend = $info_href->{'chains'}{'DL'}{$chain}{'End IQ'} ;

			print $fh "# Chain $chain - DL ($dliq .. $dliqend)\n" ;
			for (my $iq=$dliq; $iq <= $dliqend; ++$iq)
			{
				my $ant = 1 + $info_href->{'chains'}{'DL'}{$chain}{'antennas'}{$iq} ;

				my $addr = 0x78000 + $iq*0x00100 ;

				my $path_type = ($dltype << 4) | ($chain & 0x0f) ;

				print $fh "field=DlRfChainPath\[$iq\] value=$chain\n" ;
				print $fh "field=DlRfChainType\[$iq\] value=$dltype\n" ;
				print $fh "field=DlRfChainAntPort\[$iq\] value=$ant\n" ;
				print $fh "field=DlRfChainIqStream\[$iq\] value=$iq\n" ;

				print $fh "field=DLSampBufSize\[$iq\] value=1\n" ;
				print $fh "field=ULSampBufSize\[$iq\] value=2\n" ;

				## Set TSSI & RSSI to some debug values
				my $tssi = (2*$iq+3) & 0xffff ;
				my $rssi_hi = $iq & 0xffff ;
				my $rssi_lo = (3*$iq+4) & 0xffff ;

				print $fh "field=DLTSSI\[$iq\] value=$tssi\n" ;
				print $fh "field=ULRSSIHi\[$iq\] value=$rssi_hi\n" ;
				print $fh "field=ULRSSILo\[$iq\] value=$rssi_lo\n" ;
			}
			print $fh "\n" ;
		}


		if ($chain < $ulchains)
		{
			my $uliqs = $info_href->{'chains'}{'UL'}{$chain}{'Num Streams'} ;
			my $ultype = $info_href->{'chains'}{'UL'}{$chain}{'Type'} ;
			my $uliq = $info_href->{'chains'}{'UL'}{$chain}{'Start IQ'} ;
			my $uliqend = $info_href->{'chains'}{'UL'}{$chain}{'End IQ'} ;

			print $fh "# Chain $chain - UL ($uliq .. $uliqend)\n" ;
			for (my $iq=$uliq; $iq <= $uliqend; ++$iq)
			{
				my $ant = 1 + $info_href->{'chains'}{'UL'}{$chain}{'antennas'}{$iq} ;

				my $addr = 0x78000 + $iq*0x00100 ;

				my $path_type = ($ultype << 4) | ($chain & 0x0f) ;

				print $fh "field=UlRfChainPath\[$iq\] value=$chain\n" ;
				print $fh "field=UlRfChainType\[$iq\] value=$ultype\n" ;
				print $fh "field=UlRfChainAntPort\[$iq\] value=$ant\n" ;
				print $fh "field=UlRfChainIqStream\[$iq\] value=$iq\n" ;
			}
			print $fh "\n" ;
		}
	}



	close $fh ;
}


#=================================================================================
# END
#=================================================================================
__END__

=head1 NAME

capacity-emu-fpga-cfg - Create fpga emulation config file from fpga capacity report

=head1 SYNOPSIS

capcity-emu-fpga-cfg [options] <filename>

Options:

       -debug level         set debug level
       -verbose level       set verbosity level
       -help                brief help message
       -man                 full documentation

       -capacity <file>     Capacity report text file

=head1 OPTIONS

=over 8

=item B<-help>

Print a brief help message and exits.

=item B<-man>

Prints the manual page and exits.

=item B<-verbose>

Set verbosity level. Higher values show more information.

=item B<-debug>

Set debug level. Higher levels show more debugging information (only really of any interest to developers!)

=item B<-capacity>

Required option used to specify the filename of the capacity report (see below for description)

=back

=head1 DESCRIPTION

Create a configuration file for the FPGA emulator using the capacity report from a real fpga.

The RRH TIF interface provides a command for reporting the fpga capacity information ".carrierHw.showCapacity"
which needs to be run in su mode:

/#->.carrierHw.showCapacity
Status=OK Info="
Num Fibres.............: 2
Num TX Ant.............: 2
Num RX Ant.............: 2
Num DL Carriers........: 14
Num UL Carriers........: 14
Num DL Chains..........: 2
Num UL Chains..........: 2
Fibre 0
  DL Streams...........: 6
  DL Start IQ..........: 0
  UL Streams...........: 6
  UL Start IQ..........: 0
Fibre 1
  DL Streams...........: 8
  DL Start IQ..........: 6
  UL Streams...........: 8
  UL Start IQ..........: 6
UL Chain 0
  Type.................: 11
  Num Streams..........: 12
  Start IQ.............: 0
  End IQ...............: 11
  IQ 0 Antenna......: 0
  IQ 1 Antenna......: 1
  IQ 2 Antenna......: 0
  IQ 3 Antenna......: 1
  IQ 4 Antenna......: 0
  IQ 5 Antenna......: 1
  IQ 6 Antenna......: 0
  IQ 7 Antenna......: 1
  IQ 8 Antenna......: 0
  IQ 9 Antenna......: 1
  IQ 10 Antenna......: 0
  IQ 11 Antenna......: 1
UL Chain 1
  Type.................: 4
  Num Streams..........: 2
  Start IQ.............: 12
  End IQ...............: 13
  IQ 12 Antenna......: 0
  IQ 13 Antenna......: 1
DL Chain 0
  Type.................: 11
  Num Streams..........: 12
  Start IQ.............: 0
  End IQ...............: 11
  IQ 0 Antenna......: 0
  IQ 1 Antenna......: 1
  IQ 2 Antenna......: 0
  IQ 3 Antenna......: 1
  IQ 4 Antenna......: 0
  IQ 5 Antenna......: 1
  IQ 6 Antenna......: 0
  IQ 7 Antenna......: 1
  IQ 8 Antenna......: 0
  IQ 9 Antenna......: 1
  IQ 10 Antenna......: 0
  IQ 11 Antenna......: 1
DL Chain 1
  Type.................: 4
  Num Streams..........: 2
  Start IQ.............: 12
  End IQ...............: 13
  IQ 12 Antenna......: 0
  IQ 13 Antenna......: 1
"

You run this command and cut'n'paste the output into a text file. Then specify that text file as the -capcity
option to create a new config file.

Command:

  ./tools/capacity-emu-fpga-cfg.pl -capacity capacity.txt cfg/fpga-emu.cfg



=cut
