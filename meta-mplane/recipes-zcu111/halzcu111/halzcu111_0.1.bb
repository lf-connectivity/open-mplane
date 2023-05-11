SUMMARY = "ZCU111 M-Plane HAL"
DESCRIPTION = "Open M-Plane Server"
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://libhalmplane"

S = "${WORKDIR}/libhalmplane"

inherit cmake

FILES_SOLIBSDEV = ""
FILES_${PN} += "${includedir} ${libdir}"

DEPENDS += "xcommon common vhi i2cdetect"
RDEPENDS_${PN} += "i2cdetect"

BUILD_BOARD = "zcu111"
EXTRA_OECMAKE_append += " -DBUILD_BOARD=${BUILD_BOARD}"
EXTRA_OECMAKE_append += " -DCONTEXT=YOCTO"

PROVIDES += "virtual/halmplane"
RPROVIDES_${PN} += "virtual/halmplane"
