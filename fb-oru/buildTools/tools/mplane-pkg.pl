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

my %SKIP_LIST = (
	".LICENSE" => 0,
	".LZO" => 1,
	".anno_out" => 0,
	".art" => 1,
	".bak" => 0,
	".bin" => 1,
	".bsh" => 0,
	".c" => 0,
	".cc" => 0,
	".cfg" => 0,
	".classpath" => 0,
	".cmd" => 0,
	".conf" => 0,
	".config" => 0,
	".contrib" => 0,
	".cpp" => 0,
	".cproject" => 0,
	".css" => 0,
	".dll" => 1,
	".dot" => 0,
	".dox" => 0,
	".doxyfile" => 0,
	".dtd" => 0,
	".editorconfig" => 0,
	".el" => 0,
	".env" => 0,
	".exe" => 1,
	".filters" => 1,
	".gif" => 1,
	".gitattributes" => 1,
	".gitignore" => 1,
	".gitmodules" => 1,
	".gv" => 0,
	".gz" => 1,
	".h" => 0,
	".hpp" => 0,
	".html" => 0,
	".ico" => 1,
	".ifp" => 0,
	".in" => 0,
	".inc" => 0,
	".java" => 0,
	".jmx" => 0,
	".js" => 0,
	".json" => 0,
	".lnk" => 1,
	".log" => 0,
	".md" => 0,
	".md5" => 0,
	".md5list" => 0,
	".mf" => 0,
	".mk" => 0,
	".odg" => 0,
	".odp" => 0,
	".old" => 0,
	".out" => 0,
	".pdf" => 0,
	".pkg" => 0,
	".pl" => 0,
	".pm" => 0,
	".png" => 1,
	".prefs" => 0,
	".project" => 0,
	".properties" => 0,
	".py" => 0,
	".rc" => 0,
	".script" => 0,
	".sh" => 0,
	".sln" => 1,
	".svg" => 0,
	".tgz" => 1,
	".tpl" => 0,
	".tsf" => 0,
	".txt" => 0,
	".vcxproj" => 1,
	".vdproj" => 1,
	".vhd" => 0,
	".vim" => 0,
	".xcf" => 0,
	".xml" => 0,
	".xsd" => 0,
	".xsl" => 0,
	".xx" => 0,
	".xz" => 1,
	".yang" => 0,
	".yml" => 0,
	".zip" => 1,
) ;

my @TRANSLATE_LIST = (
	's/Mplane/Mplane/g',
) ;

	my $debug=0 ;
	my $verbose=0 ;
	my $help=0 ;
	my $man=0 ;
	my $ros_only ;

	my $merge = 0 ;
	my $verbose = 0 ;

	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,

		'm' => \$merge,
		'v=i' => \$verbose,
		'ros' => \$ros_only,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

	process($merge, $verbose, $ros_only) ;

	exit(0);


#============================================================================================

#--------------------------------------------------------------------------------------------
sub process
{
	my ($merge, $verbose, $ros_only) = @_ ;

	my $wd = `pwd`;
	chomp $wd;

	# get the list of repositories
	my $out = `make BOARD=ATLAS CUSTOMER=MPLANE APPLICATION=ORANRRH show-repos` ;
#	print "REPOS: $out\n";

	if ($ros_only)
	{
		$out = "ros" ;
	}

	my %extensions ;
	my %warnings ;
	my $numWarnings = 0 ;

	my @repos = split /\s+/, $out ;
	for my $repo (@repos)
	{
		print "REPO: $repo\n" ;

		$warnings{$repo} = {} ;


		## Do git merge is required
		if ($merge)
		{
			$out = `cd $wd/../../$repo && git merge master` ;
			print "MERGE: $out\n" ;
		}

		## Get files
		$out = `find "$wd/../../$repo" |grep -v build/|grep -v .git/` ;
#		print "FILES: $out\n";

		my @files = split /\s+/, $out ;
		for my $file (@files)
		{
			next if (-d $file) ;
			print "FILE: $file\n" if $verbose > 0 ;

			my ($name,$path,$suffix) = fileparse($file, qr/\.[^.]*/);

			$extensions{$suffix} = 1 ;

			if ( (exists $SKIP_LIST{$suffix}) && ($SKIP_LIST{$suffix} == 1) )
			{
				print "**SKIPPED**\n" if $verbose > 0 ;
				next;
			}

			## Create the sed command
			my $cmd = "sed -i" ;
			foreach my $ed (@TRANSLATE_LIST)
			{
				$cmd .= " -e '$ed'" ;
			}
			$cmd .= " $file" ;

			#print "CMD: $cmd\n" ;

			$out = `$cmd` ;
		}

	}

	if ($verbose > 1)
	{
		print "\n--EXTENSIONS--\n" ;
		for my $ext (sort keys %extensions)
		{
			print "$ext\n" ;
		}
	}
}



#---------------------------------------------------------------------------------------------------------------

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

mplane-pkg - Process the repositories ready for packaging for Mplane delivery

=head1 SYNOPSIS

mplane-pkg [options]

Options:

       -debug level         set debug level
       -verbose level       set verbosity level
       -help                brief help message
       -man                 full documentation

       -ros                 process only the ros repository

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

Run this script in buildTool/cmake


=cut
