#!/usr/bin/perl

# use warnings;
use strict;

use IO::File;
use Carp qw{verbose};
use Data::Dumper;
use Getopt::Long;
use POSIX qw{strftime} ;
use Pod::Usage ;
use File::Spec ;
use File::Basename ;
use File::Path qw/make_path/ ;

our $VERSION = "1.01" ;
our $name ;
our $fullname ;
our $DEBUG = 0 ;

my @cmdLine = @ARGV;				# save for debug


	my $debug=0 ;
	my $verbose=0 ;
	my $help=0 ;
	my $man=0 ;
	
	my $yangdir = "." ;
	my $yanglint ;
	my $outfile ;
	
	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,
		
		'dir=s' => \$yangdir,
		'yanglint=s' => \$yanglint,
		'out=s' => \$outfile,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

    pod2usage("$0: No yanglint given.")  if (!$yanglint) ;
    pod2usage("$0: No output file given.")  if (!$outfile) ;

	if (! -x $yanglint)
	{
	    pod2usage("$0: yanglint invalid.") ;
	}

	## make output dir
	my $outdir = (File::Spec->splitpath($outfile))[1] ;
	make_path($outdir) ;	
	
	print "GENERATE: $outfile\n" ;

	open(my $ofh, ">", "$outfile") or die "Unable to write $outfile" ;

	chdir $yangdir ;
	for my $yangfile (glob("./*.yang"))
	{
		process_file($yanglint, $yangfile, $ofh) ;  
	}
	
	close $ofh ;  

	exit(0);


#============================================================================================

#--------------------------------------------------------------------------------------------
sub process_file
{
	my ($yanglint, $yangfile, $ofh) = @_ ;
	
	print "PROCESS : $yangfile\n" ;
	print $ofh "           <schema>\n" ;

	open(my $fh, '-|', "$yanglint -f yin $yangfile") or die $!;
	while (my $line = <$fh>) 
	{
		chomp $line ;
		
		print "$line\n" ;
		
# <?xml version="1.0" encoding="UTF-8"?>
# <module name="o-ran-usermgmt"
#         xmlns="urn:ietf:params:xml:ns:yang:yin:1"
#         xmlns:o-ran-usermgmt="urn:o-ran:user-mgmt:1.0"
#         xmlns:nacm="urn:ietf:params:xml:ns:yang:ietf-netconf-acm">
#   <yang-version value="1.1"/>
#   <namespace uri="urn:o-ran:user-mgmt:1.0"/>
 
 		if ($line =~ /module name=\"([^\s\"]+)\"/)
 		{
 			print $ofh "              <identifier>$1</identifier>\n" ;
 			next ;
 		}
 
 		if ($line =~ /namespace uri=\"([^\s\"]+)\"/)
 		{
 			print $ofh "              <namespace>$1</namespace>\n" ;
 			next ;
 		}
 
 		if ($line =~ /yang-version value=\"([^\s\"]+)\"/)
 		{
 			print $ofh "              <version>$1</version>\n" ;
 			next ;
 		}
 
	}

	print $ofh "           </schema>\n" ;
	close $fh ;


}

#---------------------------------------------------------------------------------------------------------------

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

yang2schemas - Convert YANG files into schema xml

=head1 SYNOPSIS

yang2schemas [options]  -yanglint <path to yanglint> -dir <path to yang files> -out <output file>

Options:

       -debug level         set debug level
       -verbose level       set verbosity level
       -help                brief help message
       -man                 full documentation
       -edit                create XML for 'edit-config' variables (rather than 'get')
       
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

Runs yanglint on all yang files found in the specified directory and converts to schema xml

=cut

