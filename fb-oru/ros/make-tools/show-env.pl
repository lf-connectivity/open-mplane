#!/usr/bin/perl
#

# USAGE: show-env.pl
#
# Makefile tool used to get environment values from build settings

use warnings;
use strict;
use File::Find;
use Getopt::Long;
use Pod::Usage ;

	my $help = 0 ;
	my $man=0 ;
	my $showSize = 0 ;
	my $debug = 0 ;
	my $verbose = 0 ;

	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'h|help' => \$help,
		'man' => \$man,
		
		'size' => \$showSize,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;



	my $envVar = $ARGV[0];
	my $projectDir = $ARGV[1] || '.' ;
	
	if (!$envVar)
	{
		print "Error: Must specify an environment variable to display\n" ;
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
	
	#my $kernelSize = sprintf("0x%08x", $nameSizes{"kernel1"}) ;
	#my $kernelStart1 = sprintf("0x%08x", $offsets[ $numMap{"kernel1"} ]) ;
	#my $kernelStart2 = sprintf("0x%08x", $offsets[ $numMap{"kernel2"} ]) ;
	#
	
	if ($debug)
	{
		print "numMap\n" ;
		foreach my $name (sort keys %numMap)
		{
			print "  $name => $numMap{$name}\n" ;
		}
		print "\n" ;
		
		print "nameMap\n" ;
		foreach my $name (sort keys %nameMap)
		{
			print "  $name => $nameMap{$name}\n" ;
		}
		print "\n" ;
		
		print "nameSizes\n" ;
		foreach my $name (sort keys %nameSizes)
		{
			print "  $name => $nameSizes{$name}\n" ;
		}
		print "\n" ;
		
		print "offsets\n" ;
		foreach my $off (@offsets)
		{
			printf "  0x%08x\n", $off ;
		}
		print "\n" ;
	}
	
	if (!exists($nameSizes{$envVar}))
	{
		print "ERROR: Unknown variable $envVar\n" ;
		exit 1 ;
	}
	
	if ($showSize)
	{
		# size
		printf "0x%08x", $nameSizes{$envVar} ;
	}
	else
	{
		# start offset
		my $idx = $numMap{$envVar} ;
		printf "0x%08x", $offsets[$idx] ;
	}

	
	exit 0 ;
	
	
#---------------------------------------------------------------------------------------------------------------

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

show-env - Display partition values

=head1 SYNOPSIS

show-env [options]  <partition name>

Options:

       -debug level         set debug level
       -verbose level       set verbosity level
       -help                brief help message
       -man                 full documentation
       
       -size                Display partition size (default is to show partition start offset)
       
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

Processes the petalinux project config file to determine the flash partition settings


=cut

	
	