#
# This file is the sshd-config recipe.
#

SUMMARY = "Replace SSH server config"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://sshd-config file://sshd-keys \
	"

S = "${WORKDIR}"

do_install() {
     install -d ${D}${sysconfdir}/init.d
     install -m 0755 ${S}/sshd-config ${D}${sysconfdir}/init.d
     install -m 0755 ${S}/sshd-keys ${D}${sysconfdir}/init.d
     install -d ${D}${sysconfdir}/rc2.d
     install -d ${D}${sysconfdir}/rc3.d
     install -d ${D}${sysconfdir}/rc4.d
     install -d ${D}${sysconfdir}/rc5.d
     ln -s ../init.d/sshd-config ${D}${sysconfdir}/rc2.d/S99sshd-config
     ln -s ../init.d/sshd-keys ${D}${sysconfdir}/rc2.d/S08sshd-keys
     ln -s ../init.d/sshd-config ${D}${sysconfdir}/rc3.d/S99sshd-config
     ln -s ../init.d/sshd-keys ${D}${sysconfdir}/rc3.d/S08sshd-keys
     ln -s ../init.d/sshd-config ${D}${sysconfdir}/rc4.d/S99sshd-config
     ln -s ../init.d/sshd-keys ${D}${sysconfdir}/rc4.d/S08sshd-keys
     ln -s ../init.d/sshd-config ${D}${sysconfdir}/rc5.d/S99sshd-config
     ln -s ../init.d/sshd-keys ${D}${sysconfdir}/rc5.d/S08sshd-keys
}
