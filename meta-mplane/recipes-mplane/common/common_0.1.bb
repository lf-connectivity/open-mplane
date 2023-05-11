SUMMARY = "common library"
DESCRIPTION = "Common utilities for FB-ORU software"
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/common; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/common"

inherit cmake mplane-cmake

DEPENDS += "xcommon"

EXTRA_OECMAKE_append = " -DCFG_DATA_PATH=/nandflash/configdata"
