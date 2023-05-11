SUMMARY = "Common files to put in the rootfs"
DESCRIPTION = ""
SECTION = "core"
LICENSE = "Meta-MIT"
LIC_FILES_CHKSUM = "file://${META_MPLANE_DIR}/licenses/Meta-MIT;md5=ae79e563b8a09c8fc37978f18dbaa640"

FILESEXTRAPATHS_append := ":${META_MPLANE_DIR}/.."

SRC_URI = "file://fb-oru/applications/common-rootfs/rootfs/common"

S = "${WORKDIR}"

RDEPENDS_${PN} += "bash"

FILES_${PN} = "/etc /usr"

STARTUP_APP="MplaneOranrrhProcess"

TARGET_DIR="${D}"
SOURCE_DIR="${S}/fb-oru/applications/common-rootfs/rootfs/common"

inherit mplane-install

do_substitute () {
  mkdir -p ${SOURCE_DIR}/etc/init.d/app.d/
  find ${SOURCE_DIR} -type f -exec sed -i "s/@STARTUP_APP@/${STARTUP_APP}/g" {} \;
  cp ${SOURCE_DIR}/etc/init.d/30_app.sh.in ${SOURCE_DIR}/etc/init.d/app.d/30_app.sh
  cp ${SOURCE_DIR}/etc/init.d/30_app.sh.in ${SOURCE_DIR}/etc/init.d/30_app.sh
}

addtask do_substitute before do_install after do_compile
