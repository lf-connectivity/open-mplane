DESCRIPTION = "Lua is a powerful light-weight programming language designed \
for extending applications."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=efa3b19feaced71ab67e3649bd67f45e"
HOMEPAGE = "http://www.lua.org/"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/..:${THISDIR}/files"

PR = "r2"

DEPENDS += "readline"
SRC_URI = "http://www.lua.org/ftp/lua-${PV}.tar.gz"

S = "${WORKDIR}/lua-${PV}"

inherit pkgconfig binconfig

TARGET_CC_ARCH += " -fPIC ${LDFLAGS}"
EXTRA_OEMAKE = "'CC=${CC} -fPIC' 'MYCFLAGS=${CFLAGS} -DLUA_USE_LINUX -fPIC' MYLDFLAGS='${LDFLAGS}'"

do_configure_prepend() {
    sed -i -e s:/usr/local:${prefix}:g src/luaconf.h
    sed -i -e s:lib/lua/5.1/:${base_libdir}/lua/5.1/:g src/luaconf.h
}

do_compile () {
    oe_runmake linux
}

do_install () {
    oe_runmake \
        'INSTALL_TOP=${D}${prefix}' \
        'INSTALL_BIN=${D}${bindir}' \
        'INSTALL_INC=${D}${includedir}/' \
        'INSTALL_MAN=${D}${mandir}/man1' \
        'INSTALL_SHARE=${D}${datadir}/lua' \
        'INSTALL_LIB=${D}${libdir}' \
        'INSTALL_CMOD=${D}${libdir}/lua/5.1' \
        install
    install -d ${D}${libdir}/pkgconfig
    install -m 0644 ${S}/etc/lua.pc ${D}${libdir}/pkgconfig/lua5.1.pc
    rmdir ${D}${libdir}/lua/5.1
    rmdir ${D}${libdir}/lua
    rmdir ${D}${datadir}/lua/5.1
    rmdir ${D}${datadir}/lua
}
BBCLASSEXTEND = "native"

SRC_URI[md5sum] = "3e8dfe8be00a744cec2f9e766b2f2aee"
SRC_URI[sha256sum] = "7f5bb9061eb3b9ba1e406a5aa68001a66cb82bac95748839dc02dd10048472c1"
