#!/usr/bin/perl -w
#
# $Revision: 27548 $
#
# Simple script that strips off the header bytes from a Xilinx bit file
#

use warnings;
use strict;

use IO::File;
use Carp qw{verbose};
use Data::Dumper;
use Getopt::Long;
use POSIX qw{strftime} ;
use Pod::Usage ;
use File::Spec ;
use File::Path qw/make_path/ ;

our $VERSION = "1.00" ;


my @cmdLine = @ARGV;				# save for debug


	my $debug=0 ;
	my $verbose=0 ;
	my $help=0 ;
	my $man=0 ;
	
	my $infile ;
	my $outfile ;
	
	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,
		
		'i=s' => \$infile,
		'o=s' => \$outfile,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

    pod2usage("$0: No input file given.")  if (!$infile) ;
    pod2usage("$0: No output file given.")  if (!$outfile) ;

	if (! -f $infile)
	{
	    pod2usage("$0: Input file invalid.") ;
	}

	process_file($infile, $outfile) ;    

	exit(0);


#============================================================================================

#--------------------------------------------------------------------------------------------
sub process_file
{
	my ($infile, $outfile) = @_ ;
	
	# Look for the frame marker (32 bytes of 0xFF)
	open(my $fh, "<", "$infile") or die "Unable to read $infile" ;
	binmode $fh ;
	
	my $buffer ;
	my $num_read = read $fh, $buffer, 1024, 0 ;
	
	my @bytes = unpack("C*", $buffer) ;
	
	my $start = 0 ;
	my $ff_count = 0 ;
	foreach my $byte (@bytes)
	{
		++$start ;

		if ($byte == 0xff)
		{
			if (++$ff_count >= 32)
			{
				$start -= 32 ;
				last ;
			}
		}
		else
		{
			$ff_count = 0 ;
		}

	}
	
	print "Input........: $infile\n" ;
	print "Output.......: $outfile\n" ;
	print "Data start...: $start\n" ;

	open(my $ofh, ">", "$outfile") or die "Unable to write $outfile" ;
	binmode $ofh ;
	
	my @out ;
	for (my $i=$start; $i < scalar(@bytes); ++$i)
	{
		push @out, $bytes[$i] ;
	}
	print $ofh pack("C*", @out) ;
	
	while ($num_read > 0)
	{
		$num_read = read $fh, $buffer, 8192 ;
		print $ofh $buffer ;
	}
	
	close $fh ;
	close $ofh ;
	
}

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

xilinx-bin2bit - Convert Xilinx bit file to bin file

=head1 SYNOPSIS

xilinx-bin2bit [options] -i <bit file> -o <bin file

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

Reads the Xilinx bit file, finds the header and removes it creating the stripped bin file


=cut

