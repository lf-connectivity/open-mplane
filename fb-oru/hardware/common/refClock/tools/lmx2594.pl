#!/usr/bin/perl -w
#
#

use warnings;
use strict;

use Getopt::Long;
use Pod::Usage ;

our $VERSION = "1.00" ;

	my $debug = 0;
	my $verbose = 0;
	my $help ;
	my $man ;
		
	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'help' => \$help,
	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;
    pod2usage("$0: No arguments given.")  if (@ARGV == 0) ;
    pod2usage("$0: Specify input and output filenames.")  if (@ARGV < 2) ;
	
	my $infile = $ARGV[0] ;
	my $outfile = $ARGV[1] ;

	process_file($infile) ;
	
	exit 0 ;

#=================================================================================
# FUNCTIONS
#=================================================================================

#--------------------------------------------------------------------------------------------
sub process_file
{
	my ($datasheet) = @_ ;
	
	print "PROCESS: $datasheet\n" ;
	
	my $line ;
	my %info ;
	my $inRegBits = 0 ;
	my $inRegFields = 0 ;
	my @bitCols ;
	
	open(my $fh, "<", "$datasheet") or die "Unable to read $datasheet" ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		
		print "LINE <$line>\n" ; 

		# Look for start of register bit section
		#               D15   D14    D13   D12     D11   D10       D9           D8    D7       D6      D5       D4       D3       D2       D1       D0
		if ($line =~ m/\s*D15\s+D14/)
		{
			$inRegBits = 1 ;
			$inRegFields = 0 ;
			
			# Need to work out the columns
			@bitCols = () ;
			while ($line =~ /D/g)
			{
				push @bitCols, $-[0] ;
				print "bit col $-[0]\n" ;
			}			
			
			next ;
		}
		
		# Look for 
		#  Location        Field                          Type           Reset        Description
		if ($line =~ m/\s*Location\s+Field/)
		{
			$inRegBits = 0 ;
			$inRegFields = 1 ;
			next ;
		}
		
		
		
		if ($inRegBits)
		{
			# Look for 
			#      R0           E_SY       1     0       0     1                                                      1                             ERDO
			if ($line =~ /\s*R([0-9]+)\s+/)
			{
				my $reg = $1 ;
				my $dataStart = $+[0] ;
				print "Found reg R$reg\n" ;
				my $regDefault = 0 ;
				while ($line =~ /1/g)
				{
					next if ($-[0] <= $dataStart) ;
					
					print " * R$reg bit set at col $-[0]\n" ;
					
					# Convert column to a bit number
					for (my $i=0; $i < $#bitCols; ++$i)
					{
						next if ($-[0] != $bitCols[$i]) ;
						
						my $bitNum = 15 - $i ;
						my $defVal = 1 << $bitNum ;
						$regDefault |= $defVal ;
						print " * R$reg col [$i] bit $bitNum : default=$regDefault\n" ;
					}
				}			
			}
		}

	}
	
	close $fh ;	
	
}



#=================================================================================
# END
#=================================================================================
__END__

=head1 NAME

lmx2594 - Create LMX2594 header from datasheet

=head1 SYNOPSIS

lmx2594 [options] <input filename> <output filename>

Options:

       -debug level         set debug level
       -verbose level       set verbosity level
       -help                brief help message
       -man                 full documentation
       
       
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

Processes the LMX2594 pdf to text output in order to create a header file with the register definitions


=cut
