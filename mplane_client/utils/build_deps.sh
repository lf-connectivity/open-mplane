#! /bin/bash

# Build and install netopeer2 by default
INSTALL_NETOPEER2=true

# Do not install Centos 8 rpms by default
INSTALL_DNF_DEPS=false

# Display Help
display_help()
{
   echo "Usage: build_deps.sh [--no-netopeer2] [--dnf-deps] [--dir <path>] [--help]"
   echo
   echo "options:"
   echo "--no-netopeer2    Disable build/install netopeer2."
   echo "--dnf-deps        Download rpm packages."
   echo "--dir <path>      Specify the path to M-Plane client directory."
   echo "--help            Show this help message and exit."
   echo
}

# Parse options
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        --no-netopeer2)
            INSTALL_NETOPEER2=false
            shift
            ;;
        --dnf-deps)
            INSTALL_DNF_DEPS=true
            shift
            ;;
        --dir)
            if [[ $# -lt 2 ]]; then
                echo "Error: no directory given for --dir"
                exit 1
            fi
            MPLANE_CLIENT_DIR=$2
            shift 2
            ;;
        --help)
            display_help
            exit 0
            ;;
        *)
            echo "'$1' is not a valid options. See '--help'."
            exit 1
            ;;
    esac
done

if [[ -z "$MPLANE_CLIENT_DIR" ]]; then
    if [[ $(git rev-parse --is-inside-work-tree 2>/dev/null) ]]; then
        # Get the absolute path of the root of this repo
        REPO_TOPLEVEL=$(git rev-parse --show-toplevel)
        MPLANE_CLIENT_DIR=$REPO_TOPLEVEL/mplane_client
    else
        echo "Error: could not identify M-Plane client directory"
        exit 1
    fi
fi

cd $MPLANE_CLIENT_DIR/deps
mkdir -p install
mkdir -p install/bin
mkdir -p install/lib

# Symlink lib64 to lib because libyang/libnetconf2/sysrepo use lib and lib64
# depending on platform
if [[ ! -d install/lib64 ]]; then
    ln -s $(pwd)/install/lib install/lib64
fi

# Install Centos 8 rpms
if [[ $INSTALL_DNF_DEPS == true ]]; then
    if [[ -d centos8-rpms ]]; then
        find centos8-rpms -name "*.x86_64.rpm" | xargs sudo dnf install --disablerepo=* --skip-broken -y
    else
        echo "Could not find centos8-rpms dir, not installing rpm deps"
    fi
fi

# Build libssh
mkdir -p libssh-0.9.5/build
cd libssh-0.9.5/build
cmake -D WITH_EXAMPLES=OFF \
      -D CMAKE_INSTALL_PREFIX:PATH='' \
      ..
make -j $(nproc)
make DESTDIR=$(pwd)/../../install install
cd ../..

# Build libyang
mkdir -p libyang/build
cd libyang/build
cmake -D ENABLE_BUILD_TESTS=OFF \
      -D CMAKE_INSTALL_PREFIX:PATH='' \
      ..
make -j $(nproc)
make DESTDIR=$(pwd)/../../install install
cd ../..

# Build libnetconf2
mkdir -p libnetconf2/build
cd libnetconf2/build
cmake -D LIBSSH_INCLUDE_DIR=../../install/include \
      -D LIBSSH_LIBRARY=../../install/lib64/libssh.so \
      -D LIBYANG_INCLUDE_DIR=../../install/include \
      -D LIBYANG_LIBRARY=../../install/lib64/libyang.so \
      -D ENABLE_BUILD_TESTS=OFF \
      -D CMAKE_INSTALL_PREFIX:PATH='' \
      ..
make -j $(nproc)
make DESTDIR=$(pwd)/../../install install
cd ../..

# Build sysrepo
# Not needed for mpclient, but needed by netopeer2
if [[ $INSTALL_NETOPEER2 == true ]]; then
    mkdir -p sysrepo/build
    cd sysrepo/build
    cmake -D LIBYANG_INCLUDE_DIR=../../install/include \
        -D LIBYANG_LIBRARY=../../install/lib64/libyang.so \
        -D CMAKE_INSTALL_PREFIX:PATH='' \
        ..
    make -j $(nproc)
    make DESTDIR=$(pwd)/../../install install
    cd ../..
