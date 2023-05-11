SUMMARY = "m-plane command line interface application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://climp"

S = "${WORKDIR}/climp"

CFLAGS_prepend = "-I ${S}/include"
SOLIBS = ".so"
FILES_SOLIBSDEV = ""

do_install() {
    luadir="${datadir}/lua/5.1/"
    mplanedir="${datadir}/lua/5.1/mplane/"
    testdir="${luadir}/tests/"

    install -d ${D}${bindir}
    install -d ${D}${luadir}
    install -d ${D}${testdir}
    install -d ${D}${mplanedir}

    install -m 0755 ${S}/climp ${D}${bindir}/
    install -m 0755 ${S}/climp_test ${D}${bindir}/

    install -m 0755 ${S}/climp.lua ${D}${luadir}/climp.lua
    install -m 0755 ${S}/tests/climp_test.lua ${D}${testdir}/climp_test.lua

    install -D -m 0755 ${S}/mplane/logger.lua ${D}${mplanedir}/
    install -D -m 0755 ${S}/mplane/hal.lua ${D}${mplanedir}/
}
RDEPENDS_${PN} += "luajit lua-argparse lua-luaunit lua-penlight virtual/halmplane"
DEPENDS += "virtual/halmplane"

FILES_${PN} += "${datadir}"
