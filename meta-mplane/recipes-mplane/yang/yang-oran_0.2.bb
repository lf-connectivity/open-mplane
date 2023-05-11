DESCRIPTION = "Yang ORAN modules"
SECTION = "core"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"


FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://fb-oru/yang-models"

S = "${WORKDIR}"

FILES_${PN} = "/usr"

TARGET_DIR="${D}/usr/share/yang-models"
SOURCE_DIR="${S}/fb-oru/yang-models/ORAN-WG4.MP-YANGs-v0x.00"

inherit mplane-install
