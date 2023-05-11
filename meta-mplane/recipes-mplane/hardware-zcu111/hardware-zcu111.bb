SUMMARY = "ZCU111 Hardware Library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/hardware/ZCU111; \
           file://fb-oru/hardware/shared/zcu111-radio; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/hardware/ZCU111"

inherit cmake mplane-cmake

DEPENDS += " \
            xcommon \
            common \
            hardware-common \
            hardware-shared \
            sysfsutils \
           "
