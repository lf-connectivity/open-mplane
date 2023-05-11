#
# This file is the i2cdetect recipe.
#

SUMMARY = "Simple i2cdetect application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://i2cdetect.c \
	   file://i2cbusses.c \
	   file://i2cbusses.h \
	   file://smbus.c \
	   file://smbus.h \
	   file://util.c \
	   file://util.h \
	   file://version.h \
	   file://Makefile \
	   file://i2cdump.c \
	   file://i2cget.c \
	   file://i2cset.c \
		  "

S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 i2cdetect ${D}${bindir}
	     install -m 0755 i2cdump ${D}${bindir}
	     install -m 0755 i2cget ${D}${bindir}
	     install -m 0755 i2cset ${D}${bindir}
}
