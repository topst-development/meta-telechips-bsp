FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
	file://gst1.20.3_20200611.1-tcc-gstreamer1.0-omx-add-telechips-audio-codec.patch \
	file://20200622.1-tcc-gstreamer1.0-omx-add-telechips-video-codec.patch \
	file://gst1.20.3_20220906.1-tcc-gstreamer1.0-omx-add-flushed.patch \
	file://20200720.1-tcc-gstreamer1.0-omx-videodec-add-specout-return.patch \
	file://gst1.20.3_20220906.1-tcc-gstreamer1.0-omx-add-telechips-videodec-property.patch \
	file://gst1.20.3_20220906.1-tcc-gstreamer1.0-omx-remove-licence-codec-at-default-setting.patch \
	file://20200915.1-tcc-gstreamer1.0-omx-omxaudiodec-set-output-timestamp.patch \
	file://20201012.1-tcc-gstreamer1.0-omx-change-mjpeg-mimetype-to-video-x-jpeg-for-distinguish-image-jpeg.patch \
	file://20201019.1-tcc-gstreamer1.0-omx-add-omxvideodec-ringmode.patch \
	file://20201201.1-tcc-gstreamer1.0-omx-add_clear_error_state.patch \
	file://20201201.2-tcc-gstreamer1.0-omx-modify-wmv-hack-remove-no-empty-eos-buffer.patch \
	file://gst1.20.3_20210209.1-tcc-gstreamer1.0-omx-add-omxh264enc.patch \
	file://20210225.1-tcc-gstreamer1.0-omx-omxvideodec-add-sinkevent.patch \
	file://20210225.2-tcc-gstreamer1.0-omx-omxaudiodec-omxvideodec-prevent-seek-dead-lock.patch \
	file://20210518.1-tcc-gstreamer1.0-omx-omxbufferpool-dont-need-copy-set.patch \
	file://20210929.1-tcc-gstreamer1.0-omx-omxvideodec-set-output-pts-if-frame-pts-is-null.patch \
	file://20211104.1-tcc-gstreamer1.0-omx-add-code-for-divx-enable.patch \
	file://20211122.1-tcc-gstreamer1.0-omx-fix-multi-audio-decoding-to-play.patch \
	${@bb.utils.contains_any('TCC_ARCH_FAMILY', 'tcc897x', '', '${WAYLAND_SINK_PATCH}', d)} \
	file://20221111.1-tcc-gstreamer1.0-omx-set-can-support-resolution-video-size.patch \
	file://gst1.20.5_20230728.1-tcc-gstreamer1.0-omx-fix-Handle-unsupported-H.265-profiles-for-video-decoder_gstreamer1.0-omx.patch \
"

WAYLAND_SINK_PATCH = " \
	file://gst1.20.3_20220908.1-tcc-gstreamer1.0-omx-support-tc-dmabuf.patch \
"

GSTREAMER_1_0_OMX_TARGET = "bellagio"
GSTREAMER_1_0_OMX_CORE_NAME = "${libdir}/libomxil-tcc.so.0"

DEPENDS += "virtual/kernel"
RDEPENDS:${PN} = "libomxil-telechips"

set_omx_core_name() {
	sed -i -e "s;^core-name=.*;core-name=${GSTREAMER_1_0_OMX_CORE_NAME};" "${D}${sysconfdir}/xdg/gstomx.conf"
}

ADD_INCLUDE_PATH = " \
	-I${STAGING_KERNEL_DIR}/${KERNEL_MACH_PATH}/include \
	-I${STAGING_KERNEL_DIR}/include/video/tcc \
	-I${STAGING_KERNEL_DIR}/include/video/telechips \
	-I${STAGING_KERNEL_BUILDDIR}/include \
"

EXTRA_OECONF += "--enable-h265dec"
EXTRA_OECONF += "PROCESSOR=${TCC_ARCH_FAMILY}"

CFLAGS:append = " ${ADD_INCLUDE_PATH}"
CFLAGS:append = " -D${GST_ARCH_FAMILY_NAME}_INCLUDE"
#CFLAGS:append = " -DSUPPORT_HIGHBPS_OUTPUT"
CFLAGS:append = " ${@bb.utils.contains('INVITE_PLATFORM', 'support-4k-video', '-DSUPPORT_4K_VIDEO', '', d)}"
