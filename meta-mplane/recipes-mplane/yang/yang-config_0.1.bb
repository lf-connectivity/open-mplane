DESCRIPTION = "Yang startup configuration"
SECTION = "core"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"


FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://fb-oru/yang-manager-server/yang-config"

S = "${WORKDIR}"

FILES_${PN} = "/usr"

TARGET_DIR="${D}/usr/share/yang-config"
SOURCE_DIR="${S}/fb-oru/yang-manager-server/yang-config"

inherit mplane-install
