#!/usr/bin/perl -w
#
# Create the sub-directory CMakeLists.txt files for common repository
#

use warnings;
use strict;

use Cwd ;
use File::Copy ;
use File::Spec ;
use File::Glob ;
use File::Basename ;
use File::Path qw/make_path/ ;
use Data::Dumper;
use Getopt::Long;

our $VERSION = "1.03" ;

my $debug = 0;
my $verbose = 0;

	my @src_exclude = ('build-\w+') ;
	my @inc_exclude = @src_exclude ;
	my @virtual_test = (qw/vrh vrs/);
	
	my $inc_dir = "inc" ;
	my $templates_dir = "templates" ;
	my $force ;
	my $help ;
	my $gen_dir = "" ;
	my $gen_path = "" ;
	
	my %defines ;
	my $install_mode = 0 ;
	my ($install_src, $install_dest) ;

	my @cmdLine = @ARGV;				# save for debug
	my $prog = $0 ;
	my $progpath = File::Spec->rel2abs($prog) ;
	$progpath = (File::Spec->splitpath($progpath))[1] ;
	
	if (!GetOptions(
		"help" => \$help,
		"debug=i" => \$debug,
		"verbose!" => \$verbose,
		
		"dir=s" => \$gen_dir,
		"path=s" => \$gen_path,
	    )) 
	{
	    print "Invalid args\n";
	    usage(1) ;
	}
	usage() if ($help) ;

	## Normal mode
	foreach my $repo_path (@ARGV)
	{
		chdir $repo_path or die "Unable to cd to $repo_path : $!" ;
		
		# analyse the files in the repository
		print "Analysing repository : $repo_path\n" if $debug ;
		my %vars = analyse_repo(\@src_exclude, \@inc_exclude) ;
		%vars = (%vars, %defines) ;
		
		print "$vars{repo}\n" ;
		
		print STDERR Data::Dumper->Dump([\%vars], [qw/%vars/]) if $debug ;

		# Output the CMakeList.txt file in each subdir
		foreach my $subdir (sort keys %{$vars{'cmake'}})
		{
			# if a subdirectory has been specified then only generate cmake for that
			if ($gen_dir)
			{
				my $dir = $subdir ;
				$dir =~ s%/.*$%% ;
				next unless ($dir eq $gen_dir) ;
			}
			
			# if a path has been specified then only generate cmake for that
			if ($gen_path)
			{
				next unless ($subdir eq $gen_path) ;
			}
			
			
			# strip off any directory path from sub-directory to leave just the name
			my $target = subdir2target($subdir) ;
			
			my $WIDTH=40 ;
			my $len = length $subdir ;
			my $pad = "." x ($WIDTH-$len) ;
			print "  $subdir$pad: " ;
			chdir "$repo_path/$subdir" or die "Unable to cd to $repo_path/$subdir : $!" ;
			

			# read the CMakeLists file
			my %cmakeVars ;
			if (-f "CMakeLists.txt")
			{
				readCMakeLists($target, $subdir, \%cmakeVars) ;
			print STDERR Data::Dumper->Dump([\%cmakeVars], [qw/%cmakeVars/]) if $debug ;
				
				## Write file if required
				if ( writeCMakeListsRequired($target, $subdir, \%vars, \%cmakeVars) )
				{
					print "** MODIFIED **" ;
					writeMergedCMakeLists($target, $subdir, \%vars, \%cmakeVars) ;
				}
				else
				{
					print "No Change" ;
				}
			}
			else
			{			
				## Write file 
				print "** NEW **" ;
				writeNewCMakeLists($target, $subdir, \%vars) ;
			}
			
			print "\n" ;
		}
		print "\n" ;
	}

	exit(0);


#------------------------------------------------------------------------------------------------------------------------------------
#	add_sources (SOURCES 
#		src/Benchmark.cpp
#	)
#	
#	if (${TARGET} STREQUAL "x86_64")
#	
#		# Load google test
#		include (gtest)
#		
#		# Uses VRH mocks
#		include_directories(${GITDIR}/vrh/test/inc)
#		
#		set(gtest_src 
#			gtest/Benchmark_unittest.cpp
#		)
#		
#		addGtest(Benchmark_GTEST ${gtest_src})
#		
#	# Load cppunit test
#	include (cppunit)
#	
#	# Uses VRH mocks
#	include_directories(${GITDIR}/vrh/test/inc)
#	
#	include_directories(test)
#	set(device_TEST 
#		test/DeviceTestCase.cpp
#		test/DeviceTests.cpp
#	)
#	
#	addCppunitTest(device_UT ${device_TEST})
#			
#		# Add code coverage
#		include (coverage)
#		addCoverage(Benchmark_GTEST)
#		
#	
#	endif (${TARGET} STREQUAL "x86_64")
#
sub writeNewCMakeLists
{
	my ($target, $subdir, $vars_href) = @_ ;

	open my $fh, ">CMakeLists.txt" or die "Unable to write CMakeLists.txt in $subdir" ;
			
			
	print $fh "# Cmake file for $subdir\n\n" ;
	print $fh "add_sources (SOURCES\n" ;
	foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'src'}})
	{
		print $fh "\t$src\n" ;
	}
	print $fh ")\n\n" ;
			
	#	## Cppcheck
	#	include (cppcheck)
	#	addCppcheck(Delay)
	print $fh "## Cppcheck\n" ;
	print $fh "include (cppcheck)\n" ;
	print $fh "addCppcheck($target)\n\n" ;

			
	print $fh "if (\${TARGET} STREQUAL \"x86_64\")\n\n" ;
			
	print $fh "\tset (libs \"\")\n" ;
	if ($vars_href->{'repo'} eq 'common')
	{
		# do nothing
	}
	elsif ($vars_href->{'repo'} eq 'hardware')
	{
		my $repo = $vars_href->{'repo'} ;
		print $fh "\taddRepoLib (libs common)\n" ;
		if ($subdir eq 'common')
		{
			# do nothing
		}
		elsif ($subdir eq 'ETNA')
		{
			print $fh "\taddRepoLib (libs ${repo} common)\n" ;
		}
		elsif ($subdir =~ /^ETNA_/)
		{
			print $fh "\taddRepoLib (libs ${repo} ETNA)\n" ;
		}
	}
	elsif ($vars_href->{'repo'} eq 'services')
	{
		print $fh "\taddRepoLib (libs common)\n" ;
		print $fh "\taddRepoLib (libs hardware common)\n" ;
		if ($subdir eq 'common')
		{
			# do nothing
		}
		elsif ($subdir eq 'ETNA')
		{
			print $fh "\taddRepoLib (libs hardware ETNA)\n" ;
			print $fh "\taddRepoLib (libs services common)\n" ;
		}
		elsif ($subdir =~ /^(ETNA_[^\/]+)/)
		{
			print $fh "\taddRepoLib (libs hardware ETNA)\n" ;
			print $fh "\taddRepoLib (libs hardware ${1})\n" ;
			print $fh "\taddRepoLib (libs services common)\n" ;
			print $fh "\taddRepoLib (libs services ETNA)\n" ;
		}
	}
	elsif ($vars_href->{'repo'} eq 'tif')
	{
		my $repo = $vars_href->{'repo'} ;
		print $fh "\taddRepoLib (libs common)\n" ;
		if ($subdir eq 'common')
		{
			# do nothing
		}
		elsif ($subdir eq 'ETNA')
		{
			print $fh "\taddRepoLib (libs ${repo} common)\n" ;
		}
		elsif ($subdir =~ /^ETNA_/)
		{
			print $fh "\taddRepoLib (libs ${repo} common)\n" ;
			print $fh "\taddRepoLib (libs ${repo} ETNA)\n" ;
		}
		elsif ($subdir =~ /^ETNA\-([^\-]+)\-([^\-\/]+)/)
		{
			my ($customer, $app) = ($1, $2) ;
			print $fh "\taddRepoLib (libs ${repo} common)\n" ;
			print $fh "\taddRepoLib (libs ${repo} ETNA)\n" ;
			print $fh "\taddRepoLib (libs ${repo} ETNA_${app})\n" ;
		}
	}
	print $fh "\n" ;
			

	# google test
	if (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
	{
		print $fh "\t# Load google test\n" ;
		print $fh "\tinclude (gtest)\n\n" ;

		print $fh "\tinclude_directories(gtest)\n" ;
		print $fh "\tset(gtest_src\n" ;
		foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
		{
			print $fh "\t\t$src\n" ;
		}
		print $fh "\t)\n" ;
		print $fh "\taddGtest(${target}_GTEST \"\${libs}\" \${gtest_src})\n\n" ;
	}
			
	# cppunit test
	if (@{$vars_href->{'cmake'}{$subdir}{'test'}})
	{
		print $fh "\t# Load cppunit\n" ;
		print $fh "\tinclude (cppunit)\n\n" ;

		print $fh "\tinclude_directories(test)\n" ;
		print $fh "\tset(test_src\n" ;
		foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'test'}})
		{
			print $fh "\t\t$src\n" ;
		}
		print $fh "\t)\n" ;
		print $fh "\taddCppunitTest(${target}_TEST \"\${libs}\" \${test_src})\n\n" ;
	}
			
	# code coverage
	print $fh "\t# Add code coverage\n" ;
	print $fh "\tinclude (coverage)\n" ;
	if (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
	{
		print $fh "\taddCoverage(${target}_GTEST)\n" ;
	}
	if (@{$vars_href->{'cmake'}{$subdir}{'test'}})
	{
		print $fh "\taddCoverage(${target}_TEST)\n" ;
	}
	print $fh "\n" ;
			
	# memcheck
	print $fh "\t# Add memory leak check\n" ;
	print $fh "\tinclude (valgrind)\n" ;
	if (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
	{
		print $fh "\taddMemcheck(${target}_GTEST)\n" ;
	}
	if (@{$vars_href->{'cmake'}{$subdir}{'test'}})
	{
		print $fh "\taddMemcheck(${target}_TEST)\n" ;
	}
	print $fh "\n" ;
			
			
	print $fh "\nendif (\${TARGET} STREQUAL \"x86_64\")\n\n" ;
			
			
	close $fh ;
}

#------------------------------------------------------------------------------------------------------------------------------------
sub writeMergedCMakeLists
{
	my ($target, $subdir, $vars_href, $cmakeVars_href) = @_ ;

	rename "CMakeLists.txt", "CMakeLists.txt.bak" ;
	open my $fh, ">CMakeLists.txt" or die "Unable to write CMakeLists.txt in $subdir" ;
			
	foreach my $src (@{$cmakeVars_href->{'pre-sources'}})
	{
		print $fh "$src\n" ;
	}
	print $fh "add_sources (SOURCES\n" ;
	foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'src'}})
	{
		print $fh "\t$src\n" ;
	}
	print $fh ")\n\n" ;
			

	# google test
	if (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
	{
		if (! %{$cmakeVars_href->{'gtest'}} )
		{
			print $fh "\n\t# Load google test\n" ;
			print $fh "\tinclude (gtest)\n\n" ;
			
			print $fh "\tinclude_directories(gtest)\n\n" ;
			
		}
		
		foreach my $src (@{$cmakeVars_href->{'pre-gtest'}})
		{
			print $fh "$src\n" ;
		}
		print $fh "\tset(gtest_src\n" ;
		foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
		{
			print $fh "\t\t$src\n" ;
		}
		foreach my $src (@{$cmakeVars_href->{'extra-gtest'}})
		{
			print $fh "$src\n" ;
		}
		print $fh "\t)\n" ;
		
		if (! %{$cmakeVars_href->{'gtest'}} )
		{
			print $fh "\taddGtest(${target}_GTEST \"\${libs}\" \${gtest_src})\n\n" ;
		}
		foreach my $src (@{$cmakeVars_href->{'post-gtest'}})
		{
			print $fh "$src\n" ;
		}

	}
			
	# cppunit test
	if (@{$vars_href->{'cmake'}{$subdir}{'test'}})
	{

		if (! %{$cmakeVars_href->{'test'}} )
		{
			print $fh "\n\t# Load cppunit\n" ;
			print $fh "\tinclude (cppunit)\n\n" ;

			print $fh "\tinclude_directories(test)\n\n" ;
		}
		
		foreach my $src (@{$cmakeVars_href->{'pre-test'}})
		{
			print $fh "$src\n" ;
		}
		print $fh "\tset(test_src\n" ;
		foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'test'}})
		{
			print $fh "\t\t$src\n" ;
		}
		foreach my $src (@{$cmakeVars_href->{'extra-test'}})
		{
			print $fh "$src\n" ;
		}
		print $fh "\t)\n" ;
		
		if (! %{$cmakeVars_href->{'test'}} )
		{
			print $fh "\taddCppunitTest(${target}_TEST \"\${libs}\" \${test_src})\n\n" ;
		}
		foreach my $src (@{$cmakeVars_href->{'post-test'}})
		{
			print $fh "$src\n" ;
		}
		
	}
			
	foreach my $src (@{$cmakeVars_href->{'pre-end'}})
	{
		print $fh "$src\n" ;
	}
			
			
	close $fh ;
}



