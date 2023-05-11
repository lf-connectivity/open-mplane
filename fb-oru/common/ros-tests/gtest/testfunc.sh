#!/bin/sh
#
# Run the specified function
#
source image-mgr.sh

IMAGE_DIR=${1:-/nandflash}
TMP_DIR=${2:-/tmp}
func=${3:-runRetry}

imageMgr $IMAGE_DIR $TMP_DIR 0 1

eval $func $4 $5 $6 $7 $8 $9

