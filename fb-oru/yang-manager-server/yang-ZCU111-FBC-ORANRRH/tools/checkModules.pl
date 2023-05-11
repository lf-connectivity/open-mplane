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
	
	my $rulesfile ;
	my $modulesfile ;
	
	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,
		
		'rules=s' => \$rulesfile,
		'mod=s' => \$modulesfile,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

    pod2usage("$0: No rules file given.")  if (!$rulesfile) ;
    pod2usage("$0: No modules file given.")  if (!$modulesfile) ;

	if (! -f $rulesfile)
	{
	    pod2usage("$0: Rules file invalid.") ;
	}
	if (! -f $modulesfile)
	{
	    pod2usage("$0: Modules file invalid.") ;
	}

	my %modules ;
	
	process_modules($modulesfile, \%modules) ;    
	process_rules($rulesfile, \%modules) ;    

	exit(0);


#============================================================================================

#--------------------------------------------------------------------------------------------
sub process_modules
{
	my ($modulesfile, $modules_href) = @_ ;
	
	my $line ;
	open(my $fh, "<", "$modulesfile") or die "Unable to read $modulesfile" ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		
print ">>$line<<\n" if $DEBUG ;	

		# looking for:
		# module: ietf-netconf-acm	
		if ($line =~ /^\s*module:\s*(\S+)$/)
		{
			$modules_href->{$1} = 0 ;
		}
	}
	close $fh ;	
}


#--------------------------------------------------------------------------------------------
sub process_rules
{
	my ($rulesfile, $modules_href) = @_ ;
	
	my %invalid ;
	
	my $line ;
	open(my $fh, "<", "$rulesfile") or die "Unable to read $rulesfile" ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		
print ">>$line<<\n" if $DEBUG ;

		# Skip header line
		if ($line =~ /Rule/)
		{
			next ;
		}

		# Line should be in the form:
		# 0     1    2   3     4   5
		# Rules sudo nms fm-pm swm Module
		# urn:o-ran:supervision:x.y --X --- --- --- o-ran-supervision
		
		my @fields = split / /, $line ;
		my $module = $fields[5] ;
		
		if ( exists($modules_href->{$module}) )
		{
			$modules_href->{$module} = 1 ;
		}
		else
		{
			$invalid{$module} = 1 ;
		}
	}
	close $fh ;	
	
	print "INVALID\n" ;
	foreach my $mod (sort keys %invalid)
	{
		print "  $mod\n" ;
	}
	print "\n" ;
	
	print "NOT COVERED\n" ;
	foreach my $mod (sort keys %$modules_href)
	{
		next if ($modules_href->{$mod} > 0) ;
		print "  $mod\n" ;
	}
	print "\n" ;
	
	
	
	
}

#---------------------------------------------------------------------------------------------------------------

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

checkModules - Check module names in rules are valid

=head1 SYNOPSIS

checkModules [options]  -rules <rules file> -mod <modules file>

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

Reads the rules CSV file and a file that contains the module names in the format:

module: ietf-netconf-acm

(i.e. yang-lint tree output)

Checks that all of the module names in the rules file are valid and match up with the valid module names. 


=cut

