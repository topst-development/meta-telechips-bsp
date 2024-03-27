include libcdk.inc

LIC_FILES_CHKSUM = "file://include/tcc_audio_interface.h;beginline=1;endline=31;md5=ee857ba4f0e423eaf3df666efd399ce0"
S = "${WORKDIR}/git/audiocodec"

do_configure:append() {
  if ${@bb.utils.contains('INVITE_PLATFORM', 'commercial', 'true', 'false', d)}; then
    if ${@bb.utils.contains('SUPPORTED_COMMERCIAL_LIST', 'ddp', 'true', 'false', d)}; then
      touch ${S}/ddpdec/ddpdec.c
      sed -i '$ a libtccac3dec_la_LDFLAGS = -lm\nlibtccac3dec_la_LIBADD += -lglib-2.0' ${S}/ddpdec/Makefile.am
      sed -i '$ a libtccac3dec_la_CFLAGS += -I$(LINUX_PLATFORM_ROOTDIR)/prebuilts/include/glib-2.0' ${S}/ddpdec/Makefile.am
      sed -i '$ a libtccac3dec_la_CFLAGS += -I$(LINUX_PLATFORM_ROOTDIR)/prebuilts/lib/glib-2.0/include' ${S}/ddpdec/Makefile.am
    fi
  fi
}

do_install:append() {
	rm -rf ${D}${includedir}
}
