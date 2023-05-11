#!/usr/bin/perl
#

# USAGE: make-env.pl
#
# Creates environment file from build settings

use warnings;
use strict;
use File::Find;

my $envTemplate = $ARGV[0];
my $envFilename = $ARGV[1];
my $projectDir = $ARGV[2] || '.' ;

if (!$envTemplate || !$envFilename)
{
	print "Error: Must specify template file and output environment file\n" ;
	exit 1 ;
}

## Process config file

# proces file
my $config = "$projectDir/project-spec/configs/config" ;
open(my $fh, "$config") || die "failed to open $config - $!";
my $line;
my %nameMap ;
my %numMap ;
my %nameSizes ;
my @sizes ;
my @offsets ;
while (defined($line = <$fh>)) 
{
    chomp($line);
    
    # Looking for:
    # CONFIG_SUBSYSTEM_FLASH_PSU_QSPI_0_BANKLESS_PART0_NAME="boot"
    # CONFIG_SUBSYSTEM_FLASH_PSU_QSPI_0_BANKLESS_PART0_SIZE=0x02300000
	if ($line =~ /CONFIG_SUBSYSTEM_FLASH_PSU_QSPI_0_BANKLESS_PART(\d+)_NAME=\"([^\"]+)\"/)
	{
		my ($num, $name) = ($1, $2) ;
#		print "$num NAME $name\n" ;
		$nameMap{$num} = $name ;
		$numMap{$name} = $num ;
	}
	if ($line =~ /CONFIG_SUBSYSTEM_FLASH_PSU_QSPI_0_BANKLESS_PART(\d+)_SIZE=0x([\da-fA-F]+)/)
	{
		my ($num, $size) = ($1, hex($2)) ;
#		print "$num SIZE $size\n" ;
		if (!exists($nameMap{$num}))
		{
			continue ;
		}
	
		$nameSizes{ $nameMap{$num} } = $size ;
		
		while ($#sizes < $num)
		{
			push(@sizes, 0) ;
		}
		$sizes[$num] = $size ;
	}

}
close($fh) ;

my $offset = 0 ;
foreach my $size (@sizes)
{
	push(@offsets, $offset) ;
	$offset += $size ;	
}

#printf("KERNEL 1: 0x%08x [size 0x%08x]\n", $offsets[ $numMap{"kernel1"} ], $nameSizes{"kernel1"}) ; 
#printf("KERNEL 2: 0x%08x [size 0x%08x]\n", $offsets[ $numMap{"kernel2"} ], $nameSizes{"kernel2"}) ; 

my $kernelSize = sprintf("0x%08x", $nameSizes{"kernel1"}) ;
my $kernelStart1 = sprintf("0x%08x", $offsets[ $numMap{"kernel1"} ]) ;
my $kernelStart2 = sprintf("0x%08x", $offsets[ $numMap{"kernel2"} ]) ;

## Open template
open(my $ofh, '>', "$envFilename") || die "unable to write to $envFilename - $!";
open(my $tfh, "$envTemplate") || die "failed to open $envTemplate - $!";
while (defined($line = <$tfh>)) 
{
    chomp($line);
	$line =~ s/(\$\w+)/$1/eeg ;
	print $ofh "$line\n" ;    
}
close $ofh ;
close $tfh ;

#print<<"EOF";
#bootcmd=run boot1
#bootdelay=4
#console=console=ttyPS0,115200
#boot1=sf probe 0 && sf read \${netstart} \${kernelstart1} \${kernelsize} && bootm \${netstart}
#boot2=sf probe 0 && sf read \${netstart} \${kernelstart2} \${kernelsize} && bootm \${netstart}
#kernelsize=$kernelSize
#kernelstart1=$kernelStart1
#kernelstart2=$kernelStart1
#netstart=0x10000000
#EOF
