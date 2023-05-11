do_install_append () {
  mv ${D}${bindir}/luajit* ${D}${bindir}/luajit
}

FILES_${PN} += "/usr/bin/*"
