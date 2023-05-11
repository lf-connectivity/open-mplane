#
# This file is the i2cenv recipe.
#

SUMMARY = "u-boot environment read/write"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://Makefile \
           file://BootEnv.cpp \
           file://BootEnv.h \
           file://BootEnvDevice.cpp \
           file://BootEnvDevice.h \
           file://ByteTransfer.hpp \
           file://Crc.cpp \
           file://Crc.h \
           file://I2cEnv.cpp \
           file://IBootEnv.h \
           file://IBootEnvDevice.h \
           file://Loggable.h \
           file://SingleBootEnv.cpp \
           file://SingleBootEnv.h \
           file://stringfunc.hpp \
           file://Zcu111BootEnv.cpp \
           file://Zcu111BootEnv.h \
		  "

S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 i2cenv ${D}${bindir}
}
