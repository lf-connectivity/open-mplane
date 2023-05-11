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
	
	my $yangfile ;
	my $outfile ;
	my $editconfig = 0 ;
	
	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,
		
		'edit' => \$editconfig,
		'yang=s' => \$yangfile,
		'out=s' => \$outfile,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

    pod2usage("$0: No template file given.")  if (!$yangfile) ;
    pod2usage("$0: No output file given.")  if (!$outfile) ;

	if (! -f $yangfile)
	{
	    pod2usage("$0: Input file invalid.") ;
	}

	process_file($yangfile, $outfile, $editconfig) ;    

	exit(0);


#============================================================================================

#--------------------------------------------------------------------------------------------
sub process_file
{
	my ($yangfile, $outfile, $editconfig) = @_ ;
	
	## make output dir
	my $outdir = (File::Spec->splitpath($outfile))[1] ;
	make_path($outdir) ;	
	
	print "PROCESS : $yangfile\n" ;
	print "GENERATE: $outfile\n" ;
	
# module: ietf-interfaces
#   +--rw interfaces
#   |  +--rw interface* [name]
#   |     +--rw name                                 string
#   |     +--ro speed?                               ietf-yang-types:gauge64
#   |     +--ro statistics
#   |     |  +--ro discontinuity-time    ietf-yang-types:date-and-time
#   |     +--rw ietf-ip:ipv4!
#   |     |  +--rw ietf-ip:enabled?                      boolean <true>
#   |     |  +--rw ietf-ip:mtu?                          uint16
#   |     |  +--rw ietf-ip:address* [ip]
#   |     |  |  +--rw ietf-ip:ip         ietf-inet-types:ipv4-address-no-zone
#   |     |  |  +--rw (ietf-ip:subnet)
#   |     |  |  |  +--:(ietf-ip:prefix-length)
#   |     |  |  |  |  +--rw ietf-ip:prefix-length?   uint8
#   |     |  |  |  +--:(ietf-ip:netmask)
#   |     |  |  |     +--rw ietf-ip:netmask?   ietf-yang-types:dotted-quad {ietf-ip:ipv4-non-contiguous-netmasks}?
#   |     |  |  +--ro ietf-ip:origin?    ip-address-origin
#   |     |  +--rw ietf-ip:neighbor* [ip]
#   |     |  |  +--rw ietf-ip:ip                    ietf-inet-types:ipv4-address-no-zone
#   |     |     +--rw o-ran-interfaces:s-plane-marking?            ietf-inet-types:dscp <46>
#   |     |     +--rw o-ran-interfaces:other-marking?              ietf-inet-types:dscp <0>
#   |     |     +--rw o-ran-interfaces:enhanced-uplane-markings* [up-marking-name]
#   |     |        +--rw o-ran-interfaces:up-marking-name     string
#   |     |        +--rw o-ran-interfaces:enhanced-marking?   ietf-inet-types:dscp
#   |     +--rw ietf-ip:ipv6!
#   |     |  +--rw ietf-ip:enabled?                      boolean <true>

	
	my $line ;
	open(my $fh, "<", "$yangfile") or die "Unable to read $yangfile" ;
	open(my $ofh, ">", "$outfile") or die "Unable to write $outfile" ;
	
	my $inModule = 0 ;
	my %tags ;
	my $prevLevel = 0 ;
	my $prevRO = 0 ;
	while (defined($line=<$fh>))
	{
		chomp $line ;
		
		if ($line =~ /^module:/)
		{
			print $ofh "\n$line\n" ;
			$inModule = 1 ;
			next ;
		}
	
		if (!$line)
		{
			for (my $i=$prevLevel; $i >= 0; --$i)
			{
				if (exists $tags{$i})
				{
# print " * close $tags{$i} ($i)\n" ;				
					my $prefix = " " x $i ;
					print $ofh "${prefix}</$tags{$i}>\n" ;
					delete $tags{$i} ;
				}
			}

			$inModule = 0 ;
			$prevLevel = 0 ;
			undef %tags ;
			$prevRO = 0 ;
			next ;
		}
	
		next if (!$inModule) ;
		
# print ">>$line<<\n" ;

		# deprecated
 		if ($line =~ /^(.*x\-\-)ro (\S+)(.*)$/)
#		if ($line =~ /x--ro/)
		{
# 			print "DEPRECATED RO $1\n" ;
			$prevRO = 1 ;
		}

		if ($line !~ /\+/)
		{
# print "--skip\n" if $DEBUG ;
			next ;
		}
		
		my ($start, $tag, $arg) ;
		my $typeRO = 0 ;
		if ($line =~ /^(.*)rw (\S+)(.*)$/)
		{
# 			print "RW $2 [$3]\n" ;
			$start = $1 ;
			$tag = $2 ;
			$arg = $3 ;
		}
		
		if ($line =~ /^(.*)ro (\S+)(.*)$/)
		{
# 			print "RO $2 [$3]\n" ;
			$start = $1 ;
			$tag = $2 ;
			$arg = $3 ;
			$typeRO = 1 ;
		}
		if ($line =~ /^(.*\+\-\-:)(\S+)(.*)$/)
		{
# 			print "CASE $2 [$3]\n" ;
			$start = $1 ;
			$tag = "CASE-$2" ;
			$arg = $3 ;
			$typeRO = $prevRO ;
		}

	
		$prevRO = $typeRO ;
		next if (!$tag) ;
		
		
		
		if ($tag =~ /[\S:]+:([^\s:]+)/)
		{
			$tag = $1 ;
		}
		if ($tag =~ /^:\(([^\s:]+)\)/)
		{
			$tag = $1 ;
		}
		$tag =~ s/^([\w\-]+)[?!\*]$/\1/ ;
  		print "TAG $tag  ARG $arg  - type RO=$typeRO  prev RO=$prevRO\n" ;
		
		$arg =~ s/^\s*(\S+)\s*$/\1/ ;
		$arg =~ s/^\s*->\s+(\S+)\s*$/\1/ ;
		$arg =~ s/^\s*(\S+)\s+\S+$/\1/ ;
		if ($arg =~ /^\[(\S+)\]$/)
		{
			$arg = "" ;
		}
		if ($arg =~ /^\{(\S+)\}\?$/)
		{
			$arg = "" ;
		}
		$arg =~ s/^\s*(\S+)/\1/ ;

# 		if ($arg)
# 		{
# 			print "  ARG $arg\n" ;
# 		}

		# if this is a tag, don't decend if it's RO and we're only displaying RW 
		if (!$arg && $editconfig)
		{
			next if ($typeRO) ;
		}

		my $prefixLen = length $start ;
		my $spaces = " " x $prefixLen ;
		
# my $type = "OPEN {" ;
# $type = "LEAF" if ($arg) ;
# print "$tag ($prevLevel -> $prefixLen) $type\n" ;	
		
		# see if we need to close the current tag(s)
		if (($prefixLen < $prevLevel) || (!$arg))
		{
			for (my $i=$prevLevel; $i >= $prefixLen; --$i)
			{
				if (exists $tags{$i})
				{
# print " * close $tags{$i} ($i)\n" ;				
					my $prefix = " " x $i ;
					print $ofh "${prefix}</$tags{$i}>\n" ;
					delete $tags{$i} ;
				}
			}
		}
	
		# if arg then it's a leaf, otherwise it's opening a tag
		if ($arg)
		{
			# leaf - only show if matches requested
			# For edit-config, show only read/write
			# otherwise (got get), show everything
			# 
			if (!$editconfig || ($editconfig && !$typeRO))
			{
				print $ofh "${spaces}<$tag>$arg</$tag>\n" ;
			}
		}
		else
		{
			print $ofh "${spaces}<$tag>\n" ;
			$tags{$prefixLen} = $tag ;
		}
		$prevLevel = $prefixLen ;
		
				
	}
	close $fh ;	
	close $ofh ;	
	
}

#---------------------------------------------------------------------------------------------------------------

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

yangtree2xml - Convert YANG tree text into XML

=head1 SYNOPSIS

yangtree2xml [options]  -yang <yangtree text file> -out <output file> <names>

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

Reads a yang tree text file (created by "yanglint -f tree") and creates XML that can be used to document example settings


=cut

