#! /bin/bash

# How many parallel threads to run when building mpclient; 1 thread by default
PARALLEL=1

# Parse options
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        --parallel|-j)  # Build in parallel threads
            PARALLEL=$2
            shift
            shift
            ;;
        *)
            echo "Unknown option '$1'"
            shift
            ;;
    esac
done

mkdir -p ../build
cd ../build
cmake ..
./wrapper.sh make -j $PARALLEL
cd ..
