SUMMARY = "ORAN RRH ZCU111 sources for the M-Plane services library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/services/ZCU111-FBC-ORANRRH; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/services/ZCU111-FBC-ORANRRH"

inherit cmake mplane-cmake

DEPENDS += " \
  xcommon \
  common \
  hardware-common \
  hardware-zcu111-oranrrh \
  fpga-zcu111 \
  services-common \
  services-shared \
  services-zcu111 \
  services-oranrrh \
  vhi \
  vsi \
  "