#------------------------------------------------------------------------------------------------------------------------------------
sub readCMakeLists
{
	my ($target, $subdir, $vars_href) = @_ ;

	for (keys %$vars_href)
    {
        delete $vars_href->{$_};
    }
    
    $vars_href->{'pre-sources'} = [] ;
    $vars_href->{'sources'} = {} ;
    $vars_href->{'extra-sources'} = [] ;
    $vars_href->{'pre-gtest'} = [] ;
    $vars_href->{'gtest'} = {} ;
    $vars_href->{'extra-gtest'} = [] ;
    $vars_href->{'post-gtest'} = [] ;
    $vars_href->{'pre-test'} = [] ;
    $vars_href->{'test'} = {} ;
    $vars_href->{'extra-test'} = [] ;
    $vars_href->{'post-test'} = [] ;
    $vars_href->{'pre-end'} = [] ;
    
	if (-f "CMakeLists.txt")
	{
		open my $fh, "<CMakeLists.txt" or die "Unable to read CMakeLists.txt in $subdir" ;
				
		#	add_sources (SOURCES 
		#		src/Benchmark.cpp
		#	)
		
		my $state = "" ;
		my $prev_state = "" ;
		
		my @pre = () ;
		my $line ;
		while (defined($line=<$fh>))
		{
			# skip spaces, comments
			chomp $line ;
			my $orig_line = $line ;
			$line =~ s/^\s+// ;
			$line =~ s/\s+$// ;
			$line =~ s/#.*$// ;
			
			unless ($line)
			{
				# save into the state as an extra, or prefix the state contents with these lines
				if ($state)
				{
					push @{ $vars_href->{"extra-${state}"} }, $orig_line ;
				}
				else
				{
					push @pre, $orig_line ;
				}
				next ;
			}
			
			# check state
			if ($line =~ /add_sources\s*\(SOURCES/)
			{
				$state = "sources" ;
				$prev_state = $state ;
				$vars_href->{'pre-sources'} = [@pre] ;
				@pre = () ;
				next ;
			}
			elsif ($line =~ /set\s*\(([^_]+)_src/)
			{
				$state = "$1" ;
				$prev_state = $state ;
				$vars_href->{"pre-${state}"} = [@pre] ;
				@pre = () ;
				next ;
			}
			
			# check for state end
			if ($state)
			{
				if ($line =~ /\)/)
				{
					$state = "" ;
					next ;
				}
			}

			# skip to next if not currently in a state
			if (!$state)
			{
				# Check for test add
				if ($line =~ /addGtest/)
				{
					push @{ $vars_href->{"post-${prev_state}"} }, $orig_line ;
					next ;
				}
				elsif ($line =~ /addCppunitTest/)
				{
					push @{ $vars_href->{"post-${prev_state}"} }, $orig_line ;
					next ;
				}
				
				push @pre, $orig_line ;
				next ;
			}
			
			# skip if name contains a variable
			if ($line =~ /\$/)
			{
				push @{ $vars_href->{"extra-${state}"} }, $orig_line ;
				next ;
			}
			
			# store name
			$vars_href->{$state}{$line}++ ;
		}
				
		close $fh ;
		
		if (@pre)
		{
			$vars_href->{'pre-end'} = [@pre] ;
		}
	}
	
	
}


#------------------------------------------------------------------------------------------------------------------------------------
# See if something has changed 
sub writeCMakeListsRequired
{
	my ($target, $subdir, $vars_href, $cmakeVars_href) = @_ ;

	# check source
	foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'src'}})
	{
		if (!exists($cmakeVars_href->{'sources'}{$src}))
		{
			print "CHANGE: Source $src not found in existing file\n" if $debug ;
			return 1 ;
		}
	}
	
	# check gtest
	if (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
	{
		foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'gtest'}})
		{
			if (!exists($cmakeVars_href->{'gtest'}{$src}))
			{
				print "CHANGE: gtest $src not found in existing file\n" if $debug ;
				return 1 ;
			}
		}
	}
			
	# cppunit test
	if (@{$vars_href->{'cmake'}{$subdir}{'test'}})
	{
		foreach my $src (@{$vars_href->{'cmake'}{$subdir}{'test'}})
		{
			if (!exists($cmakeVars_href->{'test'}{$src}))
			{
				print "CHANGE: test $src not found in existing file\n" if $debug ;
				return 1 ;
			}
		}
	}

	
	return 0 ;
}

#------------------------------------------------------------------------------------------------------------------------------------
# convert a directory name to a variable
sub subdir2target
{
	my ($subdir) = @_ ;
	
	# get string
	my $target = basename($subdir) ;
	
	# replace '-'
	$target =~ s%\-%%g ;

	return $target ;
}


