#! /bin/bash

cd $(git rev-parse --show-toplevel)/mplane_client/test/docker

# Clone O-RAN simulator
clone_repo=true
if [[ -d ./sim-o1-interface ]] && [[ -n "$(ls -A ./sim-o1-interface)" ]]; then
    echo "Destination path 'sim-o1-interface' already exists and is not an empty directory."
    while true; do
        read -p "Do you wish to overwrite 'sim-o1-interface'? [y/n]" yn
        case ${yn} in
            [Yy]* )
                clone_repo=true
                rm -rf ./sim-o1-interface
                break
                ;;
            [Nn]* )
                clone_repo=false
                break
                ;;
            * ) echo "Please answer y or n.";;
        esac
    done
fi

if [[ ${clone_repo} = true ]]; then
    git config --global advice.detachedHead false
    git clone https://github.com/o-ran-sc/sim-o1-interface

    # Build O-RAN simulator
    cd sim-o1-interface
    git checkout 95f6cc4 # Checkout a recent commit (instead of a tag)
    patch -N -p1 < ../patches/0002-Reconfigure-keys-and-disable-ssh.patch
    cd ntsimulator
    ./nts_build.sh
    cd ../../
fi

# Build M-Plane tester
docker-compose build
