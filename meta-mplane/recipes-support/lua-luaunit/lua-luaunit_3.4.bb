DESCRIPTION = "A unit testing framework for Lua"
HOMEPAGE = "https://github.com/bluebird75/luaunit"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=3cbaf542c6e9a9dcad6c372227ac49a1"

SRCREV = "ddee11c5069c699f4fc6e6c0cea1f1c11dddc373"
SRC_URI = "git://github.com/bluebird75/luaunit.git;protocol=https;branch=master \
"

S = "${WORKDIR}/git"

RDEPENDS_${PN} = "luajit"

do_install () {
    luadir="${datadir}/lua/5.1"
    # move 'luaunit.lua' to lua module path
    install -m 0755 -d ${D}${luadir}/
    install -D -m 0755 ${S}/luaunit.lua ${D}${luadir}/
}

FILES_${PN} = "${datadir}"
