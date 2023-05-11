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

	my $rulesfile ;
	my $xmlfile ;
	my $cppfile ;

	GetOptions(
		"debug=i" => \$debug,
		"verbose=i" => \$verbose,
		'man' => \$man,
		'h|help' => \$help,

		'rules=s' => \$rulesfile,
		'xml=s' => \$xmlfile,
		'cpp=s' => \$cppfile,

	)  or pod2usage(2) ;

    pod2usage(1) if $help;
    pod2usage(-verbose => 2) if $man;

    pod2usage("$0: No rules file given.")  if (!$rulesfile) ;
    pod2usage("$0: No output file(s) given.")  if (!$xmlfile && !$cppfile) ;

	if (! -f $rulesfile)
	{
	    pod2usage("$0: Rules file invalid.") ;
	}

	process_rules($rulesfile, $xmlfile, $cppfile) ;

	exit(0);


#============================================================================================


#--------------------------------------------------------------------------------------------
sub process_rules
{
	my ($rulesfile, $xmlfile, $cppfile) = @_ ;

	my %rules ;
	my @groups ;

	my $line ;
	open(my $fh, "<", "$rulesfile") or die "Unable to read $rulesfile" ;
	while (defined($line=<$fh>))
	{
		chomp $line ;

print ">>$line<<\n" if $DEBUG ;

		# Get header line
		if ($line =~ /Rule/)
		{
			# Line should be in the form:
			# 0     1    2   3     4   5   6          7
			# Rules sudo nms fm-pm swm smo hybrid-odu Module
			my @fields = split / /, $line ;
			next unless (@fields == 8) ;

			$groups[0] = "" ;
			my $i=1 ;
			for (; $i <= 6; ++$i)
			{
				$groups[$i] = $fields[$i] ;
				$rules{ $groups[$i] } = {} ;
			}

			# add a "root" group
			$groups[$i] = "root" ;
			$rules{ $groups[$i] } = {} ;

			next ;
		}

		# Line should be in the form:
		# 0     1    2   3     4   5   6          7
		# Rules sudo nms fm-pm swm smo hybrid-odu Module
		# urn:o-ran:supervision:x.y RWX --- --- --- RW- RWX o-ran-supervision

		my @fields = split / /, $line ;
		next unless (@fields == 8) ;

		my $module = $fields[7] ;

		my $i=1;
		for (; $i <= 6; ++$i)
		{
			my $access = $fields[$i] ;

			# RFC8341 defines the "read" operation as:
			#   "allows the client to read a data node instance from a
			#	datastore or receive the notification event type."
			# so if we have X then we need to also enable R

			# TODO: is the above actually true?
			# if ($access =~ /X/)
			# {
			# 	substr($access, 0, 1) = "R" ;
			# }

			$rules{ $groups[$i] }{ $module } = $access ;
		}

		# add root
		$rules{ $groups[$i] }{ $module } = "RWX" ;
	}
	close $fh ;


#	## DEBUG
#	for my $group (@groups)
#	{
#		print "GROUP: $group\n" ;
#
#		for my $mod (sort keys %{$rules{ $group }})
#		{
#			my $access = $rules{ $group }{ $mod } ;
#			print "  $mod : $access\n" ;
#		}
#		print "\n" ;
#	}
#	print "\n" ;

	## Outut

	## XML
	if ($xmlfile)
	{
		open(my $ofh, ">", "$xmlfile") or die "Unable to write $xmlfile" ;
		for my $group (@groups)
		{
			next if $group eq "" ;

			print $ofh "  <rule-list>\n" ;
			print $ofh "    <name>$group-rules</name>\n" ;
			print $ofh "    <group>$group</group>\n" ;

			for my $mod (sort keys %{$rules{ $group }})
			{
				my $access = $rules{ $group }{ $mod } ;

	print "[$group] $mod $access\n" ;

				# skip any R-X rules because that's the default
				next if ($access eq "R-X") ;

	#print " > OUT <\n" ;

				print $ofh "    <rule>\n" ;
				if ($access eq "R--")
				{
					print $ofh "      <name>$group-$mod</name>\n" ;
					print $ofh "      <module-name>$mod</module-name>\n" ;
					print $ofh "      <access-operations>exec</access-operations>\n" ;
					print $ofh "      <action>deny</action>\n" ;
					print $ofh "      <comment>$group $mod $access</comment>\n" ;
				}
				elsif ($access eq "RWX")
				{
					print $ofh "      <name>$group-$mod</name>\n" ;
					print $ofh "      <module-name>$mod</module-name>\n" ;
					print $ofh "      <access-operations>create update delete</access-operations>\n" ;
					print $ofh "      <action>permit</action>\n" ;
					print $ofh "      <comment>$group $mod $access</comment>\n" ;
				}
				elsif ($access eq "--X")
				{
					print $ofh "      <name>$group-$mod</name>\n" ;
					print $ofh "      <module-name>$mod</module-name>\n" ;
					print $ofh "      <access-operations>read</access-operations>\n" ;
					print $ofh "      <action>deny</action>\n" ;
					print $ofh "      <comment>$group $mod $access</comment>\n" ;
				}
				elsif ($access eq "RW-")
				{
					print $ofh "      <name>$group-$mod-permit-write</name>\n" ;
					print $ofh "      <module-name>$mod</module-name>\n" ;
					print $ofh "      <access-operations>create update delete</access-operations>\n" ;
					print $ofh "      <action>permit</action>\n" ;
					print $ofh "      <comment>$group $mod $access (1/2)</comment>\n" ;
				}
				elsif ($access eq "---")
				{
					print $ofh "      <name>$group-$mod</name>\n" ;
					print $ofh "      <module-name>$mod</module-name>\n" ;
					print $ofh "      <access-operations>read</access-operations>\n" ;
					print $ofh "      <action>deny</action>\n" ;
					print $ofh "      <comment>$group $mod $access (1/2)</comment>\n" ;
				}
				else
				{
					print "** UNHANDLED ACCESS $access **\n" ;
				}
				print $ofh "    </rule>\n" ;

				if ( ($access eq "RW-") || ($access eq "---") )
				{
					print $ofh "    <rule>\n" ;
					print $ofh "      <name>$group-$mod-deny-exec</name>\n" ;
					print $ofh "      <module-name>$mod</module-name>\n" ;
					print $ofh "      <access-operations>exec</access-operations>\n" ;
					print $ofh "      <action>deny</action>\n" ;
					print $ofh "      <comment>$group $mod $access (2/2)</comment>\n" ;
					print $ofh "    </rule>\n" ;
				}


			}
			print $ofh "  </rule-list>\n" ;
		}
		close $ofh ;
	}


	## C++
	if ($cppfile)
	{
		open(my $ofh, ">", "$cppfile") or die "Unable to write $cppfile" ;
		for my $group (@groups)
		{
			next if $group eq "" ;

			# Camel case
			my $Group = $group ;
			$Group =~ s/\-//g ;
			$Group = ucfirst $Group ;

			print $ofh <<"HEAD";
//-------------------------------------------------------------------------------------------------------------
bool IetfNetconfAcmHandler::add${Group}Rules()
{
	std::map<std::string, std::string> dataCfg;

	dataCfg["rule-list[name='$group-rules']/name"] = "$group-rules" ;
	dataCfg["rule-list[name='$group-rules']/group"] = "$group" ;

HEAD

			for my $mod (sort keys %{$rules{ $group }})
			{
				my $access = $rules{ $group }{ $mod } ;

	print "[$group] $mod $access\n" ;

				# skip any R-X rules because that's the default
				next if ($access eq "R-X") ;

	#print " > OUT <\n" ;

				my $name = "$group-$mod" ;
				my $ops = "" ;
				my $action = "" ;
				my $comment = "$group $mod $access" ;

				if ($access eq "R--")
				{
					$ops = "exec" ;
					$action = "deny" ;
				}
				elsif ($access eq "RWX")
				{
					$ops = "create update delete" ;
					$action = "permit" ;
				}
				elsif ($access eq "--X")
				{
					$ops = "read" ;
					$action = "deny" ;
				}
				elsif ($access eq "RW-")
				{
					$name = "$group-$mod-permit-write" ;
					$ops = "create update delete" ;
					$action = "permit" ;
					$comment .= " (1/2)" ;
				}
				elsif ($access eq "---")
				{
					$name = "$group-$mod-deny-read" ;
					$ops = "read" ;
					$action = "deny" ;
					$comment .= " (1/2)" ;
				}
				else
				{
					print "** UNHANDLED ACCESS $access **\n" ;
				}

				print $ofh <<"RULE1";
//	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/name"] = "$name" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/module-name"] = "$mod" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/access-operations"] = "$ops" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/action"] = "$action" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/comment"] = "$comment" ;

RULE1


				if ( ($access eq "RW-") || ($access eq "---") )
				{
					$name = "$group-$mod-deny-exec" ;
					print $ofh <<"RULE2";
//	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/name"] = "$name" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/module-name"] = "$mod" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/action"] = "deny" ;
	dataCfg["rule-list[name='$group-rules']/rule[name='$name']/comment"] = "$group $mod $access (2/2)" ;

RULE2

				}


			}

			print $ofh <<"TAIL";
	if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
		return false ;

	return true ;
}


TAIL

		}
		close $ofh ;
	}

}

#---------------------------------------------------------------------------------------------------------------

#============================================================================================
# END
#============================================================================================
__END__

=head1 NAME

genRules - Generate nacm rules XML from rules file

=head1 SYNOPSIS

genRules [options]  -rules <rules file> [-xml <xml output>] [-cpp <C++ output>]

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

Reads the rules CSV file and outputs the information as XML setting for ietf-netconf-nacm


=cut
