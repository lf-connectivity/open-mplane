SUMMARY = "Virtual Yang Mangaer Server Interface for M-Plane Server"
DESCRIPTION = "Open M-Plane Server"
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/yang-manager-server/vyms/inc; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/yang-manager-server/vyms/inc"

inherit cmake mplane-cmake
