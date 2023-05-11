DESCRIPTION = "Feature-rich command line parser for Lua"
HOMEPAGE = "https://github.com/luarocks/argparse"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=121fa4cef6513eb48482998ce7805bad"

# NOTE: Using a fork of original: https://github.com/mpeterv/argparse
# The original is no longer maintained.

SRCREV = "27967d7b52295ea7885671af734332038c132837"
SRC_URI = "git://github.com/luarocks/argparse.git;protocol=https;branch=master \
"

S = "${WORKDIR}/git"

RDEPENDS_${PN} += "luajit"

do_install () {
    luadir="${datadir}/lua/5.1"
    install -m 0755 -d ${D}${luadir}/
    install -D -m 0755 ${S}/src/argparse.lua ${D}${luadir}/
}

FILES_${PN} += "${datadir}"
