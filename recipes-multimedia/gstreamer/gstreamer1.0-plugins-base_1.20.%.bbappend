FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
		file://gst1.20.3_20220902.1-tcc-gstreamer1.0-plugins-base-riff-parser-can-create-flac-decode-caps.patch \
		file://20200512.1-tcc-gstreamer1.0-plugins-base-Create-allocate-output-function-to-prevent-segment-fault.patch \
		file://gst1.20.3_20220902.2-tcc-gstreamer1.0-plugins-base-add-Telechips-platform-specific-codec-and-support-ringmode.patch \
		file://20200910.1-tcc-gstreamer1.0-plugins-base-playbin-disable-text-play.patch \
		file://20200915.1-tcc-gstreamer1.0-plugins-base-audiodecoder-correct-timestamp.patch \
		file://gst1.20.3_20220902.3-tcc-gstreamer1.0-plugins-base-add-tc-format-to-video-meta.patch \
		file://20201012.1-tcc-gstreamer1.0-plugins-base-allocator-check-memory-type-instread-of-allocator-type.patch \
		file://20210809.1-tcc-gstreamer1.0-plugins-base-add-tc-parameter-for-using-dma-buf.patch \
		file://20221111.1-tcc-gstreamer1.0-plugins-base-mod-typefind-riff-id3v2frame.patch \
		file://20221115.1-tcc-gstreamer1.0-plugins-base-videodecoder-if-pts-is-invalid-use-dts-data.patch \
"
# for tc-dma-buf
#SRC_URI:append = " \
#    ${@oe.utils.conditional('VIDEO_SINK', 'waylandsink', 'file://20201130.1-tcc-gstreamer1.0-plugins-base-riff-high-resolution-jpeg-stream-is-decoded-by-JPU.patch', '', d)} \
#"

ADD_INCLUDE_PATH = " \
	-I${STAGING_KERNEL_DIR}/${KERNEL_MACH_PATH}/include \
	-I${STAGING_KERNEL_DIR}/include/video/tcc \
	-I${STAGING_KERNEL_DIR}/include/video/telechips \
"
CFLAGS:append = " ${ADD_INCLUDE_PATH}"
