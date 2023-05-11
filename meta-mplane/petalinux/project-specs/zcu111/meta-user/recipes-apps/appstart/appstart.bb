#
# This file is the appstart recipe.
#

SUMMARY = "Start main application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://appstart file://appTarball file://prog-fpga"

S = "${WORKDIR}"

do_install() {
     install -d ${D}${bindir}
     install -m 0755 prog-fpga ${D}${bindir}

	 install -d ${D}${sysconfdir}/init.d
	 install -d ${D}${sysconfdir}/init.d/app.d
     install -m 0755 ${S}/appstart ${D}${sysconfdir}/init.d
     install -m 0755 ${S}/appTarball ${D}${sysconfdir}/init.d
     install -d ${D}${sysconfdir}/rc2.d
     install -d ${D}${sysconfdir}/rc3.d
     install -d ${D}${sysconfdir}/rc4.d
     install -d ${D}${sysconfdir}/rc5.d

     ln -s ../init.d/appTarball ${D}${sysconfdir}/rc2.d/S80appTarball
     ln -s ../init.d/appTarball ${D}${sysconfdir}/rc3.d/S80appTarball
     ln -s ../init.d/appTarball ${D}${sysconfdir}/rc4.d/S80appTarball
     ln -s ../init.d/appTarball ${D}${sysconfdir}/rc5.d/S80appTarball
     
     ln -s ../init.d/appstart ${D}${sysconfdir}/rc2.d/S90appstart
     ln -s ../init.d/appstart ${D}${sysconfdir}/rc3.d/S90appstart
     ln -s ../init.d/appstart ${D}${sysconfdir}/rc4.d/S90appstart
     ln -s ../init.d/appstart ${D}${sysconfdir}/rc5.d/S90appstart
}

DEPENDS += " packagegroup-mplane netopeer2 "
RDEPEDNS_${PN} += " packagegroup-mplane netopeer2 "
