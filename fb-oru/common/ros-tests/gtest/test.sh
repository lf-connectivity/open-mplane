#!/bin/sh

source image-mgr.sh

IMAGE_DIR=${1:-/nandflash}
TMP_DIR=${2:-/tmp}

imageMgr $IMAGE_DIR $TMP_DIR

runRetry

