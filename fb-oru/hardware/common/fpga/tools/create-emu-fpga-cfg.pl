#!/usr/bin/perl -w
#
# Create off-target fpga settings
#

use warnings;
use strict;

use Data::Dumper;
use Getopt::Long;
use Pod::Usage ;

	our $VERSION = "2.11" ;

	my $debug = 0;
	my $verbose = 0;
	my $help ;
	my $man ;

	my $outfile ;

	my ($fibres, $antennas, $carriers) = (2, 2, 8) ;
	my ($dlchains, $ulchains) = (6, 8) ;
	my ($dl_chain_iqstreams, $ul_chain_iqstreams) = (8, 12) ;
	my ($dl_fibre_iqstreams, $ul_fibre_iqstreams) = (12, 16) ;
	my @chains ;

	my $options = "" ;

	GetOptions(
		"debug=i" 		=> \$debug,
		"verbose=i" 	=> \$verbose,
		'man' 			=> \$man,

		'fibres=i'		=> \$fibres,
		'ants=i'		=> \$antennas,
		'carriers=i'	=> \$carriers,
		'dlchains=i'	=> \$dlchains,
		'ulchains=i'	=> \$ulchains,

		'dlfiq=i'		=> \$dl_fibre_iqstreams,
		'ulfiq=i'		=> \$ul_fibre_iqstreams,

		'dlciq=i'		=> \$dl_chain_iqstreams,
		'ulciq=i'		=> \$ul_chain_iqstreams,

		'chain=s@'		=> \@chains,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;
    pod2usage("$0: No arguments given.")  if (@ARGV == 0) ;

	my $max_chains = $dlchains>$ulchains ? $dlchains : $ulchains ;

	if (!@chains)
	{
		## For my testing, I want chain0 and chain5 set to type 4
		#//	0 	Supports WiMAX channel bandwidths 3.5, 5, 7 and 10 MHz at a 224 MHz DSP clock rate
		#//	1 	Supports LTE channel bandwidths 5, 10, 15 and 20 MHz at a 224 MHz DSP clock rate
		#//	2 	Supports W-CDMA (5 MHz channel bandwidth only) at a 224 MHz DSP clock rate
		#//	3 	Supports WiMAX channel bandwidths 3.5, 5, 7 and 10 MHz at a 245.76 MHz DSP clock rate
		#//	4 	Supports LTE channel bandwidths 5, 10, 15 and 20 MHz at a 245.76 MHz DSP clock rate
		#//	5 	Supports LTE channel bandwidths 5 and 10 MHz only at a 245.76 MHz DSP clock rate
		#//	6 	Supports LTE channel bandwidths 5 MHz only at a 245.76 MHz DSP clock rate
		#//
		#//	7 	Supports LTE channel bandwidths 5, 10, 15 and 20 MHz and W-CDMA at a 245.76 MHz DSP clock rate
		#//	8 	Supports LTE channel bandwidths 5 and 10 MHz only and W-CDMA at a 245.76 MHz DSP clock rate
		#//	9 	Supports LTE channel bandwidths 5 MHz only and W-CDMA at a 245.76 MHz DSP clock rate

		#  chain      0, 1, 2, 3, 4, 5, 6, 7
		my @types = ( 4, 7, 8, 0, 9, 4, 2, 6) ;

		# set defaults
		my $ant=1 ;
		my $type_idx=0 ;
		for (my $chain = 0; $chain < $max_chains; ++$chain)
		{
			my $type = $types[$type_idx] ;

			# chain:type:ant:dliqstreams:uliqstreams
			push @chains, "$chain:$type:$ant:$dl_chain_iqstreams:$ul_chain_iqstreams" ;

			if (++$ant > $antennas)
			{
				$ant=1 ;
			}

			if (++$type_idx >= scalar(@types))
			{
				$type_idx=0 ;
			}

#			if (--$type < 0)
#			{
#				$type =4 ;
#			}
		}
	}

	## -fibres 2 -ants 2 -carriers 28 -dlchains 2 -ulchains 2 -dlfiq 6 -ulfiq 6  -dlciq 14 -ulciq 14 -chain 0:11:a:12:12 -chain 1:4:a:2:2  tmp.tx# recreate the options used

	$options .= "-fibres $fibres " ;
	$options .= "-ants $antennas " ;
	$options .= "-carriers $carriers " ;
	$options .= "-dlchains $dlchains " ;
	$options .= "-ulchains $ulchains " ;
	$options .= "-dlfiq $dl_fibre_iqstreams " ;
	$options .= "-ulfiq $ul_fibre_iqstreams " ;
	$options .= "-dlciq $dl_chain_iqstreams " ;
	$options .= "-ulciq $ul_chain_iqstreams " ;

	foreach my $chain_spec (@chains)
	{
		$options .= "-chain $chain_spec " ;
	}


	$outfile = $ARGV[0] ;
	open my $fh, ">$outfile" or die "Error: cannot write to file $outfile : $!" ;

	## Start
	print $fh <<HEAD ;
## Created by create-emu-fpga-cfg v$VERSION
##
## Creation options set:
##   $options
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

# always done
address=0x40a values=0xffff

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


field=m0_XilinxCoreMajorRevision value=5
field=m0_XilinxCoreMinorRevision value=1
field=m1_XilinxCoreMajorRevision value=5
field=m1_XilinxCoreMinorRevision value=1

# Sizes
field=FpgaFibres value=$fibres
field=FpgaAntennas value=$antennas
field=FpgaCarriers value=$carriers
field=NumDlRfChains value=$dlchains
field=NumUlRfChains value=$ulchains

HEAD


	## Chain specs
	my @chain_info ;
#	my $processing = 33 ;
	my $processing = 0x1234 ;
	foreach my $chain_spec (@chains)
	{
print " + chain spec=$chain_spec\n" ;

		# expect chain def in the form
		#
		# chain:type:ant:dliqstreams:uliqstreams
		my @fields = split(/:/, $chain_spec) ;
		if (@fields == 5)
		{
			my $chain = $fields[0] ;
			$chain_info[$chain] = {
				'type'	=> $fields[1],
				'ant'	=> $fields[2],
				'dliq'	=> $fields[3],
				'uliq'	=> $fields[4],
				'dlproc'=> $processing+7,
				'ulproc'=> $processing-5,
			} ;
			$processing += 17 ;
		}
	}


	## OUTPUT ###################################################

	## Antennas

	print $fh "## Antennas\n\n" ;
	for (my $ant = 0; $ant < $antennas; ++$ant)
	{
		my $antdelay = 0x1234 + 11*$ant ;
		print $fh "# Ant $ant\n" ;
		print $fh <<ANT ;
field=antennaProcDelay[${ant}] value=$antdelay ;
ANT

	}

	## Fibres
	print $fh "## Fibres\n\n" ;
	for (my $fibre = 0; $fibre < $fibres; ++$fibre)
	{
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
m${fibre}_DlFibreIqStreams = $dl_fibre_iqstreams
m${fibre}_UlFibreIqStreams = $ul_fibre_iqstreams

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

m${fibre}_R21Lo = $r21
m${fibre}_R21Hi = 0
m${fibre}_CDCFIFODelay = $fifo
m${fibre}_BarrelShift = $barrel
m${fibre}_Framediff = $framediff
m${fibre}_FramediffAdjust = $framediffadj


FIBRE




		printf $fh "# Fibre control - disable Tx \naddress=0x%05x value=0x4806\n\n\n", 0x40010 + $fibre*0x01000 ;
	}



	## RF Chain
	print $fh "## Chains\n\n" ;
	for (my $chain = 0; $chain < $max_chains; ++$chain)
	{
		if (!$chain_info[$chain])
		{
			print "ERROR: No information for chain $chain\n" ;
			exit 1 ;
		}

		my $dliqs = $chain >= $dlchains ? 0 : $chain_info[$chain]{dliq} ;
		my $uliqs = $chain >= $ulchains ? 0 : $chain_info[$chain]{uliq} ;

		print $fh "# Chain $chain\n" ;


#		my $addr = 0x30000 + $chain*0x01000 ;
#
#		printf $fh "address=0x%05x value=0x%04x\n", $addr+0, $chain_info[$chain]{type} ;
#		printf $fh "address=0x%05x value=0x%04x\n", $addr+4, $dliqs ;
#		printf $fh "address=0x%05x value=0x%04x\n", $addr+8, $chain_info[$chain]{dlproc} ;
#		printf $fh "address=0x%05x value=0x%04x\n", $addr+0x10, $chain_info[$chain]{type} ;
#		printf $fh "address=0x%05x value=0x%04x\n", $addr+0x14, $uliqs ;
#		printf $fh "address=0x%05x value=0x%04x\n", $addr+0x18, $chain_info[$chain]{ulproc} ;
#		print $fh "\n" ;

		print $fh <<CHAIN ;
field=DlType[$chain] value=$chain_info[$chain]{type}
field=DlIqStreams[$chain] value=$dliqs
field=ResultingDlProcessing[$chain] value=$chain_info[$chain]{dlproc}
field=UlType[$chain] value=$chain_info[$chain]{type}
field=UlIqStreams[$chain] value=$uliqs
field=ResultingUlProcessing[$chain] value=$chain_info[$chain]{ulproc}

CHAIN

	}



	## Fibre IQ

	my $num_dbm_iqstreams = $ul_fibre_iqstreams/4 ;

	print $fh "## ## Fibre IQ Stream\n\n" ;
	my $iqstream = 0 ;
	for (my $fibre = 0; $fibre < $fibres; ++$fibre)
	{
		print $fh "# Fibre $fibre\n" ;
		for (my $fibre_iq=0; $fibre_iq < $ul_fibre_iqstreams; ++$fibre_iq)
		{

#			my $addr = 0x70000 + $iqstream*0x00100 ;
#
#			#	0x0 	Fibre_Path 	3..0 	R 	N/A 	Indicates the number of the link that the IQ stream is connected to.
#			#	0x0 	Fibre_Type 	7..4 	R 	N/A 	Indicates the type of the link that the IQ stream is connected to (0x1=>OBSAI RP3-01, 0x2=>CPRI).
#			#	0x2 	Fibre_IQ_Stream 	15..0 	R 	N/A 	Indicates the IQ Stream index within the link that the IQ stream is connected to.
#			my $path_type = (0x1 << 4) | ($fibre & 0x0f) ;
#
#			printf $fh "address=0x%05x value=0x%04x\n", $addr+0x00, $path_type ;
#			printf $fh "address=0x%05x value=0x%04x\n", $addr+0x02, $fibre_iq ;

			print $fh "field=FibrePath\[$iqstream\] value=$fibre\n" ;
			print $fh "field=FibreIQType\[$iqstream\] value=1\n" ;
			print $fh "field=FibreIQStream\[$iqstream\] value=$fibre_iq\n" ;

			my $dbm_supported = $iqstream >= $fibres*$ul_fibre_iqstreams-$num_dbm_iqstreams ? 1 : 0 ;
			print $fh "field=DBMSupported\[$iqstream\] value=$dbm_supported\n" ;

			my $ulDelayActual = 0x7658 + 3 * $iqstream ;
			print $fh "field=UlDelayActual\[$iqstream\] value=$ulDelayActual\n" ;

			print $fh "\n" ;

			++$iqstream ;
		}
	}


	## RF Chain IQ

	my ($dliq, $uliq) = (0, 0) ;
	print $fh "## ## RF Chain IQ Stream\n\n" ;
	for (my $chain = 0; $chain < $max_chains; ++$chain)
	{
		my ($dlchainiq, $ulchainiq) = (0,0) ;
		my $alternating_ant = 1 ;
		if ($chain < $dlchains)
		{
			my $dliqend = $dliq + $chain_info[$chain]{dliq} -1 ;
			print $fh "# Chain $chain - DL ($dliq .. $dliqend)\n" ;
			for (my $iq=$dliq; $iq <= $dliqend; ++$iq)
			{
				my $addr = 0x78000 + $iq*0x00100 ;

				my $path_type = ($chain_info[$chain]{type} << 4) | ($chain & 0x0f) ;

#				printf $fh "address=0x%05x value=0x%04x\n", $addr+0x00, $path_type ;
#				printf $fh "address=0x%05x value=0x%04x\n", $addr+0x02, $iq ;
#				printf $fh "address=0x%05x value=0x%04x\n", $addr+0x04, $chain_info[$chain]{ant} ;
#				print $fh "\n" ;

				print $fh "field=DlRfChainPath\[$iq\] value=$chain\n" ;
				print $fh "field=DlRfChainType\[$iq\] value=$chain_info[$chain]{type}\n" ;
				my $ant = $chain_info[$chain]{ant} ;
				if ($ant eq 'a')
				{
					$ant = $alternating_ant ;
				}
				print $fh "field=DlRfChainAntPort\[$iq\] value=$ant\n" ;
				print $fh "field=DlRfChainIqStream\[$iq\] value=$dlchainiq\n" ;

				print $fh "field=DLSampBufSize\[$iq\] value=1\n" ;
				print $fh "field=ULSampBufSize\[$iq\] value=2\n" ;

				## Set TSSI & RSSI to some debug values
				my $tssi = (2*$iq+3) & 0xffff ;
				my $rssi_hi = $iq & 0xffff ;
				my $rssi_lo = (3*$iq+4) & 0xffff ;

				print $fh "field=DLTSSI\[$iq\] value=$tssi\n" ;
				print $fh "field=ULRSSIHi\[$iq\] value=$rssi_hi\n" ;
				print $fh "field=ULRSSILo\[$iq\] value=$rssi_lo\n" ;

				if (++$alternating_ant > 2)
				{
					$alternating_ant = 1 ;
				}

				++$dlchainiq ;
			}
			print $fh "\n" ;
			$dliq = $dliqend + 1 ;
		}


		$alternating_ant = 1 ;
		if ($chain < $ulchains)
		{
			my $uliqend = $uliq + $chain_info[$chain]{uliq} -1 ;
			print $fh "# Chain $chain - UL ($uliq .. $uliqend)\n" ;
			for (my $iq=$uliq; $iq <= $uliqend; ++$iq)
			{
				my $addr = 0x78000 + $iq*0x00100 ;

				my $path_type = ($chain_info[$chain]{type} << 4) | ($chain & 0x0f) ;

#				printf $fh "address=0x%05x value=0x%04x\n", $addr+0x08, $path_type ;
#				printf $fh "address=0x%05x value=0x%04x\n", $addr+0x0A, $iq ;
#				printf $fh "address=0x%05x value=0x%04x\n", $addr+0x0C, $chain_info[$chain]{ant} ;
#				print $fh "\n" ;

				print $fh "field=UlRfChainPath\[$iq\] value=$chain\n" ;
				print $fh "field=UlRfChainType\[$iq\] value=$chain_info[$chain]{type}\n" ;
				my $ant = $chain_info[$chain]{ant} ;
				if ($ant eq 'a')
				{
					$ant = $alternating_ant ;
				}
				print $fh "field=UlRfChainAntPort\[$iq\] value=$ant\n" ;
				print $fh "field=UlRfChainIqStream\[$iq\] value=$ulchainiq\n" ;

				if (++$alternating_ant > 2)
				{
					$alternating_ant = 1 ;
				}

				++$ulchainiq ;
			}
			print $fh "\n" ;
			$uliq = $uliqend + 1 ;
		}
	}



	close $fh ;
	exit 0 ;



#=================================================================================
# END
#=================================================================================
__END__

=head1 NAME

create-emu-fpga-cfg - Create a load file for emu-fpga.pl

=head1 SYNOPSIS

create-emu-fpga-cfg [options] <filename>

Options:

       -debug level         set debug level
       -verbose level       set verbosity level
       -help                brief help message
       -man                 full documentation

       -fibres <num>		number of fibres [default=2]
       -ants <num>			number of antennas [default=2]
       -carriers <num>		number of carriers [default=8]
       -dlchains <num>		number of DL RF chains [default=6]
       -ulchains <num>		number of UL RF chains [default=8]
       -chain <spec>		specify chain
       -dlfiq <num>         Number of DL fibre iq streams [default=12]
       -ulfiq <num>         Number of UL fibre iq streams [default=16]
       -dlciq <num>         Number of DL chain iq streams [default=8]
       -ulciq <num>         Number of UL chain iq streams [default=12]

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

=back

=head1 DESCRIPTION

Create a load configuration file for the FPGA emulator, setting the default values of registers based on the
hardware specifications.

The -chain option may be used multiple times, once for each chain definition. Each definition is of the form:

	chain:type:ant:dliqstreams:uliqstreams

Example:

To create the following set up (which replicates real hardware), run the command shown:

	fibre0.num_dl_iqs 2
	fibre0.num_ul_iqs 2
	fibre1.num_dl_iqs 2
	fibre1.num_ul_iqs 2
	num_antennas      4
	num_carriers      32
	num_dl_carriers   16
	num_dl_chain_iqs  4
	num_dl_fibre_iqs  4
	num_dlchains      4
	num_fibres        2
	num_rx_antennas   4
	num_tx_antennas   4
	num_ul_carriers   16
	num_ul_chain_iqs  4
	num_ul_fibre_iqs  4
	num_ulchains      4
	dl_chain0.supported_type          type 7 - dspclk 245760000 airstds lte, wcdma chbws 5M, 10M, 15M, 20M
	dl_chain1.supported_type          type 7 - dspclk 245760000 airstds lte, wcdma chbws 5M, 10M, 15M, 20M
	dl_chain2.supported_type          type 0 - dspclk 224000000 airstds wimax chbws 3.5M, 5M, 7M, 10M
	dl_chain3.supported_type          type 0 - dspclk 224000000 airstds wimax chbws 3.5M, 5M, 7M, 10M
	ul_chain0.supported_type          type 7 - dspclk 245760000 airstds lte, wcdma chbws 5M, 10M, 15M, 20M
	ul_chain1.supported_type          type 7 - dspclk 245760000 airstds lte, wcdma chbws 5M, 10M, 15M, 20M
	ul_chain2.supported_type          type 0 - dspclk 224000000 airstds wimax chbws 3.5M, 5M, 7M, 10M
	ul_chain3.supported_type          type 0 - dspclk 224000000 airstds wimax chbws 3.5M, 5M, 7M, 10M


Command:

  ./utils/create-emu-fpga-cfg.pl -fibres 2 -ants 4 -carriers 8 -dlchains 4 -ulchains 4 -dlfiq 4 -ulfiq 4 \
  	-dlciq 4 -ulciq 4 -chain 0:7:1:4:4 -chain 1:7:1:4:4 -chain 2:0:1:4:4 -chain 3:0:1:4:4 cfg/emu-fpga.cfg


Example2:

To create 4 flex-chains

  ./utils/create-emu-fpga-cfg.pl -fibres 2 -ants 2 -carriers 32 -dlchains 4 -ulchains 4 -dlfiq 4 -ulfiq 4 \
  	-dlciq 4 -ulciq 8 -chain 0:10:1:4:8 -chain 1:10:1:4:8 -chain 2:10:1:4:8 -chain 3:10:1:4:8 cfg/emu-fpga-flexi.cfg

Example3:

To create the following set up (which replicates real hardware), run the command shown:

	fibre0.num_dl_iqs 3
	fibre0.num_ul_iqs 3
	fibre1.num_dl_iqs 3
	fibre1.num_ul_iqs 3
	mrcmd             info
	num_antennas      2
	num_carriers      32
	num_dl_carriers   16
	num_dl_chain_iqs  6
	num_dl_fibre_iqs  6
	num_dlchains      4
	num_fibres        2
	num_rx_antennas   2
	num_tx_antennas   2
	num_ul_carriers   16
	num_ul_chain_iqs  6
	num_ul_fibre_iqs  6
	num_ulchains      4
	dl_chain0.supported_type          type 4 - dspclk=245760000 airstds=lte chbws=5M,10M,15M,20M
	dl_chain1.supported_type          type 4 - dspclk=245760000 airstds=lte chbws=5M,10M,15M,20M
	dl_chain2.supported_type          type 5 - dspclk=245760000 airstds=lte chbws=5M,10M
	ul_chain0.supported_type          type 4 - dspclk=245760000 airstds=lte chbws=5M,10M,15M,20M
	ul_chain1.supported_type          type 4 - dspclk=245760000 airstds=lte chbws=5M,10M,15M,20M
	ul_chain2.supported_type          type 5 - dspclk=245760000 airstds=lte chbws=5M,10M


Command:

  ./tools/create-emu-fpga-cfg.pl -fibres 2 -ants 2 -carriers 32 -dlchains 3 -ulchains 3 -dlfiq 6 -ulfiq 6 \
  	-dlciq 6 -ulciq 6 -chain 0:4:1:2:2 -chain 1:4:1:2:2 -chain 2:5:1:2:2 -chain 3:0:1:0:0 cfg/etna.cfg



=cut
