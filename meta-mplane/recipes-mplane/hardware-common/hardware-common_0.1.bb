SUMMARY = "hardware-common Library"
DESCRIPTION = "Common hardware utilities and interfaces for FB-ORU software"
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/hardware/common; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/hardware/common"

inherit cmake mplane-cmake

DEPENDS += "xcommon common vhi vsi libtinyxml2"
