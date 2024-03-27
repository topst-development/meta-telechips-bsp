DESCRIPTION = "Telechips OMX Decoder library"
SECTION = "libs"

LICENSE = "LGPL-2.1-only & Telechips"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/LGPL-2.1-only;md5=1a6d268fd218675ffea8be556788b780 \
                    file://src/omx/omx_include/tcc_audio_common.h;beginline=1;endline=16;md5=bbbd5733d2f0be44ccf56e2c3b509ab2 \
                    file://src/omx/omx_include/tcc_video_common.h;beginline=1;endline=16;md5=133307b648fca781317bcbbde9cf88af"

inherit autotools-brokensep pkgconfig

SRC_URI = "${TELECHIPS_AUTOMOTIVE_MULTIMEDIA_GIT}/libomxil-telechips.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
SRC_URI += "file://libomxil-bellagio.pc"

SRCREV = "c4584099dbb37dfa7b5c2e7ca9f14cd5d4a2c508"

DEPENDS = "libcdk-audio libcdk-video glib-2.0 virtual/kernel"

PATCHTOOL = "git"

S = "${WORKDIR}/git"

ADD_INCLUDE_PATH = " \
	-I${STAGING_DIR_HOST}/usr/include/glib-2.0 \
	-I${STAGING_DIR_HOST}/usr/lib/glib-2.0/include \
	-I${STAGING_KERNEL_DIR}/include/video/tcc \
	-I${STAGING_KERNEL_DIR}/include/video/telechips \
	-I${STAGING_KERNEL_BUILDDIR}/include \
"

EXTRA_OECONF += "PROCESSOR=${TCC_ARCH_FAMILY}"
CFLAGS:append = " ${ADD_INCLUDE_PATH}"
CFLAGS:append = " ${@bb.utils.contains('INVITE_PLATFORM', 'support-4k-video', '-DSUPPORT_4K_VIDEO', '', d)}"
CFLAGS:append = " ${@bb.utils.contains_any('VIDEO_SINK', 'waylandsink', '-DFORCE_DISABLE_MAP_CONVERTER', '', d)}"

PROVIDES += "virtual/libomxil"

do_install:append() {
	install -d ${D}${includedir}
	install -d ${D}${libdir}/pkgconfig

	install -m 0644 ${WORKDIR}/libomxil-bellagio.pc ${D}${libdir}/pkgconfig/
	cp -ap ${S}/src/omx/omx_include/* ${D}${includedir}
}

PACKAGES = "${PN} ${PN}-dev ${PN}-staticdev ${PN}-dbg"
INSANE_SKIP:${PN} += "installed-vs-shipped dev-so textrel"

FILES:${PN} += "${libdir}/*.so \
                ${libdir}/*${SOLIBS} \
"
FILES:${PN}-staticdev += "${libdir}/*.a \
"
FILES:${PN}-dev += "${libdir}/*.la \
                    ${libdir}/*${SOLIBSDEV} \
"
FILES:${PN}-dbg += "${libdir}/.debug/ \
"

RDEPENDS:${PN} += " \
	libcdk-audio \
"

