SUMMARY = "IEEE 802.1adg utility programs"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/applications/FBC-ORANRRH/802_1agUtils; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/applications/FBC-ORANRRH/802_1agUtils"

inherit cmake mplane-cmake

DEPENDS += "libpcap common"

FILES_${PN} = "/usr/local"

do_install_append () {
  mkdir -p ${D}/usr/local
  mv ${D}/usr/bin ${D}/usr/local
}

