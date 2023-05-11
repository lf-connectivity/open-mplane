DESCRIPTION = "Yang IETF modules"
SECTION = "core"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://fb-oru/oran-libs/cmake/rootfs/etc/yang-modules"

S = "${WORKDIR}"

FILES_${PN} = "/etc"

TARGET_DIR="${D}/etc/yang-modules"
SOURCE_DIR="${S}/fb-oru/oran-libs/cmake/rootfs/etc/yang-modules"

inherit mplane-install