#------------------------------------------------------------------------------------------------------------------------------------
sub analyse_repo
{
	my ($src_exclude_aref, $inc_exclude_aref) = @_ ;
	
	my $topdir = File::Spec->rel2abs(".") ;
	my $repo = $topdir ;
	$repo =~ s%.*/([^/]+)$%$1% ;
	my $REPO = uc $repo ;
	
	my $repo_var = automakeVar($repo) ;
	my $REPO_VAR = automakeVar($REPO) ;
	
	my %vars = (
		## Simple vars
		'repo'		=> $repo,
		'REPO'		=> $REPO,
		'repofile'	=> "",
		
		## Multi-line
		'includes'	=> "",
		'libsrc'	=> "",
		'binsrc'	=> "",
		'unittest'	=> "",
		'unitgtest'	=> "",
		'testsrc'	=> "",
		'gtestsrc'	=> "",
		'cppcheck'	=> "",
		'cppunit'	=> "",
		'gtest'		=> "",
		'memcheck'	=> "",
		'threadcheck'=> "",
		'testlib'	=> "",
		'applications-src'	=> "",
		'fpga-src'	=> "",
		
		## Internal use
		'_commonLib'=> "",
		'@libs'		=> [],
		'%libs'		=> {},
		'@testlibs'	=> [],
		'%boards'	=> {},	# list of board names found in repo (with src/ content)
		'%apps'		=> {},	# list of customer-app names found in repo (with src/ content)
		'%binapps'	=> {},	# list of customer-app names found in repo (with bin-src/ content)
		'%applications'	=> {},	# list of customer-app names found in repo (with bin-src/ content). Under each is a list of the applications
		'%appList'	=> {},	# List of all apps
		'%fpgas'	=> {},
		
		
		################
		'cmake'		=> {},
	);
	
	
	## -- Looking for inc dirs ---------------------------------
	my @inc = glob_files("inc", $inc_exclude_aref, 0, 4) ;
	my %inc ;
	foreach my $incdir (@inc)
	{
		my $path = File::Spec->rel2abs($incdir) ;
		my $dir = File::Spec->abs2rel($path, $topdir) ;
		$dir =~ s%/$%% ;
		
		$inc{$dir} = 1 ;
	}
	
	
	#	COMMON_INCLUDE = \
	#	  -I$(srcdir)/../common/inc \
	#	  -I$(srcdir)/../vrh/inc \ 
	#	  -I$(srcdir)/../vrs/inc 
	
	foreach my $dir (sort keys %inc)
	{
		$vars{'includes'} .= " \\\n\t-I\$(srcdir)/../$repo/$dir" ;
		next if $dir eq 'inc' ;
		
		## cmake
		my $name = dir2var($dir) ;
		$name =~ s%/inc$%% ;
		newCmake($name, \%vars) ;
		push @{ $vars{'cmake'}{$name}{'inc'} }, 'inc' ; 
	}
	
	
	## -- Looking for source files ---------------------------------
	my $got_common_dir = 0 ;
	my %src ;
	find_src_files(\%src, $topdir, "src", $src_exclude_aref, \$got_common_dir, \%vars) ;
	
	# also in subdirs under src
	find_sub_src_files(\%src, $topdir, "src", $src_exclude_aref, 4) ;
	
	#	## Library Source
	#	DATATYPE_SRC = \
	#	datatype/src/Frequency.cpp \
	#	datatype/src/Power.cpp \
	#	datatype/src/SString.cpp 
	foreach my $dir (sort keys %src)
	{
		my $srcname = uc dir2var($dir) ; 
		$vars{'libsrc'} .= "$srcname = " ;
		foreach my $path (@{$src{$dir}})
		{
			$vars{'libsrc'} .= " \\\n\t$path" ;
		}
		$vars{'libsrc'} .= "\n\n" ;
		
		## cmake
		my $name = dir2var($dir) ;
		$name =~ s%/src$%% ;
		newCmake($name, \%vars) ;
		foreach my $path (@{$src{$dir}})
		{
			$path =~ s%^$name/%% ;
			push @{ $vars{'cmake'}{$name}{'src'} }, $path ; 
		}
	}
	
	# For any repos that have dirs 'common', 'ETNA', 'HOST' etc. then we need
	# to create helper libs 
	my %top_dirs ;
	my @checklibs ;
	my @libs ;
	if ($got_common_dir)
	{
		#	libETNAhardware_la_SOURCES =  \
		#		$(ETNA_CARRIER_SRC) \
		#		$(ETNA_FPGA_SRC) \
		#		$(ETNA_RADIO_SRC) 
		#
		foreach my $dir (sort keys %src)
		{
			my $top = $dir ;
			$top =~ s%^([^/]+)/.*%$1% ;
			
			my $srcname = uc dir2var($dir) ; 
			$top_dirs{$top} ||= [] ;
			push @{ $top_dirs{$top} }, $srcname ;
		}
		
		#	libETNAhardware_la_SOURCES =  \
		#		$(ETNA_CARRIER_SRC) \
		#		$(ETNA_FPGA_SRC) \
		#		$(ETNA_RADIO_SRC) 
		#	
		#	libHOSThardware_la_SOURCES =  \
		#		$(HOST_CARRIER_SRC) \
		#		$(HOST_RADIO_SRC) 
		#	
		#	libCOMMONhardware_la_SOURCES =  \
		#		$(COMMON_ADC_SRC) \
		#		$(COMMON_ATTENUATOR_SRC) \
		#
		$vars{'libsrc'} .= "## Helper libs\n" ;
		foreach my $top (sort keys %top_dirs)
		{
			my $TOP = automakeVar(uc $top) ;
			$vars{'libsrc'} .= "lib${TOP}${repo_var}_la_SOURCES =" ;
			foreach my $var (@{ $top_dirs{$top} })
			{
				$vars{'libsrc'} .= " \\\n\t\$($var)" ;
			}
			$vars{'libsrc'} .= "\n\n" ;
			
			$TOP = uc $top ;
			my $lib = toLibName(${TOP}, ${repo}) ;
			push @libs, $lib ;
			
			my $base = libBaseName($lib, $repo) ;
			if ($base)
			{
				$vars{'%libs'}{$base} = $lib ;
			}
			
			if ($TOP eq 'COMMON')
			{
				$vars{'_commonLib'} = $lib ;
			}
			
			## Save board & app names
			my ($board, $app) = getBoardApp($base) ;
			$vars{'%boards'}{$board} = 1 if $board ;
			$vars{'%apps'}{$app} = 1 if $app ;
		}
		
		#	libETNAcheck_la_SOURCES =  \
		#		$(libETNAhardware_la_SOURCES) \
		#		$(libCOMMONhardware_la_SOURCES)
		#	
		#	libHOSTcheck_la_SOURCES =  \
		#		$(libHOSThardware_la_SOURCES) \
		#		$(libCOMMONhardware_la_SOURCES)
		#
		$vars{'libsrc'} .= "## Helper test libs\n" ;
		foreach my $top (sort keys %top_dirs)
		{
			next if $top eq 'common' ;
			
			my $TOP = automakeVar(uc $top) ;
			$vars{'libsrc'} .= "lib${TOP}check_la_SOURCES = \\\n" ;
			$vars{'libsrc'} .= "	\$(lib${TOP}${repo_var}_la_SOURCES) \\\n" ;
			$vars{'libsrc'} .= "	\$(libCOMMON${repo_var}_la_SOURCES)\n" ;
			
			$TOP = uc $top ;
			push @checklibs, toLibName(${TOP}, "check") ;
		}
		$vars{'libsrc'} .= "\n\n" ;
		
	}
	else
	{
		## Skip if no source files
		if (keys %src)
		{
			#	libhardware_la_SOURCES = \
			#	$(DATATYPE_SRC) \
			$vars{'libsrc'} .= "lib${repo_var}_la_SOURCES = " ;
			foreach my $dir (sort keys %src)
			{
				my $srcname = uc dir2var($dir) ; 
				$vars{'libsrc'} .= " \\\n\t\$($srcname)" ;
			}
		
			my $lib = toLibName("", ${repo}) ;
			push @libs, $lib ;
		}
	}
	
	$vars{'libsrc'} .= "\n\n" ;
	$vars{'libsrc'} .= "NOINST_LIBS = " ;
	foreach my $lib (@libs)
	{
		$vars{'libsrc'} .= "\\\n\t$lib" ;
	}
	$vars{'libsrc'} .= "\n\n" ;
	$vars{'libsrc'} .= "CHECK_LIBS = " ;
	foreach my $lib (@checklibs)
	{
		$vars{'libsrc'} .= "\\\n\t$lib" ;
	}
	
	$vars{'@libs'} = [ @libs ] ;
	$vars{'@testlibs'} = [ @checklibs ] ;
	
	
	## -- Looking for bin-src files ---------------------------------
	my %binsrc ;
	find_src_files(\%binsrc, $topdir, "bin-src", $src_exclude_aref, \$got_common_dir, \%vars) ;
	
	# also in subdirs under bin-src
	find_sub_src_files(\%binsrc, $topdir, "bin-src", $src_exclude_aref, 4) ;
	
	#	## Library Source
	#	GENTOOL_BIN_SRC = \
	#    common/gentool/bin-src/Path.cpp \
	#    common/gentool/bin-src/TemplateFile.cpp \
	#    common/gentool/bin-src/TifXml.cpp \
	#    common/gentool/bin-src/TifData.cpp 
	foreach my $dir (sort keys %binsrc)
	{
		my $srcname = uc dir2var($dir) ; 
		$vars{'binsrc'} .= "$srcname = " ;
		foreach my $path (@{$binsrc{$dir}})
		{
			$vars{'binsrc'} .= " \\\n\t$path" ;
		}
		$vars{'binsrc'} .= "\n\n" ;
		
		## Save the 'app' name (if exists) for this program
		my ($board, $appname) = getBoardApp($dir, 1) ;
		if ($appname)
		{
			$vars{'%binapps'}{$appname} = 1 ;
			
			## Also save the actual application name - use the name just above bin-src
			foreach my $path (@{$binsrc{$dir}})
			{
				if ($path =~ m%/([^/]+)/bin\-src/%)
				{
					my $application = $1 ;
					$vars{'%applications'}{$appname} ||= {} ;
					$vars{'%applications'}{$appname}{$application} ||= [] ;
					
					if (!exists($vars{'%appList'}{$application}))
					{
						push @{$vars{'%applications'}{$appname}{$application} }, $path ;
					}
				}		
			}

			foreach my $application (keys %{$vars{'%applications'}{$appname}})
			{
				if (!exists($vars{'%appList'}{$application}))
				{
					$vars{'applications-src'} .= "${application}_SRC = " ;
					foreach my $path (@{$vars{'%applications'}{$appname}{$application}})
					{
						$vars{'applications-src'} .= " \\\n\t$path" ;
					}
					$vars{'applications-src'} .= "\n\n" ;

					$vars{'%appList'}{$application} = 1 ;
				}
			}
		}
	}
	
	
	## -- CPPUNIT Test files ---------------------------------
	my %test ;
	find_src_files(\%test, $topdir, "test", $src_exclude_aref) ;
	
	# also in subdirs under test
	find_sub_src_files(\%test, $topdir, "test", $src_exclude_aref) ;

	
	
	#	## Unit Tests
	#	
	#	check_PROGRAMS = \
	#	datatype/UT \

	foreach my $dir (sort keys %test)
	{
		my $testname = uc dir2var($dir) ; 
		$vars{'unittest'} .= " \\\n\t${dir}/UT\$(EXEEXT)" ;
	}
	
	#	datatype_UT_SOURCES = \
	#	datatype/test/DataTypeTests.cpp \
	#	datatype/test/SStringTestCase.cpp
	#	datatype_UT_LDFLAGS = -lcppunit
	foreach my $dir (sort keys %test)
	{
		my $testname = dir2var("${dir}") . "_UT" ; 
		$vars{'testsrc'} .= "${testname}_SOURCES = " ;
		foreach my $path (@{$test{$dir}})
		{
			$vars{'testsrc'} .= " \\\n\t$path" ;
		}
		$vars{'testsrc'} .= "\n" ;
		$vars{'testsrc'} .= "${testname}_LDFLAGS = -lcppunit -lrt \$(AM_LDFLAGS)\n" ;
		
		my $top = $dir ;
		$top =~ s%^([^/]+)/.*%$1% ;
		my $TOP = automakeVar(uc $top) ;
		
		$vars{'testsrc'} .= "${testname}_LDADD = \$(${testname}_LIBS) \$(${TOP}_ALL_LIB) \$(${TOP}_LDADD) \$(LDADD) \$(CPPUNIT_LIB)\n" ;
		
		$vars{'testsrc'} .= "\n" ;

		
		## cmake
		my $name = dir2var($dir) ;
		$name =~ s%/test$%% ;
		newCmake($name, \%vars) ;
		foreach my $path (@{$test{$dir}})
		{
			$path =~ s%^$name/%% ;
			push @{ $vars{'cmake'}{$name}{'test'} }, $path ; 
		}


	}
	
	## -- Google Test files ---------------------------------
	my %gtest ;
	find_src_files(\%gtest, $topdir, "gtest", $src_exclude_aref) ;

	# also in subdirs under gtest
	find_sub_src_files(\%gtest, $topdir, "gtest", $src_exclude_aref) ;

	
	#	## Unit Tests
	#	
	#	check_PROGRAMS = \
	#	datatype/UT \

	foreach my $dir (sort keys %gtest)
	{
		my $testname = uc dir2var($dir) ; 
		$vars{'unitgtest'} .= " \\\n\t${dir}/UT\$(EXEEXT)" ;
	}
	
	#	datatype_UT_SOURCES = \
	#	datatype/test/DataTypeTests.cpp \
	#	datatype/test/SStringTestCase.cpp
	#	datatype_UT_LDFLAGS = -lcppunit
	foreach my $dir (sort keys %gtest)
	{
		my $testname = dir2var("${dir}") . "_UT" ; 
		$vars{'gtestsrc'} .= "${testname}_SOURCES = " ;
		foreach my $path (@{$gtest{$dir}})
		{
			$vars{'gtestsrc'} .= " \\\n\t$path" ;
		}
		$vars{'gtestsrc'} .= "\n" ;
		$vars{'gtestsrc'} .= "${testname}_LDFLAGS = -lrt \$(AM_LDFLAGS)\n" ;
		
		my $top = $dir ;
		$top =~ s%^([^/]+)/.*%$1% ;
		my $TOP = automakeVar(uc $top) ;
		
		$vars{'gtestsrc'} .= "${testname}_LDADD = \$(${testname}_LIBS) \$(${TOP}_ALL_LIB) \$(${TOP}_LDADD) \$(LDADD) \$(GTEST_LIB)\n" ;
		
		$vars{'gtestsrc'} .= "\n" ;


		
		## cmake
		my $name = dir2var($dir) ;
		$name =~ s%/gtest$%% ;
		newCmake($name, \%vars) ;
		foreach my $path (@{$gtest{$dir}})
		{
			$path =~ s%^$name/%% ;
			push @{ $vars{'cmake'}{$name}{'gtest'} }, $path ; 
		}

	}
	
	## -- Test Library Files ---------------------------------
	my %testlibsrc ;
	find_src_files(\%testlibsrc, $topdir, "test-lib-*/src", $src_exclude_aref) ;

	# also in subdirs under gtest
#	find_sub_src_files(\%testlibsrc, $topdir, "test-lib-*/src", $src_exclude_aref) ;

	if ($debug)
	{
		print STDERR "test-lib files: ", Data::Dumper->Dump([\%testlibsrc], [qw/%testlibsrc/]) ;
	}

	# post-process names to just get the library name
	my %testlib ;
	foreach my $path (keys %testlibsrc)
	{
		my $aref = $testlibsrc{$path} ;
		
		$path =~ s%^.*/test\-lib\-([^/]+)/.*$%$1% ;
		
		$testlib{$path} ||= [] ;
		push @{ $testlib{$path} }, @$aref ;
	}

	if ($debug)
	{
		print STDERR "Processed test-lib files: ", Data::Dumper->Dump([\%testlib], [qw/%testlib/]) ;
	}

	
	foreach my $libname (keys %testlib)
	{
		my $lib = toLibName("", $libname) ;
		$vars{'testlib'} .= "noinst_LTLIBRARIES += $lib\n" ;

		my $libvar = automakeVar(${lib}) ;
		$vars{'testlib'} .= "${libvar}_SOURCES = " ;
		foreach my $src (@{$testlib{$libname}})
		{
			$vars{'testlib'} .= "\\\n\t$src " ;
		}
		$vars{'testlib'} .= "\n" ;
	}

	## -- CPPCHECK files ---------------------------------

	foreach my $dir (sort keys %src)
	{
		my $srcname = uc dir2var($dir) ; 
		
		# get path to level above src
		my $path = $dir ;
		$path =~ s%/src$%% ;
		
		$vars{'cppcheck'} .= "${path}/cppcheck.xml: \$($srcname)\n" ;
	}

	## -- CPPUNIT files ---------------------------------

	foreach my $dir (sort keys %test)
	{
		my $testname = uc dir2var($dir) ; 
		$vars{'cppunit'} .= "${dir}/cppunit.xml: ${dir}/UT\$(EXEEXT)\n" ;
	}

	## -- GTEST files ---------------------------------

	foreach my $dir (sort keys %gtest)
	{
		my $testname = uc dir2var($dir) ; 
		$vars{'gtest'} .= "${dir}/gtest.xml: ${dir}/UT\$(EXEEXT)\n" ;
	}

	## -- MEMCHECK files ---------------------------------

	foreach my $dir (sort keys %test)
	{
		my $testname = uc dir2var($dir) ; 
		$vars{'memcheck'} .= "${dir}/UT.memcheck: ${dir}/UT\$(EXEEXT) ${dir}/UT.memcheck.xml\n" ;
	}

	## -- FPGA files ---------------------------------

	my %fpga ;
	find_fpga_files(\%fpga, $topdir, "images") ;
	

	## -- DONE ---------------------------------
	print " * DONE\n" if $debug ;
	
	return %vars ;

}

