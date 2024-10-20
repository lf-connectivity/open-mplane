SUMMARY = "Generic M-Plane HAL"
DESCRIPTION = "Open M-Plane Server"
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://libhalmplane"

S = "${WORKDIR}/libhalmplane"

inherit cmake

# set this as appropriate
BUILD_BOARD ?= "example"
BUILD_BOARD_STYLE ?= "BUILTIN"

EXTRA_OECMAKE_append += " -DBUILD_BOARD=${BUILD_BOARD}"
EXTRA_OECMAKE_append += " -DBUILD_BOARD_STYLE=${BUILD_BOARD_STYLE}"
EXTRA_OECMAKE_append += " -DCONTEXT=YOCTO"

DEPENDS += "libtinyxml2"

PROVIDES += "virtual/halmplane"
RPROVIDES_${PN} += "virtual/halmplane"
