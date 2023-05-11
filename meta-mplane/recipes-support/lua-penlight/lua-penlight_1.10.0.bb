DESCRIPTION = "A set of pure Lua libraries focusing on input data handling, \
functional programming, and OS path management."
HOMEPAGE = "https://github.com/lunarmodules/Penlight"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.md;md5=0a2993b604147dcce1ea113b72b618cd"

SRCREV = "230980552484198e5b3fc0dd916002738eeafc51"
SRC_URI = "git://github.com/lunarmodules/Penlight.git;protocol=https;branch=master \
"

S = "${WORKDIR}/git"

RDEPENDS_${PN} = "luajit"

do_install () {
    luadir="${datadir}/lua/5.1"

    # move 'pl' to lua module path
    install -m 0755 -d ${D}${luadir}/pl/
    install -D -m 0755 ${S}/lua/pl/* ${D}${luadir}/pl/
}

FILES_${PN} = "${datadir}"