#------------------------------------------------------------------------------------------------------------------------------------
sub newCmake
{
	my ($name, $vars_href) = @_ ;
	$vars_href->{'cmake'}{$name} ||= {
		'src' 	=> [],
		'gtest'	=> [],
		'test'	=> [],
		'inc'	=> [],
	} ;
	
}

#------------------------------------------------------------------------------------------------------------------------------------
sub find_src_files
{
	my ($src_href, $topdir, $dirname, $src_exclude_aref, $got_common_dir_ref, $vars_href) = @_ ;

	my @src = glob_files("$dirname/*.cpp", $src_exclude_aref) ;
	foreach my $srcfile (@src)
	{
		# set the single source file used to ensure autoconf locates the src directory
		if ($vars_href)
		{
			$vars_href->{'repofile'} = $srcfile unless $vars_href->{'repofile'} ; 
		}
		
		my $path = File::Spec->rel2abs($srcfile) ;
		$path = File::Spec->abs2rel($path, $topdir) ;
		my $dir = (File::Spec->splitpath($path))[1] ;
		$dir =~ s%/$%% ;
		
		# check top dir - if it's 'common' then adjacent dirs are things like 'ETNA', 'HOST' etc
		# and need to be treated differently (e.g. in hardware repo)
		my $top = $dir ;
		$top =~ s%^([^/]+)/.*%$1% ;
		if ($got_common_dir_ref)
		{
			++$$got_common_dir_ref if ($top eq 'common') ;
		}
	
		$src_href->{$dir} ||= [] ;
		push @{ $src_href->{$dir} }, $path ;
	}
}

#------------------------------------------------------------------------------------------------------------------------------------
sub find_sub_src_files
{
	my ($src_href, $topdir, $dirname, $src_exclude_aref, $levels) = @_ ;

	$levels ||= 1 ;
	my %src ;
	my @src ;
	foreach my $level (1..$levels)
	{
		my $dirs = "*/" x $level ; 
		my @level_src = glob_files("${dirname}/${dirs}*.cpp", $src_exclude_aref) ;
		push @src, @level_src ;
	}
	foreach my $srcfile (@src)
	{
		my $path = File::Spec->rel2abs($srcfile) ;
		$path = File::Spec->abs2rel($path, $topdir) ;
		my $dir = (File::Spec->splitpath($path))[1] ;
		$dir =~ s%/$%% ;
		
		# dir is now of the form:
		#
		# ETNA/carrier/src/CarrierHardware
		#
		# Put this file into ETNA/carrier/src
		#
		$dir =~ s%/$dirname/.*%/$dirname% ;
		
		$src_href->{$dir} ||= [] ;
		push @{ $src_href->{$dir} }, $path ;
	}
}


