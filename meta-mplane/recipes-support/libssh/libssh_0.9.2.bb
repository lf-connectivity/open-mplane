UMMARY = "Multiplatform C library implementing the SSHv2 and SSHv1 protocol"
HOMEPAGE = "http://www.libssh.org"
SECTION = "libs"
LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://COPYING;md5=dabb4958b830e5df11d2b0ed8ea255a0"

FILESEXTRAPATHS_append := ":${THISDIR}/files"

DEPENDS = "zlib openssl"

SRC_URI = "git://git.libssh.org/projects/libssh.git;protocol=https;branch=stable-0.9 \
           file://libcrypto-Added-check-for-cipher-aes_key-being-NULL.patch \
          "
SRCREV = "389efc234b2dc65246b695188881e6056e369588"

S = "${WORKDIR}/git"

inherit cmake

PACKAGECONFIG ??=""
PACKAGECONFIG[gssapi] = "-DWITH_GSSAPI=1, -DWITH_GSSAPI=0, krb5, "

ARM_INSTRUCTION_SET_armv5 = "arm"

EXTRA_OECMAKE = " \
    -DWITH_GCRYPT=0 \
    -DWITH_PCAP=1 \
    -DWITH_SFTP=1 \
    -DWITH_ZLIB=1 \
    -DLIB_SUFFIX=${@d.getVar('baselib').replace('lib', '')} \
    "

do_configure_prepend () {
    # Disable building of examples
    sed -i -e '/add_subdirectory(examples)/s/^/#DONOTWANT/' ${S}/CMakeLists.txt \
        || bbfatal "Failed to disable examples"
}

TOOLCHAIN = "gcc"

