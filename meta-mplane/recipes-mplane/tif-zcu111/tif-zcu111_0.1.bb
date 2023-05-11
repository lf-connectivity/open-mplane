SUMMARY = "tif-zcu111 common library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/tif/ZCU111; \
           file://fb-oru/tif/helper/ZCU111; \
           file://fb-oru/tif/helper/ORANRRH; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/tif/ZCU111"

inherit cmake mplane-cmake

DEPENDS += "xcommon common hardware-common vhi vsi vyms yang-manager-server swtools-shared tif-common tif-common-model"