#------------------------------------------------------------------------------------------------------------------------------------
sub find_fpga_files
{
	my ($fpga_href, $topdir, $dirname, $levels) = @_ ;

	$levels ||= 1 ;

	# Get list of all fpga tarballs
	my @tgz ;
	foreach my $level (1..$levels)
	{
		my $dirs = "*/" x $level ; 
		my @level_tgz = glob("${dirname}/${dirs}*.tgz") ;
		push @tgz, @level_tgz ;
	}

	# Ensure each tarball has an md5 (otherwise drop it)
	foreach my $tgzfile (@tgz)
	{
		## check md5
		my $md5file = "$tgzfile.md5" ;
		next if ! -f $md5file ;
		
		## Get full path
		my $path = File::Spec->rel2abs($tgzfile) ;
#		$path = File::Spec->abs2rel($path, $topdir) ;
		
		## Get directory name just below $dirname
		my $dir = (File::Spec->splitpath($path))[1] ;
		$dir =~ s%.*$dirname/([^/]+).*%$1% ;
		
#		print STDERR "[$dir] $path\n" ;

		# Save path		
		$fpga_href->{$dir} ||= [] ;
		push @{ $fpga_href->{$dir} }, $path ;
	}

	if ($debug)
	{
		print STDERR "FPGA ", Data::Dumper->Dump([$fpga_href], [qw/$fpga_href/]) ;
	}
}


#------------------------------------------------------------------------------------------------------------------------------------
sub glob_files
{
	my ($spec, $exclude_aref, $start_levels, $stop_levels) = @_ ;
	my @src = () ;
	$exclude_aref ||= [] ;
	
	# ignore any marked as SKIP
	push @$exclude_aref, 'SKIP' ;
	
	$start_levels = 1 unless defined($start_levels) ;
	$stop_levels = 3 unless defined($stop_levels) ;
	
	my @levels = () ;
	for my $numlevel ($start_levels..$stop_levels)
	{
		my $levelstr = "" ;
		foreach my $level (1..$numlevel)
		{
			$levelstr .= "*/" ;
		}
		push @levels, $levelstr ;
	}
	
	foreach my $top (@levels)
	{
		my @files = glob("$top$spec") ;
		if ($debug)
		{
			print STDERR "Searching: $top$spec\n" ;
			print STDERR " * @files\n" ;
		}

		# check for exclusions
		foreach my $file (@files)
		{
			my $ok=1 ;
			foreach my $exclude (@$exclude_aref)
			{
				if ($file =~ /$exclude/)
				{
					$ok = 0 ;
					last ;
				}
			}
			
			if ($ok)
			{
				push @src, $file ;
			}
		}
	}

	print STDERR "GLOB($spec): @src\n" if $debug ;

	return @src ;	
}

#------------------------------------------------------------------------------------------------------------------------------------
sub filter_file
{
	my ($atfile, $destfile, $vars_href, $uses_href, $vtest_aref) = @_ ;
	
	my $tempfile = "$destfile.new" ;
	open my $in_fh, "<$atfile" or die "Error: Unable to read $atfile : $!" ;
	open my $out_fh, ">$tempfile" or die "Error: Unable to write $tempfile : $!" ;
	
	print " * $destfile\n" ;
	
	my @lines = filter_file_contents($in_fh, $atfile, $vars_href, $uses_href, 0, $vtest_aref) ;
		
	# output line(s)
	print $out_fh @lines ;

	close $in_fh ;
	close $out_fh ;
	
	## Now see if the new file is different from the existing file
	my $diff = system("diff", "-q", $tempfile, $destfile) ;
	if ($diff)
	{
		# replace old file with new
		system("mv", $tempfile, $destfile) ;
	}
	else
	{
		# skip new
		unlink $tempfile ;
	}
	
}

#------------------------------------------------------------------------------------------------------------------------------------
sub filter_file_contents
{
	my ($in_fh, $atfile, $vars_href, $uses_href, $level, $vtest_aref) = @_ ;
	
	$level ||= 0 ;
	my @lines = () ;
	
	if ($level > 10)
	{
		print STDERR "ERROR: Too many levels of recursion (including same file?)\n" ;
		exit 1 ;
	}
	
	my $topdir = File::Spec->rel2abs(".") ;
	my $repo = $topdir ;
	$repo =~ s%.*/([^/]+)$%$1% ;
	my $REPO = uc $repo ;

	my %setVars ;
	my $line ;
	while(defined($line = <$in_fh>))
	{
		chomp $line ;
		
		print STDERR "<$line>\n" if $debug >=2 ;
		
		# replace include
		if ($line =~ /\@include\(\s*(\S+)\s*\)\@/)
		{
			my $filepath = "$progpath/$inc_dir/$1" ;
			open my $fh, "<$filepath" or die "Error: Unable to read template from $filepath : $!" ;
			my @inc_lines = filter_file_contents($fh, $atfile, $vars_href, $uses_href, $level+1, $vtest_aref) ;
			close $fh ;
			
			push @lines, @inc_lines ;
			next ;
		}
		
		# skip @uses@ (already handled)
		if ($line =~ /\@uses\(\s*(\S+)\s*\)\@/)
		{
			next ;	
		}	
			
		# handle megalibs
		if ($line =~ /\@megalibs\(\s*([^)]*)\s*\)\@/)
		{
			my ($options) = $1 ;
			my %options = (
				'extralibs'	=> "",
				'mode'		=> "",
			) ;
			
			while ($options =~ m/(\w+)=(\S+)/g)
			{
				$options{$1} = $2 ;
			}
			
			print STDERR " * * Expanding megalibs ($options)\n" ;
			
			$line = expand_megalibs($vars_href, $uses_href->{$atfile}{'uses'}, $uses_href->{$atfile}{'order'}, 
				\%setVars, \%options, $vtest_aref) ;
		}	
			
		# handle automake conditional definition:
		# @amcond(foreach=%boards var=BOARD_IS_@forvar@ testvar=$BUILD_BOARD testval=@forvar@)@
		#
		if ($line =~ /\@amcond\(\s*([^)]*)\s*\)\@/)
		{
			my ($options) = $1 ;
			my %options = (
				'foreach'	=> "",
				'var'		=> "",
				'testvar'	=> "",
				'testval'	=> "",
			) ;
			
			while ($options =~ m/(\w+)=(\S+)/g)
			{
				$options{$1} = $2 ;
			}
			
			print STDERR " * * Expanding amcond ($options)\n" ;
			
			$line = expand_amcond($vars_href, $uses_href, \%options) ;
		}	
			
		# handle use includes
		if ($line =~ /\@useincs\@/)
		{
			print STDERR " * * Expanding uses includes\n" ;
			
			$line = expand_uses_incs($vars_href, $uses_href->{$atfile}{'uses'}, $uses_href->{$atfile}{'order'}, 
				\%setVars) ;
		}	
			
		# handle applications list
		if ($line =~ /\@applications\-list\@/)
		{
			$line = expand_applications_list($vars_href, $uses_href, \%setVars) ;
		}	
			
		# handle applications selection
		if ($line =~ /\@applications\-select\@/)
		{
			$line = expand_applications_select($vars_href, $uses_href, \%setVars) ;
		}	
			
		## Check for any unknown variables
		while ($line =~ m/\@([\w\-\:\.]+)\@/g )
		{
			if (!exists($vars_href->{$1}) || !defined($vars_href->{$1}))
			{
				print STDERR "ERROR: Template file uses variable '$1' but it is not defined\n" ;
				exit 1 ;
			}
		}
	
		# Replace any variables
		$line =~ s/\@([\w\-\:\.]+)\@/$vars_href->{$1}/g ;
		
		# Check for variable settings
		if ($line =~ /^\s*(\w+)\s*=\s*(\S+)/)
		{
			$setVars{$1} = $2 ;
		}

		print STDERR "FINAL: <$line>\n" if $debug >=3 ;
		
		# output line(s)
		push @lines, "$line\n" ;
	}

	return @lines ;
}


#------------------------------------------------------------------------------------------------------------------------------------
sub expand_megalibs
{
	my ($vars_href, $uses_href, $uses_order_aref, $setVars_href, $options_href, $vtest_aref) = @_ ;
	
	my $megalib_vars = "" ;
	my $content = "" ;
	my @megalibs = () ;
	
	# merge the used repo info into this one
	foreach my $used (@$uses_order_aref)
	{
		foreach my $var (qw/%boards %apps/)
		{
			$vars_href->{$var} = { %{$vars_href->{$var}}, %{$uses_href->{$used}{$var}} } ;
		}
	}
	
#print STDERR "Expand megalibs : ", Data::Dumper->Dump([$vars_href->{'%boards'}, $vars_href->{'%apps'}], [qw/%boards %apps/]) ;	
	
	# Get any extra libs to add
	my @extralibs = split(/,/, $options_href->{'extralibs'}) ;
	
	# list of libraries in this repo
	my @repoLibs = @{$vars_href->{'@libs'}} ;
	
	# In application mode, we need to create a megalib for all possible variants of application
	if ($options_href->{'mode'} eq 'applications')
	{
		# clear out any other libs - applications repo should only be using the libs from other repos
		@repoLibs = () ;
		
		# create list of libs that will drive the megalib creation
		my %apps = (%{$vars_href->{'%apps'}}, %{$vars_href->{'%binapps'}}) ;
		foreach my $app (sort keys %apps)
		{
			foreach my $board (sort keys %{$vars_href->{'%boards'}})
			{
				my $base = "$board-$app" ;
				push @repoLibs, toLibName($base, $vars_href->{'repo'}) ;
			}
		}
	}
	
	
	# Work through the libs in this repo
	foreach my $repoLib (@repoLibs)
	{
		# Get the base name of the lib:
		# lib<BASE><repo>.la
		my $base = libBaseName($repoLib, $vars_href->{'repo'}) ;
		next unless $base ;
		my $BASE= uc $base ;
		
		# Create megalib(s)
		my $megalib = toLibName($base, "all") ;
		my $uses_vtest = addMegalib($megalib, $vars_href->{'repo'}, $repoLib, $base, \$content, \@megalibs, 
			\@extralibs, $vars_href, $uses_href, $uses_order_aref, [], $vtest_aref) ;
		
		# create a variable setting for this megalib - but only do this if user hasn't already specified one
		my $var = automakeVar("${BASE}_ALL_LIB") ;
		if (!exists($setVars_href->{$var}))
		{
			if ( ($options_href->{'mode'} eq 'applications') && $uses_vtest )
			{
				## In application mode we do *NOT* want to be using the virtual test libs
				$megalib = toLibName("${base}-noVTEST-", "all") ;
			}
			$megalib_vars .= "$var = $megalib\n" ;
		}

		# If virtual test lib was used, create a set of special cases where it is not included
		if ($uses_vtest)
		{
			## Create a lib that contains none of the virtual test libs
			$megalib = toLibName("${base}-noVTEST-", "all") ;
			addMegalib($megalib, $vars_href->{'repo'}, $repoLib, $base, \$content, \@megalibs, 
				\@extralibs, $vars_href, $uses_href, $uses_order_aref, $vtest_aref, $vtest_aref) ;
				
			## If there are more than 1, then (for simplicity's sake!) create a lib that doesn't contain each of these libs
			if (@$vtest_aref > 1)
			{
				foreach my $vtest (@$vtest_aref)
				{
					my $VTEST = uc $vtest ;
					$megalib = toLibName("${base}-no$VTEST-", "all") ;
					
					# create a megalib that excludes this test lib
					addMegalib($megalib, $vars_href->{'repo'}, $repoLib, $base, \$content, \@megalibs, 
						\@extralibs, $vars_href, $uses_href, $uses_order_aref, [$vtest], []) ;
				}
			}
		}

	}	
	
	# Create a target for building just the megalibs
	$content .= "megalibs: " ;
	foreach my $megalib (@megalibs)
	{
		$content .= "$megalib " ;
	}
	$content .= "\n\n" ;
	
	# add the vars
	$content .= "$megalib_vars\n" ;
	
	return $content ;
}


