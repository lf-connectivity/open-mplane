SUMMARY = "Virtual Hardware Interface for M-Plane Server"
DESCRIPTION = "Open M-Plane Server"
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/hardware/vhi/inc; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/hardware/vhi/inc"

# IDpdControl.h is duplicated in VSI and VHI. The duplicate files conflict in
# when downstream recipes which DEPENDS on both VSI and VHI execute setscene
# tasks. Rename IDpdControl.h when installing VHI.
do_rename_idpdcontrol () {
    mv ${S}/IDpdControl.h ${S}/IDpdControlVHI.h
}

addtask do_rename_idpdcontrol before do_configure after do_patch

inherit cmake mplane-cmake
