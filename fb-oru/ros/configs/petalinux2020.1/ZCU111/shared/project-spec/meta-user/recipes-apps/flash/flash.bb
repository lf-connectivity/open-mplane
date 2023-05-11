#
# This file is the flash recipe.
#

SUMMARY = "Initialise SDCARD as flash storage"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://flash \
	"

S = "${WORKDIR}"

do_install() {
	 install -d ${D}${sysconfdir}/init.d
     install -m 0755 ${S}/flash ${D}${sysconfdir}/init.d
     install -d ${D}${sysconfdir}/rc2.d
     install -d ${D}${sysconfdir}/rc3.d
     install -d ${D}${sysconfdir}/rc4.d
     install -d ${D}${sysconfdir}/rc5.d
     ln -s ../init.d/flash ${D}${sysconfdir}/rc2.d/S04flash
     ln -s ../init.d/flash ${D}${sysconfdir}/rc3.d/S04flash
     ln -s ../init.d/flash ${D}${sysconfdir}/rc4.d/S04flash
     ln -s ../init.d/flash ${D}${sysconfdir}/rc5.d/S04flash
	     
}