#------------------------------------------------------------------------------------------------------------------------------------
sub expand_uses_incs
{
	my ($vars_href, $uses_href, $uses_order_aref, $setVars_href) = @_ ;

	my $REPO = $vars_href->{'REPO'} ;
	my $content = "" ;
	
	# Create content something like:
	#
	#	# creates COMMON_INCLUDE
	#	include $(srcdir)/../common/Inc.am
	#	# creates VRH_INCLUDE
	#	include $(srcdir)/../vrh/Inc.am
	#	# creates VRS_INCLUDE
	#	include $(srcdir)/../vrs/Inc.am
	#	# Include local file
	#	include Inc.am
	#	
	#	AM_CPPFLAGS += \
	#		-I/usr/include/libxml2 \
	#		$(COMMON_INCLUDE) \
	#		$(VRH_INCLUDE) \
	#		$(VRS_INCLUDE) \
	#		$(@REPO@_INCLUDE)
	#
	
	foreach my $uses (@$uses_order_aref)
	{
		my $USES = uc $uses ;
		$content .= "# creates ${USES}_INCLUDE\n" ;
		$content .= "include \$(srcdir)/../$uses/Inc.am\n" ;
	}
	$content .= "# local file - create ${REPO}_INCLUDE\n" ;
	$content .= "include Inc.am\n\n" ;
	
	$content .= "AM_CPPFLAGS += \\\n" ;
	foreach my $uses (@$uses_order_aref)
	{
		my $USES = uc $uses ;
		$content .= "    \$(${USES}_INCLUDE) \\\n" ;
		my $path = usedLibPath($uses, "Inc.am") ;
	}
	$content .= "    \$(${REPO}_INCLUDE)\n\n" ;
	
	return $content ;
}

#------------------------------------------------------------------------------------------------------------------------------------
sub expand_amcond
{
	my ($vars_href, $all_uses_href, $options_href) = @_ ;

	# merge the used repo info into this one
	foreach my $atfile (keys %$all_uses_href)
	{
		my $uses_href = $all_uses_href->{$atfile}{'uses'} ;
		my $uses_order_aref = $all_uses_href->{$atfile}{'order'} ;
		
		foreach my $used (@$uses_order_aref)
		{
			foreach my $var (qw/%boards %apps/)
			{
				$vars_href->{$var} = { %{$vars_href->{$var}}, %{$uses_href->{$used}{$var}} } ;
			}
		}
		
		# merge this repo's binapps into apps
		$vars_href->{'%apps'} = { %{$vars_href->{'%apps'}}, %{$vars_href->{'%binapps'}} } ;
	}
	my $content = "" ;

	# Given something like:	
	# 	@amcond(foreach=%boards var=BOARD_IS_@forvar@ testvar=$BUILD_BOARD testval=@forvar@)@
	#
	# Create content something like:
	#
	#	AM_CONDITIONAL([BOARD_IS_HOST], [test "x$BUILD_BOARD" == xHOST])
	#	AM_CONDITIONAL([BOARD_IS_ETNA], [test "x$BUILD_BOARD" == xETNA])
	#
	
	# check options
	foreach my $opt (qw/foreach var testvar testval/)
	{
		if (!$options_href->{$opt})
		{
			die "ERROR: \@amcond\@ macro is missing required option '$opt'" ;
		}
	}

	# Check foreach variable
	my @forvars = () ;
	if (exists($vars_href->{ $options_href->{'foreach'} }))
	{
		my $foreach = $vars_href->{ $options_href->{'foreach'} } ;
		if (ref($foreach) eq 'HASH')
		{
			@forvars = sort keys %$foreach ;
		}
		elsif (ref($foreach) eq 'ARRAY')
		{
			@forvars = @$foreach ;
		}
		else
		{
			push @forvars, $foreach ;
		}
	}
	
	# Now cycle through variables
	foreach my $forvar (@forvars)
	{
		my %localvars = (%$vars_href) ;
		$localvars{'forvar'} = $forvar ;
		$localvars{'FORVAR'} = uc $forvar ;
		
		my ($var, $testvar, $testval) = @{$options_href}{qw/var testvar testval/} ;

		# expand vars
		$var =~ s/\@(\w+)\@/$localvars{$1}/g ;
		$testvar =~ s/\@(\w+)\@/$localvars{$1}/g ;
		$testval =~ s/\@(\w+)\@/$localvars{$1}/g ;
		
		$var = automakeVar($var) ;

		# Create conditional
		my $conditional = "AM_CONDITIONAL([$var], [test \"x$testvar\" == x$testval])" ;	
		
		
		$content .= "$conditional\n" ;
	}
	
	return $content ;
}

#------------------------------------------------------------------------------------------------------------------------------------
sub expand_applications_list
{
	my ($vars_href, $all_uses_href, $options_href) = @_ ;

	# merge the used repo info into this one
	foreach my $atfile (keys %$all_uses_href)
	{
		my $uses_href = $all_uses_href->{$atfile}{'uses'} ;
		my $uses_order_aref = $all_uses_href->{$atfile}{'order'} ;
		
		foreach my $used (@$uses_order_aref)
		{
			foreach my $var (qw/%boards %apps/)
			{
				$vars_href->{$var} = { %{$vars_href->{$var}}, %{$uses_href->{$used}{$var}} } ;
			}
		}
	}
	my $content = "" ;

	# Create content something like:
	#
	#	ALL_APPLICATIONS_LIST = \
	#		$(ETNA_ALU_RRH_APPLICATION_LIST) \
	#		$(HOST_ALU_RRH_APPLICATION_LIST)
	#	
	#	ETNA_ALU_RRH_APPLICATION_LIST = EtnaAluRrhProcess$(EXEEXT)
	#	EtnaAluRrhProcess_SOURCES = $(ALU_RRH_BIN_SRC)
	#	EtnaAluRrhProcess_LDFLAGS = -lrt $(AM_LDFLAGS)
	#	EtnaAluRrhProcess_LDADD = $(EtnaAluRrhProcess_LIBS) $(ETNA_ALU_RRH_ALL_LIB) $(ETNA_ALU_RRH_ALL_LDADD) $(LDADD)
	#	
	#	HOST_ALU_RRH_APPLICATION_LIST = HostAluRrhProcess$(EXEEXT)
	#	
	#	HostAluRrhProcess_SOURCES = $(ALU_RRH_BIN_SRC)
	#	HostAluRrhProcess_LDFLAGS = -lrt $(AM_LDFLAGS)
	#	HostAluRrhProcess_LDADD = $(HostAluRrhProcess_LIBS) $(HOST_ALU_RRH_ALL_LIB) $(HOST_ALU_RRH_ALL_LDADD) $(LDADD)
	#	
	#	HOST_GENERIC_RRH_APPLICATION_LIST = HostGenericRrhProcess$(EXEEXT)
	#	
	#	HostGenericRrhProcess_SOURCES = $(GENERIC_RRH_BIN_SRC)
	#	HostGenericRrhProcess_LDFLAGS = -lrt $(AM_LDFLAGS)
	#	HostGenericRrhProcess_LDADD = $(HostGenericRrhProcess_LIBS) $(HOST_GENERIC_RRH_ALL_LIB) $(HOST_GENERIC_RRH_ALL_LDADD) $(LDADD)
	#
	
	# In application mode, we need to create an application for all possible variants of application
	my @apps = () ;
	
	# create list of all the customer-app values found
	my %apps = (%{$vars_href->{'%apps'}}, %{$vars_href->{'%binapps'}}) ;
	foreach my $app (sort keys %apps)
	{
		foreach my $board (sort keys %{$vars_href->{'%boards'}})
		{
			my $base = "$board-$app" ;
			push @apps, $base ;
		}
	}
	
	# Create a list of all the possible applications
	$content .= "ALL_APPLICATIONS_LIST = " ;
	foreach my $base (@apps)
	{
		my $var = automakeVar( uc "${base}_APPLICATIONS_LIST") ;
		$content .= "\\\n   \$($var)" ;
	}
	$content .= "\n\n" ;
	
	# For each customer-app, create the list of applications under the customer-app
	foreach my $appname (keys %{$vars_href->{'%applications'}})
	{
		#	ETNA_ALU_RRH_APPLICATION_LIST = EtnaAluRrhProcess$(EXEEXT)
		#
		foreach my $board (sort keys %{$vars_href->{'%boards'}})
		{
			my $varbase = automakeVar( uc "${board}_${appname}") ;
		
			$content .= "${varbase}_APPLICATIONS_LIST = " ;
			foreach my $application (keys %{$vars_href->{'%applications'}{$appname}})
			{
				my $boardapp = ucfirst(lc $board) . $application ;
				
				$content .= "\\\n    $boardapp\$(EXEEXT)" ;
			}
			$content .= "\n\n" ;

			$content .= "${varbase}_STARTUP_APP = " ;
			foreach my $application (keys %{$vars_href->{'%applications'}{$appname}})
			{
				my $boardapp = ucfirst(lc $board) . $application ;
				
				# If application name ends with 'Process' then treat this as the main startup application
				if ($boardapp =~ /Process$/)
				{
					$content .= "$boardapp " ;
				}
			}
			$content .= "\n\n" ;

			foreach my $application (keys %{$vars_href->{'%applications'}{$appname}})
			{
				my $boardapp = ucfirst(lc $board) . $application ;
				
				#	EtnaAluRrhProcess_SOURCES = $(EtnaAluRrhProcess_SRC)
				#	EtnaAluRrhProcess_LDFLAGS = -lrt $(AM_LDFLAGS)
				#	EtnaAluRrhProcess_LDADD = $(EtnaAluRrhProcess_LIBS) $(ETNA_ALU_RRH_ALL_LIB) $(ETNA_ALU_RRH_ALL_LDADD) $(LDADD)
				$content .= "${boardapp}_SOURCES = \$(${application}_SRC)\n" ;
				$content .= "${boardapp}_LDFLAGS = -lrt \$(AM_LDFLAGS)\n" ;
				$content .= "${boardapp}_LDADD = \$(${boardapp}_LIBS) \$(${varbase}_ALL_LIB) \$(${varbase}_ALL_LDADD) \$(LDADD)\n" ;
				$content .= "\n" ;
			}
		}
		
	}

	return $content ;
}


