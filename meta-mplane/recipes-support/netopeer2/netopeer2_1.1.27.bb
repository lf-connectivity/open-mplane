SUMMARY = ""
DESCRIPTION = ""
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=41daedff0b24958b2eba4f9086d782e1"

SRC_URI = "git://github.com/CESNET/netopeer2.git;protocol=https;branch=master \
           file://netconf_nmda_bugfix.patch"

SRCREV = "acf575ca5f0cf1337a325f5bec0898f53b5a568a"

S = "${WORKDIR}/git"

inherit cmake

DEPENDS = "yang sysrepo netconf2 curl libssh openssl"
RDEPENDS_${PN} = "openssl openssl-bin bash"

FILES_${PN} = "/usr/local/bin"

netopeer_extras_dir = "/usr/share/netopeer2"
FILES_${PN} += "${netopeer_extras_dir}"

# TODO: replace sed commands and process shell templates better
do_install () {
  mkdir -p ${D}/usr/local/bin
  cp ${B}/netopeer2-cli ${D}/usr/local/bin/netopeer2-cli
  cp ${B}/netopeer2-server ${D}/usr/local/bin/netopeer2-server

  install -dm0750 ${D}${netopeer_extras_dir}/modules
  for file in ${S}/modules/*.yang; do
    install $file ${D}${netopeer_extras_dir}/modules
  done

  install -Dm0755 ${S}/scripts/setup.sh.in ${D}${netopeer_extras_dir}/scripts/setup.sh
  install -Dm0755 ${S}/scripts/merge_hostkey.sh.in ${D}${netopeer_extras_dir}/scripts/merge_hostkey.sh
  install -Dm0755 ${S}/scripts/merge_config.sh.in ${D}${netopeer_extras_dir}/scripts/merge_config.sh

  sed -i 's/@SYSREPOCTL@/\/usr\/local\/bin\/sysrepoctl/g' ${D}${netopeer_extras_dir}/scripts/setup.sh
  sed -i 's/@MODULES_DIR@/\/usr\/share\/netopeer2\/modules/g' ${D}${netopeer_extras_dir}/scripts/setup.sh
  sed -i 's/@MODULES_OWNER@/root/g' ${D}${netopeer_extras_dir}/scripts/setup.sh
  sed -i 's/@MODULES_GROUP@/root/g' ${D}${netopeer_extras_dir}/scripts/setup.sh
  sed -i 's/@SYSREPOCFG@/\/usr\/local\/bin\/sysrepocfg/g' ${D}${netopeer_extras_dir}/scripts/merge_hostkey.sh
  sed -i 's/@OPENSSL@/\/usr\/bin\/openssl/g' ${D}${netopeer_extras_dir}/scripts/merge_hostkey.sh
  sed -i 's/@SYSREPOCFG@/\/usr\/local\/bin\/sysrepocfg/g' ${D}${netopeer_extras_dir}/scripts/merge_config.sh
}
