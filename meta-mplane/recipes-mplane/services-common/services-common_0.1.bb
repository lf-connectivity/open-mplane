SUMMARY = "Common sources for the M-Plane services library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/services-common; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/services-common"

inherit cmake mplane-cmake

DEPENDS += "xcommon common hardware-common vhi vsi"
