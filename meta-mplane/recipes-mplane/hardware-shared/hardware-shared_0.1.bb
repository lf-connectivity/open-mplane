SUMMARY = "Open M-Plane FB-ORU Shared Hardware Library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/hardware/shared/common; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/hardware/shared/common"

inherit cmake mplane-cmake

# TODO: fpga-zcu111 should be some common fpga recipe instead.
DEPENDS += "xcommon common hardware-common fpga-zcu111 vhi libtinyxml2"
