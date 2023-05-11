#!/usr/bin/perl
#

# USAGE: make-gen-init-cpio.pl ROOTFS DEVICE-LIST FILE-LIST

use warnings;
use strict;
use File::Find;

my $rootfs = $ARGV[0];
my $device_list = $ARGV[1];
my $file_list = $ARGV[2];

# file <name> <location> <mode> <uid> <gid> [<hard links>]
# dir <name> <mode> <uid> <gid>
# nod <name> <mode> <uid> <gid> <dev_type> <maj> <min>
# slink <name> <target> <mode> <uid> <gid>
# pipe <name> <mode> <uid> <gid>
# sock <name> <mode> <uid> <gid>
#

## Process device list

# Ensure /dev directory exists
print "dir /dev 0755 0 0\n";

# proces file
my $fh;
open($fh, "$device_list") || die "failed to open $device_list - $!";
my $line;
while (defined($line = <$fh>)) {
    chomp($line);
    my ($name, $type, $perm, $uid, $gid, $maj, $min) = split(/\s+/, $line);
    print "nod $name 0$perm $uid $gid $type $maj $min\n";
}
close($fh) ;

## Process file list
my %fileList ;
if (open($fh, "$file_list"))
{
	while (defined($line = <$fh>)) {
	    chomp($line);
	    my ($type, $name, @args) = split(/\s+/, $line);
	    $fileList{$name} = $type ;
		if ($type eq "file")
		{
		    my ($type, $name, $location, $mode, $uid, $gid, @links) = split(/\s+/, $line);
			print "$type $name $rootfs/$location $mode $uid $gid @links\n" ;
		}
		else
		{
	    	print "$line\n";
		}
	}
	close($fh) ;
}

## Process root filesystem directory

chdir($rootfs);
find( {
	#follow => 0,
	no_chdir => 1,

	wanted => sub {
	my $f = $File::Find::name;
	$f =~ s/^\.//;
	return if ($f eq "");
	
	# skip anything already covered in the file list
	return if (exists($fileList{$f})) ;
	
	# skip .gitignore
	return if ($f =~ /\.gitignore$/) ;
	
	#print "++++ $f _=$_\n";
	my $perm = 0755;
	if (-l) {
	    my $link = readlink($File::Find::name);
	    #print "---- link [$link] $File::Find::name\n";
	    printf("slink $f $link 0%03o 0 0\n", $perm);
	    return;
	}
	#print "++++ $f perm=$perm\n";
	if (-f) {
	    printf("file $f $rootfs$f 0%03o 0 0\n", $perm & 0777);
	    return;
	}
	if (-d) {
	    print "dir $f 0755 0 0\n";
	    return;
	}
	print "============== $File::Find::name\n";
	die sprintf("unknown file $f type 0%08o", $perm);

    }
}, ".");
