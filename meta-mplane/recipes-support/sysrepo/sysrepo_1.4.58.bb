SUMMARY = ""
DESCRIPTION = ""
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRC_URI = "git://github.com/sysrepo/sysrepo.git;protocol=https;branch=master"
SRCREV = "5b9b175ea3eac005bce1c13d24b09e56bfbdb55b"

S = "${WORKDIR}/git"

inherit cmake pkgconfig

DEPENDS = "yang"
RDEPENDS_${PN} = "openssl"

EXTRA_OECMAKE_append = " -DGEN_LANGUAGE_BINDINGS=ON"
EXTRA_OECMAKE_append = " -DGEN_CPP_BINDINGS=ON"
EXTRA_OECMAKE_append = " -DGEN_PYTHON_BINDINGS=OFF"
EXTRA_OECMAKE_append = " -DENABLE_PYTHON_TESTS=OFF"
EXTRA_OECMAKE_append = " -DBUILD_EXAMPLES=OFF"
EXTRA_OECMAKE_append = " -DCMAKE_BUILD_TYPE:String=Release"
EXTRA_OECMAKE_append = " -DENABLE_TESTS:String=False"
EXTRA_OECMAKE_append = " -DREPOSITORY_LOC:PATH=/etc/sysrepo"
EXTRA_OECMAKE_append = " -DCALL_TARGET_BINS_DIRECTLY=False"

do_install_append () {
    rm -rf ${D}/usr/lib/pkgconfig/

    mkdir -p ${D}/usr/local/
    mv ${D}/usr/bin ${D}/usr/local
}

FILES_${PN} = "${bindir} ${libdir} /usr/local/"
FILES_${PN}-dev = "${includedir} \
                   ${libdir}/libsysrepo.so \
                   ${libdir}/libsysrepo-cpp.so \
                  "
