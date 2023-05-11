#!/bin/bash

function usage () {
 echo "./unpack_yocto_packages.sh <RPM_SOURCES> <PKGDATA_DIR> <PACKAGES>"
 echo ""
 echo "Create a tarball by unpacking packages from the Yocto Package Feed."
 echo ""
 echo "Arguments:"
 echo "    RPM_SOURCES: The directory containing the RPMs in the Yocto Package Feed."
 echo "    PKGDATA_DIR: The value of the PKGDATA_DIR global Yocto path."
 echo "    PACKAGES: space-separated list of packages to populate the tarball with."
 echo ""
 echo "The tarball contents are staged in /tmp/rootfs. If you wish to stage"
 echo "these files in a different location, please specify the location by"
 echo "defining the `ROOTFS_DIR` environment variable"
}

ROOTFS_DIR?=/tmp/rootfs
ARCH=aarch64
FORMAT=rpm

# Parse and validate args
rpm_dir=$1
shift
pkgdata_dir=$1
shift
packages=$@
test -d "$rpm_dir" || { usage ;  exit 1 ; }
test -d "$pkgdata_dir" || { usage ;  exit 1 ; }
test "$packages" || { usage ;  exit 1 ; }

# Unpack RPMs
for package_name in $packages ; do   
    ## Find matching packages from Package Feed
    pn="$(grep ^PKG_$package_name $pkgdata_dir/$package_name | cut -f 2 -d ' ' )"
    pv="$(grep ^PKGV $pkgdata_dir/$package_name | cut -f 2 -d ' ' )"
    pr="$(grep ^PR $pkgdata_dir/$package_name | cut -f 2 -d ' ' )"
    package="$pn-$pv-$pr".$ARCH.$FORMAT

    package_file="$rpm_dir"/"$package"
    test -f "$package_file" || { "Package not found: $package" ;  exit 1 ; }

    # Write package to rootfs
    rpm2cpio $rpm_dir/$package | \
        cpio \
            --extract \
            --make-directories \
            --preserve-modification-time \
            --verbose \
            --directory $ROOTFS_DIR
done
