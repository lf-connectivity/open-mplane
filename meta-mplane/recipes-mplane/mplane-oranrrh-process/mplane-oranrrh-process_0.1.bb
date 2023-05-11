SUMMARY = "mplane-oranrrh-process library"
DESCRIPTION = ""
SECTION = "base"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

SRC_URI = "file://fb-oru/applications/MPLANE-ORANRRH/MplaneOranrrhProcess; \
           file://CMakeLists.txt; \
          "

S = "${WORKDIR}/fb-oru/applications/MPLANE-ORANRRH/MplaneOranrrhProcess"

inherit cmake mplane-cmake

DEPENDS += "xcommon \
            common \
            services-common \
            services-oranrrh \
            services-shared \
            services-zcu111 \
            services-zcu111-oranrrh \
            virtual/halmplane \
            vhi \
            vsi \
            swtools-shared \
            tif-common \
            tif-common-model \
            tif-zcu111-mplane-oranrrh \
            tif-zcu111-oranrrh \
            tif-zcu111 \
            yang-manager-server \
            applications-common \
            applications-common-specific \
           "

FILES_${PN} += "/bin"

do_install_append () {
    mkdir ${D}/bin
    mv ${D}/usr/bin/* ${D}/bin/
    rm -r ${D}/usr/bin
}
