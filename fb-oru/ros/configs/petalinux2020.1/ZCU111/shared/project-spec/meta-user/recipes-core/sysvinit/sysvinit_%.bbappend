# sysvinit_%.bbappend content
do_install_prepend () {
        sed -i 's/VERBOSE=no/VERBOSE=very/' ${WORKDIR}/rcS-default
}
