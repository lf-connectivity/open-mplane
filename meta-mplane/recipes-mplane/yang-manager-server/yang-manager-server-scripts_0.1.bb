SUMMARY = "yang-manager-server scripts to put in the rootfs"
DESCRIPTION = ""
SECTION = "core"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://fb-oru/yang-manager-server/cmake/rootfs/etc"

S = "${WORKDIR}"

RDEPENDS_${PN} += "bash"

FILES_${PN} = "/etc"

TARGET_DIR="${D}"
SOURCE_DIR="${S}/fb-oru/yang-manager-server/cmake/rootfs"

inherit mplane-install
