SUMMARY = "application-common-specific library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/applications/common-specific; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/applications/common-specific"

inherit cmake mplane-cmake

DEPENDS += "common vhi swtools-shared tif-common applications-common"
