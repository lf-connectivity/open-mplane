SUMMARY = "Virtual Service Interface for M-Plane Server"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/services/vsi/inc; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/services/vsi/inc"

inherit cmake mplane-cmake
