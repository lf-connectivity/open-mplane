SUMMARY = "Open M-Plane Server"
DESCRIPTION = "O-RAN Management Plane server application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://mplane_server"

S = "${WORKDIR}/mplane_server"

inherit cmake

DEPENDS += "boost zlib libssh netconf2 netopeer2 sysrepo libtinyxml2 virtual/halmplane"
RDEPENDS_${PN} += "bash"

mplane_server_extras_dir = "/usr/share/mplane-server"
FILES_${PN} += "${mplane_server_extras_dir}"

do_install_append(){
    install -Dm0644 ${S}/yang-manager-server/yang-config/YangConfig.xml ${D}${mplane_server_extras_dir}/YangConfig.xml

    install -d ${D}${mplane_server_extras_dir}/modules
        find ${S}/yang-models/O-RAN.WG4.MP-YANGs-v07.01 -type f -exec cp {} ${D}${mplane_server_extras_dir}/modules \;

    install -dm0755 ${D}${mplane_server_extras_dir}/scripts
    for file in ${S}/scripts/*; do
        install -m0755 $file ${D}${mplane_server_extras_dir}/scripts
    done
}
