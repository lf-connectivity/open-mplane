#!/bin/bash

function package_not_found () {
  echo "====================================================="
  echo "App package failed. Ensure all packages are available"
  echo ""
  echo "Run bitbake packagegroup-zcu111"
  echo "====================================================="
}

function usage () {
 echo "./zcu111_archive.sh <BUILD_FOLDER>"
 echo ""
 echo "Create a ZCU111 app tarball."
 echo ""
 echo "Arguments:"
 echo "    BUILD_FOLDER: The Yocto build directory"
}

# Constants
ROOTFS=/tmp/rootfs
ARCHIVE=app.tgz
PACKAGES="app-startup-scripts \
  applications-common-rootfs \
  dot1agd-utils \
  mplane-oranrrh-process \
  libatomic \
  libcrypto \
  libssh \
  libssl \
  libtinyxml2 \
  libtinyxml2-dev \
  netconf2 \
  netopeer2 \
  openssl-bin \
  sysrepo \
  yang \
  yang-config \
  yang-dev \
  yang-ietf \
  yang-manager-server-scripts \
  yang-oran \
  yang-startup"

# Parse Args
build_dir=$1

# Remove old build
( test -d $ROOTFS || test -f $ROOTFS ) && \
{
  read -p "$ROOTFS is not empty. Delete and continue? [y/n]>"
  test "$REPLY" != "y" && exit 1;
  rm -rf $ROOTFS
}
( test -d $ARCHIVE || test -f $ARCHIVE ) && \
{
  read -p "$ARCHIVE is not empty. Delete and continue? [y/n]>"
  test "$REPLY" != "y" && exit 1;
  rm -rf $ARCHIVE
}

# Populate rootfs
ROOTFS_DIR=$ROOTFS ./unpack_yocto_packages.sh \
  $build_dir/tmp/deploy/rpm/aarch64/ \
  $build_dir/tmp/pkgdata/zcu111-zynqmp/runtime \
  $PACKAGES || { package_not_found ; exit 1 ; }

# Cleanup rootfs for zcu111
# TODO: incorporate these changes into yocto recipes
find $ROOTFS/etc/init.d -type f -exec sed -i "s/@STARTUP_APP@/MplaneOranrrhProcess/g" {} \;
cp $ROOTFS/usr/bin/openssl $ROOTFS/bin/openssl
cp $ROOTFS/usr/bin/openssl $ROOTFS/usr/local/bin/openssl

# Create archive
curdir=$(realpath .)
{ 
  cd $ROOTFS;
  find . -type f -exec tar rf $ARCHIVE --numeric-owner --owner=0 --group=0 --mode=0755 {} \; ;
  find . -type l -exec tar rf $ARCHIVE --numeric-owner --owner=0 --group=0 --mode=0755 {} \; ;
  mv $ARCHIVE $curdir;
}
