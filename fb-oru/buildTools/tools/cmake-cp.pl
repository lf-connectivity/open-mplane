#!/usr/bin/perl -w
#
# Script to create a copy of a cmake directory (and it's control file)
#

use warnings;
use strict;

use IO::File;
use Carp qw{verbose};
use Data::Dumper;
use Getopt::Long;
use POSIX qw{strftime} ;
use Pod::Usage ;
use File::Basename ;
use File::Spec ;
use File::Path qw/make_path/ ;
use POSIX qw/strftime/ ;

our $VERSION = "1.00" ;


my @cmdLine = @ARGV;				# save for debug


	my $debug=0 ;
	my $verbose=0 ;
	my $help=0 ;
	my $man=0 ;
	
	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

    pod2usage(1) if @ARGV < 2;

	process_file($ARGV[0], $ARGV[1]) ;    

	exit(0);


#============================================================================================

#--------------------------------------------------------------------------------------------
sub process_file
{
	my ($src, $dst) = @_ ;
	
	print "PROCESS: $src\n" ;
	
	my $cmakeSrc = "$src/CMakeLists.txt" ;
	
	# Start by determining the type of CMakeLists file
	
	my $topLevel = 0 ;
	my $line ;
	open(my $fh, "<", "$cmakeSrc") or die "Unable to read $cmakeSrc" ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		print "LINE <$line>\n" if $debug ; 

		$line =~ s/^\s+// ;
		$line =~ s/\s+$// ;
		next unless $line ;
		
		# If get line like:
		#    cmake_minimum_required ....
		# then this is a top-level file
		if ($line =~ m%cmake_minimum_required%)
		{
			$topLevel = 1 ;
			last ;
		}
	}
	close $fh ;	

	$src = File::Spec->rel2abs($src) ;
	$dst = File::Spec->rel2abs($dst) ;

	if ($topLevel)
	{
		processTop($src, $dst) ;
	}
	else
	{
		processSub($src, $dst) ;
	}	
}


#--------------------------------------------------------------------------------------------
sub processTop
{
	my ($src, $dst) = @_ ;
	
	print "PROCESS TOP: $src\n" ;
	
	my $cmakeSrc = "$src/CMakeLists.txt" ;
	my $cmakeDst = "$dst/CMakeLists.txt" ;
	
	my $srcRel = File::Spec->abs2rel($src, $dst) ;
	my $dstRel = File::Spec->abs2rel($dst, $src) ;
	my $srcBase = fileparse($src) ;
	my $dstBase = fileparse($dst) ;
	
print "SRC $src BASE $srcBase REL $srcRel\n" ;	
print "DST $dst BASE $dstBase REL $dstRel\n" ;	

	make_path($dst) ;	
	
	my $line ;
	open(my $fh, "<", "$cmakeSrc") or die "Unable to read $cmakeSrc" ;
	open(my $ofh, ">", "$cmakeDst") or die "Unable to write $cmakeDst" ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		print "LINE <$line>\n" if $debug ; 
		

		if ($line =~ m%add_subdirectory%)
		{
			$line =~ s/add_subdirectory/addExternalDirectory/ ;
			$line =~ s%\(%($srcRel/% ;
		}
		else
		{
			$line =~ s/$srcBase/$dstBase/g ;
		}
		
		print $ofh "$line\n" ;
	}
	close $fh ;	
	close $ofh ;	

}

#--------------------------------------------------------------------------------------------
sub processSub
{
	my ($src, $dst) = @_ ;
	
	print "PROCESS SUB: $src\n" ;
	
	my $cmakeSrc = "$src/CMakeLists.txt" ;
	my $cmakeDst = "$dst/CMakeLists.txt" ;
	
	# Start by determining the type of CMakeLists file
	
	my $line ;
	open(my $fh, "<", "$cmakeSrc") or die "Unable to read $cmakeSrc" ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		print "LINE <$line>\n" if $debug ; 

		$line =~ s/^\s+// ;
		$line =~ s/\s+$// ;
		next unless $line ;
		
	}
	close $fh ;	

}


#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

cmake-cp - Script to create a copy of a cmake directory (and it's control file)

=head1 SYNOPSIS

cmake-cp <source> <destination>

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

Reads the CMakeLists.txt file in the <source> directory to use it as a template for creating a new file in the <destination>
directory. Creates the new CMakeLists.txt to completely reuse the existing source directories.

=cut

