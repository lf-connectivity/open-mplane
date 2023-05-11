SUMMARY = "Yang Manager Server Library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/yang-manager-server; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/yang-manager-server"

inherit cmake mplane-cmake

DEPENDS += " \
  xcommon \
  common \
  virtual/halmplane \
  hardware-common \
  hardware-zcu111-oranrrh \
  fpga-zcu111 \
  services-common \
  services-shared \
  services-zcu111 \
  services-oranrrh \
  services-zcu111-oranrrh \
  vhi \
  vsi \
  vyms \
  zlib \
  libssh \
  netconf2 \
  netopeer2 \
  sysrepo \
  yang \
  libtinyxml2 \
  "

# TODO: Fill these out with meaningful values
CXXFLAGS += "-DPRODUCT_CODE='\"foo\"'"
CXXFLAGS += "-DNETOPEER_PATH='\"\/usr\/local\/bin\"'"
CXXFLAGS += "-DDOT1AGD_PATH='\"\/usr\/local\/bin\"'"
CXXFLAGS += "-DYANG_MODS_PATH='\"\/nandflash\/yangfiles\"'"