#------------------------------------------------------------------------------------------------------------------------------------
sub expand_applications_select
{
	my ($vars_href, $all_uses_href, $options_href) = @_ ;

	# merge the used repo info into this one
	foreach my $atfile (keys %$all_uses_href)
	{
		my $uses_href = $all_uses_href->{$atfile}{'uses'} ;
		my $uses_order_aref = $all_uses_href->{$atfile}{'order'} ;
		
		foreach my $used (@$uses_order_aref)
		{
			foreach my $var (qw/%boards %apps/)
			{
				$vars_href->{$var} = { %{$vars_href->{$var}}, %{$uses_href->{$used}{$var}} } ;
			}
		}
	}
	my $content = "" ;

	# Create content something like:
	#
	#	if BOARD_IS_HOST
	#	if APP_IS_ALU_RRH
	#	APPLICATIONS_LIST += $(HOST_ALU_RRH_APPLICATION_LIST)
	#	endif
	#	if APP_IS_GENERIC_RRH
	#	APPLICATIONS_LIST += $(HOST_GENERIC_RRH_APPLICATION_LIST)
	#	endif
	#	endif
	#	
	#	if BOARD_IS_ETNA
	#	if APP_IS_ALU_RRH
	#	APPLICATIONS_LIST += $(ETNA_ALU_RRH_APPLICATION_LIST)
	#	endif
	#	endif
	#
	
	# In application mode, we need to create an application for all possible variants of application
	my @apps = () ;
	
	# create list of all the customer-app values found
	my %apps = (%{$vars_href->{'%apps'}}, %{$vars_href->{'%binapps'}}) ;
	foreach my $board (sort keys %{$vars_href->{'%boards'}})
	{
		$content .= "if BOARD_IS_${board}\n" ;
		foreach my $app (sort keys %apps)
		{
			my $var = automakeVar("${board}-${app}-APPLICATIONS_LIST") ;
			my $startupVar = automakeVar("${board}-${app}-STARTUP_APP") ;
			my $automakeApp = automakeVar($app) ;
			$content .= "if APP_IS_${automakeApp}\n" ;
			$content .= "APPLICATIONS_LIST += \$($var)\n" ;
			$content .= "STARTUP_APP += \$($startupVar)\n" ;
			$content .= "endif\n\n" ;
		}
		$content .= "endif\n\n" ;
	}
	
	return $content ;
}





#------------------------------------------------------------------------------------------------------------------------------------
sub addMegalib
{
	my ($megalib, $repo, $repoLib, $base, $content_ref, $megalibs_aref, $extralibs_aref, $vars_href, 
		$uses_href, $uses_order_aref, $skip_libs_aref, $vtest_aref) = @_ ;
	
	my %skip_libs = map {$_ => 1} @$skip_libs_aref ;
	
	push @$megalibs_aref, $megalib ;
			
	$$content_ref .= "$megalib: " ;
			
	## extra libs
	foreach my $extra (@$extralibs_aref)
	{
		$$content_ref .= "\\\n   $extra" ;
	}
	
	## This repo
	
	my %content_libs ;
	
	# if repo only has one lib OR has a common, then always use it
	my $common ;
	if (scalar(@{$vars_href->{'@libs'}}) == 1)
	{
		addLib( $vars_href->{'@libs'}[0], \%content_libs ) ;
	}
	elsif ($vars_href->{'_commonLib'})
	{
		addLib( $vars_href->{'_commonLib'}, \%content_libs ) ;
	}

	# Check for more abstract libs to include. For example, if this lib is of the form <board>-<customer>-<app>
	# Then see if there is a lib <customer>-<app> or <app>, and if so then add them
print STDERR "[$base] calling abstractParentLibs on lib: $repoLib\n" if $debug ;	
	my @parent_libs = abstractParentLibs($repo, $repoLib, $base, $vars_href) ;
	foreach my $lib (@parent_libs)
	{
		addLib( $lib, \%content_libs ) ;
	}

	# this lib - only add if there actually is any content (this is used mainly for when we're in application mode)
	if (exists($vars_href->{'%libs'}{$base}))
	{
		addLib( $repoLib, \%content_libs ) ;
	}
	
	# insert into content - ensures this repo's libs are first
	addContentLibs($content_ref, \%content_libs) ;

	## used repos
	my $used_vtest = 0 ;
	foreach my $used (@$uses_order_aref)
	{
		# skip any we are requested to ignore
		next if exists($skip_libs{$used}) ;
		
		# special case when using virtual test libs (due to test mocks)
		foreach my $vtest (@$vtest_aref)
		{
			if ($used eq $vtest)
			{
				++$used_vtest ;
				last ;
			}
		}
				
		# if repo only has one lib OR has a common, then always use it
		my $common ;
		if (scalar(@{$uses_href->{$used}{'@libs'}}) == 1)
		{
			addLib( usedLibPath($used, $uses_href->{$used}{'@libs'}[0]), \%content_libs ) ;
		}
		elsif ($uses_href->{$used}{'_commonLib'})
		{
			addLib( usedLibPath($used, $uses_href->{$used}{'_commonLib'}), \%content_libs ) ;
		}

		# Check for more abstract libs to include. For example, if this lib is of the form <board>-<customer>-<app>
		# Then see if there is a lib <customer>-<app> or <app>, and if so then add them
print STDERR "[$base] calling abstractParentLibs on used: $used\n" if $debug ;	
		my @parent_libs = abstractParentLibs($used, "", $base, $uses_href->{$used}) ;
		foreach my $lib (@parent_libs)
		{
			addLib( usedLibPath($used, $lib), \%content_libs ) ;
		}
		
		# Now see if the used lib has a lib that matches the BASE name (and isn't the same as the common lib already used)
		if (exists($uses_href->{$used}{'%libs'}{$base}))
		{
			addLib( usedLibPath($used, $uses_href->{$used}{'%libs'}{$base}), \%content_libs ) ;
		} 
		
		# insert into content - ensures this repo libs are first
		addContentLibs($content_ref, \%content_libs) ;
		
	}
	
			
	# libtool command
	$$content_ref .= "\n	\@echo \"LIBTOOL \$\@\"\n" ;
	$$content_ref .= "	\@\$(LIBTOOL) --mode=link \$(CC) \$(CFLAGS) \$(LDFLAGS) -o \$\@ \$^ > \$\@.log 2>&1\n\n" ;
	
	return $used_vtest ;
}






#------------------------------------------------------------------------------------------------------------------------------------
sub usedLibPath
{
	my ($used, $libname) = @_ ;
	
	return "\$(srcdir)/../$used/\$(BUILD_DIR)/$libname" ;	
}

#------------------------------------------------------------------------------------------------------------------------------------
sub libBaseName
{
	my ($libName, $repo) = @_ ;
	
	# Get the base name of the lib:
	# lib<BASE><repo>.la
	if ($libName =~ /lib([\w\d_\-]+)$repo/)
	{
		return $1 ;
	}
	return undef ;
}

#------------------------------------------------------------------------------------------------------------------------------------
sub addLib
{
	my ($lib, $contents_href) = @_ ;

	# Set hash value to 'new' for newly added lib; gets set to 'seen' when addded to the main list
	if (!exists($contents_href->{$lib}))
	{
		$contents_href->{$lib} = 'new' ;
	}	
}

#------------------------------------------------------------------------------------------------------------------------------------
sub addContentLibs
{
	my ($contents_ref, $contents_href) = @_ ;

	foreach my $lib (sort keys %$contents_href)
	{
		if ($contents_href->{$lib} eq 'new')
		{
			$$contents_ref .= "\\\n   $lib" ;
			$contents_href->{$lib} = 'seen' ;
		}
	}
	
}

