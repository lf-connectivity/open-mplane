#!/bin/bash

set -e
source ./utils/sync_yocto_utils.sh

sync_yocto \
  "https://git.yoctoproject.org/git/poky" \
  "https://github.com/openembedded/meta-openembedded.git"
