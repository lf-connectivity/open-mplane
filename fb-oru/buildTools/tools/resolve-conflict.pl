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

our $VERSION = "1.00" ;
our $name ;
our $fullname ;
our $DEBUG = 0 ;

my @cmdLine = @ARGV;				# save for debug

	my $debug=0 ;
	my $verbose=0 ;
	my $help=0 ;
	my $man=0 ;
	
	my $verbose = 0 ;
	
	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,
		
		'v=i' => \$verbose,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

	process($verbose) ;    

	exit(0);


#============================================================================================

#--------------------------------------------------------------------------------------------
sub process
{
	my ($verbose) = @_ ;

	my $wd = `pwd`;
	chomp $wd;
	 
	## Get files
	my $out = `find "$wd" |grep -v build/|grep -v .git/` ;

	my @files = split /\s+/, $out ;
	for my $file (@files)
	{
		next if (-d $file) ;
		print "FILE: $file\n" if $verbose > 0 ;
		
		my ($name,$path,$suffix) = fileparse($file, qr/\.[^.]*/);
		
		my $ok = 0 ;
		$ok=1 if ($suffix eq ".cpp") ;
		$ok=1 if ($suffix eq ".h") ;
		$ok=1 if ($name eq "CMakeLists") ;
		
		if ( !$ok )
		{
			print "**SKIPPED**\n" if $verbose > 0 ;
			next;
		}

#print "PROCESS $file\n" ;

		## Create the sed command
		my $cmd = "sed -i" ;
		$cmd .= " -e '/<<<<<<< HEAD/,/=======/d'";
		$cmd .= " -e '/>>>>>>> refs\\/remotes\\/origin\\/master/d'";
		$cmd .= " $file" ;
		
		#print "CMD: $cmd\n" ;
		
		$out = `$cmd` ;

		
	}
		
	
}



#---------------------------------------------------------------------------------------------------------------

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

resolve-conflict - Resolve conflict by restoring the master version

=head1 SYNOPSIS

resolve-conflict [options]

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

Run this script in a directory to resolve this directory (and it's subdirectories). Resolves only known source files:

*.cpp
*.h
CMakeLists.txt


=cut

