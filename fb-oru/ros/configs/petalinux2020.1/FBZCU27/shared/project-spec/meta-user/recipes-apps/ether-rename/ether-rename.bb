#
# Ensure 1G ethernet port is named "eth0"
#

SUMMARY = "Ensure 1G ethernet port is named 'eth0'"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://ether-rename  \
	"

S = "${WORKDIR}"

do_install() {
     install -d ${D}${sysconfdir}/init.d
     install -m 0755 ${S}/ether-rename ${D}${sysconfdir}/init.d
     install -d ${D}${sysconfdir}/rc2.d
     install -d ${D}${sysconfdir}/rc3.d
     install -d ${D}${sysconfdir}/rc4.d
     install -d ${D}${sysconfdir}/rc5.d
     ln -s ../init.d/ether-rename ${D}${sysconfdir}/rc2.d/S70ether-rename
     ln -s ../init.d/ether-rename ${D}${sysconfdir}/rc3.d/S70ether-rename
     ln -s ../init.d/ether-rename ${D}${sysconfdir}/rc4.d/S70ether-rename
     ln -s ../init.d/ether-rename ${D}${sysconfdir}/rc5.d/S70ether-rename
}
