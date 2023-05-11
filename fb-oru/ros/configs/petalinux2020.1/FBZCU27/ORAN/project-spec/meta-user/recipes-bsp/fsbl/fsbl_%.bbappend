#PATCHTOOL = "git"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI  += " \
        file://added-gigadevice-nor-qspi-support.patch \
        "

do_configure_append() {
    # Copy over psu_init.c generated from XSA hardware file
    install -m 0644 ${TOPDIR}/../project-spec/hw-description/psu_init.c ${B}/fsbl/psu_init.c
#   install -m 0644 ${TOPDIR}/../project-spec/hw-description/psu_init.h ${B}/fsbl/psu_init.h

    # XXX: HACK: Disable init_serdes in boot and ddr refresh"
    grep -n "init_serdes()" ${B}/fsbl/psu_init.c | \
      cut --delimiter=: -f 1 | \
      xargs -I {} sed -i "{} s/./\/\/&/" ${B}/fsbl/psu_init.c
}

#Enable appropriate FSBL debug or compiler flags
#YAML_COMPILER_FLAGS_append = " -DFSBL_DEBUG_DETAILED"
