SRC_URI += "file://plnx_kernel.cfg \
            "

do_configure[depends] += "kern-tools-native:do_populate_sysroot"
SRC_URI_append ="\ 
        file://plnx_kernel.cfg \ 
        file://bsp.cfg \ 
        file://0001-ptp-Add-support-for-1588-timer.patch \ 
"
RDEPENDS_kernel-base = ""
FILESEXTRAPATHS_prepend := "${THISDIR}/configs:"
KERNEL_IMAGETYPE_zynq ?= "zImage"
do_deploy_append () {
               install -m 0644 ${D}/boot/System.map-${KERNEL_VERSION} ${DEPLOYDIR}/System.map.linux
}

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
