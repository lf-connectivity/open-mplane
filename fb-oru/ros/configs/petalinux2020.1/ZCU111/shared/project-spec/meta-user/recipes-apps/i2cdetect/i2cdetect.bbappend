do_install_append() {
	    install -d ${D}${libdir}
	    install -d ${D}${includedir}

	    install -m 0644 libsmbus.so ${D}${libdir}
	    install -m 0755 smbus.h ${D}${includedir}
}
TARGET_CC_ARCH += "${LDFLAGS}"
SOLIBS = "*.so*"
FILES_SOLIBSDEV = ""