#------------------------------------------------------------------------------------------------------------------------------------
sub abstractParentLibs
{
	my ($repo, $repoLib, $base, $vars_href) = @_ ;

	my %libs ;

	if ($debug)
	{
		print STDERR "abstractParentLibs(repo=$repo, repoLib=$repoLib, base=$base) this=$vars_href->{repo}\n" ;
		print STDERR Data::Dumper->Dump([$vars_href->{'%libs'}], [qw/libs/]) ;
	}
	
	# 0: Add this lib to the list
	if ($repoLib && exists($vars_href->{'%libs'}{$base}))
	{
		$libs{$repoLib} = $base ;
	}
	
	# 1: If this lib is of the form <board>-<customer>-<app>, then see if there is a lib 
	# <customer>-<app> or <app>, and if so then add them. If it's of the form <customer>-<app> then see if there is
	# a lib <app> and add it
	my @parts = split(/\-/, $base) ;
	shift @parts ;
	@parts = reverse @parts ;
	
	my $part_base = "" ;
	foreach my $part (@parts)
	{
		$part_base = "-$part_base" if $part_base ;
		$part_base = "$part$part_base" ;
		
		my $part_lib = toLibName($part_base, $repo) ;
		print STDERR "  * [abstract] With $part , checking abstract: $part_base\n" if $debug ;
		if (exists($vars_href->{'%libs'}{$part_base}))
		{
			print STDERR "  * * [abstract] $part_base Found\n" if $debug ;
			$libs{$part_lib} = $part_base ;
		}
	}
		
	# 2: For all the libs in the list: if lib is of the form <board>-<customer>-<app> or <customer>-<app> then see
	# if lib <board>-Generic-<app> / Generic-<app> exists and add if so
	my %all_libs = (%libs, 'this' => $base);
	foreach my $lib (keys %all_libs)
	{
		my $lib_base = $all_libs{$lib} ;
		my $generic_base = "" ;
	print STDERR "  * [abstract] With $lib , checking generic: $lib_base\n" if $debug ;

		if ($lib_base =~ /^(\S+)\-(\S+)\-(\S+)$/)
		{
			$generic_base = "$1-GENERIC-$2" ;
		}
		elsif ($lib_base =~ /^(\S+)\-(\S+)$/)
		{
			$generic_base = "GENERIC-$2" ;
		}
	print STDERR "  * * [abstract] base=$generic_base\n" if $debug ;
		
		if ($generic_base && exists($vars_href->{'%libs'}{$generic_base}))
		{
	print STDERR "  * * [abstract] $generic_base Found\n" if $debug ;
			$libs{ toLibName($generic_base, $repo) } = $generic_base ;
		}
	}
	
	# 3: For all the libs in the list: if lib is of the form <board>-<customer>-<app>  then see
	# if lib <board> exists and add if so
	%all_libs = (%libs, 'this' => $base);
	foreach my $lib (keys %all_libs)
	{
		my $lib_base = $all_libs{$lib} ;
		my $board_base = "" ;
		my $app_base = "";
	print STDERR "  * [abstract] With $lib , checking board: $lib_base\n" if $debug ;

		if ($lib_base =~ /^(\S+)\-(\S+)\-(\S+)$/)
		{
			$board_base = "$1" ;
			$app_base = "$3";
		}
		
		if( !$board_base )
		{
			if ($lib_base =~ /^(\S+)\_(\S+)$/)
			{
				$board_base = "$1" ;
				$app_base = "$2" ;
			}
		}
		
	print STDERR "  * * [abstract] board base=$board_base app=$app_base \n" if $debug ;
		
		if ($board_base && exists($vars_href->{'%libs'}{$board_base}))
		{
	print STDERR "  * * [abstract] $board_base Found\n" if $debug ;
			$libs{ toLibName($board_base, $repo) } = $board_base ;
		}
		# look for <BOARD>_<APP> combinations and add if available 
		$board_base = $board_base."_".$app_base;
    print STDERR "  * * [abstract] board_app base=$board_base app=$app_base \n" if $debug ;
		
	    if ($board_base && exists($vars_href->{'%libs'}{$board_base}))
	    {
	print STDERR "  * * [abstract] $board_base Found\n" if $debug ;
		    $libs{ toLibName($board_base, $repo) } = $board_base ;
	    }		
	}

	
	if ($debug)
	{
		foreach my $lib (sort keys %libs)
		{
			print STDERR "  [abstract] $lib\n" ;
		}
	}
	
	
	return sort keys %libs ;
}

#------------------------------------------------------------------------------------------------------------------------------------
sub toLibName
{
	my ($base, $repo) = @_ ;
	
	return "lib${base}${repo}.la" ;
}


#------------------------------------------------------------------------------------------------------------------------------------
sub update_templates
{
	my ($force_update) = @_ ;
	
	foreach my $tmpl (glob("$progpath/$templates_dir/*"))
	{
		my $rel = File::Spec->abs2rel($tmpl, "$progpath/$templates_dir") ;
		if (-f $tmpl)
		{
			# see if it exists here
			# Only copy if it doesn't exist OR we're told to forceably copy it
			if ( (! -f $rel) || ($force_update && ($force_update eq $rel)))
			{
				print " * Copying $rel\n" ;
				copy($tmpl, $rel) or die "Error: Unable to copy file $rel : $!" ;
			}
		}
		
		if (-d $tmpl)
		{
			my $force_copy_dir = ($force_update && ($force_update eq $rel)) ;
			
			# if directory exists, then only copy contents if we're forced to
			next if ( (-d $rel) && !$force_copy_dir) ;

			# see if it exists here
			if (! -d $rel)
			{
				print " * Create dir $rel\n" ;
				mkdir "$rel" or die "Error: Unable to create directory : $!" ;
			}
			
			# copy 1 level of dir contents
			foreach my $dir_tmpl (glob("$progpath/$templates_dir/$rel/*"))
			{
				next unless -f $dir_tmpl ;
				my $dir_rel = File::Spec->abs2rel($dir_tmpl, "$progpath/$templates_dir") ;
				
				if ( (! -f $dir_rel) || $force_copy_dir)
				{
					print " * Copying $dir_rel\n" ;
					copy($dir_tmpl, $dir_rel) or die "Error: Unable to copy file $dir_rel : $!" ;
				}
			}
		}
	}
	
	print " * DONE\n" ;

}


#------------------------------------------------------------------------------------------------------------------------------------
# convert a directory name to a variable
sub dir2var
{
	my ($dir) = @_ ;
	
	# get string
	my $var = $dir ;
	
	# remove leading/trailing /
	$var =~ s%^/%% ;
	$var =~ s%/$%% ;
	
	# convert invalid chars
#	return automakeVar($var) ;
	return $var ;
}

#------------------------------------------------------------------------------------------------------------------------------------
# Given a directory name, split it off into board and application name. Returns empty string for either value
# if it's not specified or is common/generic
#
# Expect names of the form:			Results: board		application
#	<board>-<customer>-<app>				<board>		<customer>-<app>
#	<customer>-<app>						""			<customer>-<app>
#	Generic-<app>							""			""
#	<board>									<board>		""
#	common									""
#
#
#
sub getBoardApp
{
	my ($dir, $includeGeneric) = @_ ;
	
	$includeGeneric ||= 0 ;
	
	# Grab top-level dir is this is a path
	$dir =~ s%(^[^\/]+)/.*%$1% ;
	
	my ($board, $appname) = ("", "");
	my ($customer, $app) = ("", "");
	if ($dir =~ /^(\S+)\-(\S+)\-(\S+)$/)
	{
		$board = $1 ;
		$customer = $2 ;
		$app = $3 ;
	}
	elsif ($dir =~ /^(\S+)\-(\S+)\_(\S+)$/)
	{
		$customer = $1 ;
		$board = $2 ;
		$app = $3 ;
	}
	elsif ($dir =~ /^(\S+)\-(\S+)$/)
	{
		$customer = $1 ;
		$app = $2 ;
	}
	elsif ($dir =~ /^(\S+)\_(\S+)$/)
	{
		$board = $1 ;
		$app = $2 ;
	}
	elsif ($dir =~ /^(\S+)$/)
	{
		$board = $1 ;
	}

	$board = "" if (lc $board eq 'common') ;
	
	if (!$includeGeneric)
	{
		if (lc $customer eq 'generic')
		{
			$customer = "" ;
		}
	}
	
	if ($customer && $app)
	{
		$appname = "$customer-$app" ;
	}
	if( !$appname )
	{
		$appname = $app ;
	}
	
	return ($board, $appname) ;
}



#------------------------------------------------------------------------------------------------------------------------------------
# create a valid automake Makefile variable
sub automakeVar
{
	my ($var) = @_ ;
	
	# convert invalid chars
	$var =~ s%[^\w\d]%_%g ;
	return $var ;
}

#------------------------------------------------------------------------------------------------------------------------------------
# Find files - return an array contining all the file paths find under this directory
sub find_files
{
	my ($dir) = @_ ;
	my @files =  () ;
	
	foreach my $entry (glob("$dir/*"))
	{
		# tidy up path name (I just find it offensive having // ...)
		$entry =~ s%//%/%g ;
		
		if (-d $entry)
		{
			my @subfiles = find_files($entry) ;
			push @files, @subfiles ;
		}
		elsif (-f $entry)
		{
			push @files, $entry ;
		}
	}
	
	return @files ;	
}

#------------------------------------------------------------------------------------------------------------------------------------
# Show program usage
sub usage
{
	my ($err) = @_ ;
	
	my $prog = $0 ;
	$prog =~ s%.*/([^/]+)$%$1% ;
	
	print <<HELP;
$prog - Manage autotools files

USAGE
    $prog [<options>] <repository path>

OPTIONS
    -help            This help
    -dir dir         Only update the specified directory under the repo
    -path dir/comp   Only update the component 'comp' under directory 'dir' 

DESCRIPTION

This script is used to create/update CMake lists files.

HELP
	
	$err ||= 0 ;
	exit($err) ;
}

#============================================================================================
# END
#============================================================================================
1 ;
