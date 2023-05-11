SUMMARY = "ZCU111 ORAN RRH Hardware Library"
DESCRIPTION = "Open M-Plane Server"
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/hardware/ZCU111_ORANRRH; \
           file://fb-oru/hardware/shared/common; \
           file://fb-oru/hardware/shared/zcu111-radio; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/hardware/ZCU111_ORANRRH"

inherit cmake mplane-cmake

DEPENDS += " \
            xcommon \
            common \
            hardware-common \
            hardware-shared \
            hardware-zcu111 \
            sysfsutils \
           "
