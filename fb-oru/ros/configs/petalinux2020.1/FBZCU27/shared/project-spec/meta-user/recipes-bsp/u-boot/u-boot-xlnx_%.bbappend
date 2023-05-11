SRC_URI_append = " file://platform-top.h"
SRC_URI += "file://bsp.cfg"
SRC_URI += "file://0001-u-boot-Enable-eth0-on-FBZCU27RLB-board.patch"
SRC_URI += "file://0002-u-boot-Enable-emmc-boot-on-FBZCU27RLB-board.patch"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PATCHTOOL = "git"

do_configure_append () {
        if [ "${U_BOOT_AUTO_CONFIG}" = "1" ]; then
                install ${WORKDIR}/platform-auto.h ${S}/include/configs/
                install ${WORKDIR}/platform-top.h ${S}/include/configs/
        fi
}

do_configure_append_microblaze () {
        if [ "${U_BOOT_AUTO_CONFIG}" = "1" ]; then
                install -d ${B}/source/board/xilinx/microblaze-generic/
                install ${WORKDIR}/config.mk ${B}/source/board/xilinx/microblaze-generic/
        fi
}