fi

# Build netopeer2
# Good as a redundant diagnostic tool
mkdir -p netopeer2/build
cd netopeer2/build
if [[ $INSTALL_NETOPEER2 == true ]]; then
    cmake -D LIBSSH_INCLUDE_DIR=../../install/include \
        -D LIBSSH_LIBRARY=../../install/lib64/libssh.so \
        -D LIBYANG_INCLUDE_DIR=../../install/include \
        -D LIBYANG_LIBRARY=../../install/lib64/libyang.so \
        -D SYSREPO_INCLUDE_DIR=../../install/include \
        -D SYSREPO_LIBRARY=../../install/lib64/libsysrepo.so \
        -D LIBNETCONF2_INCLUDE_DIR=../../install/include \
        -D LIBNETCONF2_LIBRARY=../../install/lib64/libnetconf2.so \
        -D CMAKE_INSTALL_PREFIX:PATH='' \
        ..
    make -j $(nproc)
fi
# This script is run so that it precedes another command, e.g.
#    ./wrapper.sh ./mpclient-server
# It adds the locations of YANG models to the variable environment, allowing
# NETCONF to find those dependencies; these are absolute paths, so the script
# can be run from anywhere
cd ../..
echo "#! /bin/bash" > wrapper.sh
echo "LIBYANG_EXTENSIONS_PLUGINS_DIR=$(pwd)/install/lib64/libyang1/extensions \\" >> wrapper.sh
echo "LIBYANG_USER_TYPES_PLUGINS_DIR=$(pwd)/install/lib64/libyang1/user_types \\" >> wrapper.sh
if [[ $INSTALL_NETOPEER2 == true ]]; then
    echo "SYSREPOCTL_EXECUTABLE=$(pwd)/install/bin/sysrepoctl \\" >> wrapper.sh
    echo "SYSREPOCFG_EXECUTABLE=$(pwd)/install/bin/sysrepocfg \\" >> wrapper.sh
fi
echo "LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:$(pwd)/install/lib \\" >> wrapper.sh
echo "\$* &" >> wrapper.sh
echo "pid=\$!" >> wrapper.sh
echo "trap \"kill \$pid; exit 1\" INT" >> wrapper.sh  # Propagate SIGINT to the process inside
echo "wait \$pid" >> wrapper.sh
echo "exit \$?" >> wrapper.sh
chmod +x wrapper.sh
mv wrapper.sh install/bin/wrapper.sh
if [[ $INSTALL_NETOPEER2 == true ]]; then
    cd netopeer2/build
    ./../../install/bin/wrapper.sh make DESTDIR=$(pwd)/../../install install
    cd ../..
fi

# Build gRPC
mkdir -p grpc/cmake/build
cd grpc/cmake/build
cmake -D gRPC_INSTALL=ON \
      -D ABSL_ENABLE_INSTALL=ON \
      -D CARES_ENABLE_INSTALL=ON \
      -D BUILD_DEPS=ON \
      -D BUILD_SHARED_LIBS=ON \
      -D gRPC_SSL_PROVIDER=package \
      -D CMAKE_INSTALL_PREFIX:PATH='' \
      ../..
make -j $(nproc)
make DESTDIR=$(pwd)/../../../install install
cd ../../..

# Build gflags
mkdir -p gflags/build
cd gflags/build
cmake -D CMAKE_INSTALL_PREFIX:PATH='/usr/..' ..  # To avoid a CMake error
make -j $(nproc)
make DESTDIR=$(pwd)/../../install install
cd ../..

# Build glog
mkdir -p glog/build
cd glog/build
cmake -D CMAKE_INSTALL_PREFIX:PATH='' ..
make -j $(nproc)
make DESTDIR=$(pwd)/../../install install
cd ../..

# Build googletest
mkdir -p googletest/build
cd googletest/build
cmake -D CMAKE_INSTALL_PREFIX:PATH='' ..
make -j $(nproc)
make DESTDIR=$(pwd)/../../install install
cd ../..

cd ..

# Add wrapper to build
mkdir build
cp deps/install/bin/wrapper.sh build
