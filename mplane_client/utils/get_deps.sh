#! /bin/bash

# Enable the forward proxy unless explicitly told to disable
export https_proxy=fwdproxy:8080

# Do not download rpm packages unless told to do so
DOWNLOAD_DNF_DEPS=false

# Display Help
display_help()
{
   echo "Usage: get_deps.sh [--no-fwdproxy] [--dnf-deps] [--dir <path>] [--help]"
   echo
   echo "options:"
   echo "--no-fwdproxy     Disable HTTPS forward proxy."
   echo "--dnf-deps        Download rpm packages."
   echo "--dir <path>      Specify the path to M-Plane client directory."
   echo "--help            Show this help message and exit."
   echo
}

# Parse options
script_name=$0
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        --no-fwdproxy)
            unset https_proxy
            shift
            ;;
        --dnf-deps)
            DOWNLOAD_DNF_DEPS=true
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

mkdir -p $MPLANE_CLIENT_DIR/deps
cd $MPLANE_CLIENT_DIR/deps

# Download Centos 8 rpms (build dependencies and tools)
if [[ $DOWNLOAD_DNF_DEPS == true ]]; then
    mkdir -p centos8-rpms
    export no_proxy=".fbcdn.net,.facebook.com,.thefacebook.com,.tfbnw.net,.fb.com,.fburl.com,.facebook.net,.sb.fbsbx.com,localhost"
    dnf download --resolve --alldeps --destdir centos8-rpms --forcearch x86_64 openssl-devel zlib-devel pcre-devel cmake
fi

# Download all dependencies
wget -O libssh-0.9.5.tar.gz https://git.libssh.org/projects/libssh.git/snapshot/libssh-0.9.5.tar.gz
tar -xf libssh-0.9.5.tar.gz && rm libssh-0.9.5.tar.gz
git clone --single-branch --branch v1.0.240 https://github.com/CESNET/libyang
git clone --single-branch --branch v1.1.46 https://github.com/CESNET/libnetconf2
git clone --single-branch --branch v1.4.140 https://github.com/sysrepo/sysrepo
git clone --single-branch --branch v1.1.76 https://github.com/CESNET/netopeer2
git clone --single-branch --branch v1.38.0 https://github.com/grpc/grpc
cd grpc
git submodule update --init
cd ..
git clone --single-branch --branch v2.2.2 https://github.com/gflags/gflags
git clone --single-branch --branch release-1.10.0 https://github.com/google/googletest
git clone --single-branch --branch v0.5.0 https://github.com/google/glog

cd ..
