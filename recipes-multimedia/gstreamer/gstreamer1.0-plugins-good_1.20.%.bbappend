FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
		file://20200324.1-tcc-gstreamer1.0-plugins-good-add-depth-in-flacparser-caps.patch \
		file://20200324.2-tcc-gstreamer1.0-plugins-good-can-skip-dummydata-in-ac3parser.patch \
		file://20200720.1-tcc-gstreamer1.0-plugins-good-flacparse-Modify-don-t-push-meta-data-to-input-framedata.patch \
		file://gst1.20.3_20200812.1-tcc-gstreamer1.0-plugins-good-mpegaudioparse-Modify-search-next-framedata-qtdemux-add-flac-fourcc.patch \
		file://20210818.1-tcc-gstreamer1.0-plugins-good-amrparse-add-code-for-search-valid-data.patch \
		file://20221108.1-tcc-gstreamer1.0-plugins-good-mod-avidemux-qtdemux-wavparse.patch \
		file://gst1.20.3_20221109.1-tcc-gstreamer1.0-plugins-good-v4l2sink-support-telechips-format.patch \
		file://20221111.1-tcc-gstreamer1.0-plugins-good-v4l2sink-modify_v4l2_reserved.patch \
		file://gst1.20.5_20230613.1-tcc-gstreamer1.0-plugins-good-fix-skipping-the-file-when-seek-in-avi.patch \
"
# for tc-dma-buf
SRC_URI:append = " \
    ${@oe.utils.conditional('VIDEO_SINK', 'waylandsink', 'file://20201005.1-tcc-gstreamer1.0-plugins-good-v4l2sink-temp-n-plane-set-1.patch', '', d)} \
"

DEPENDS += "linux-telechips"

ADD_INCLUDE_PATH = " \
	-I${STAGING_KERNEL_DIR}/include/video/tcc \
	-I${STAGING_KERNEL_DIR}/include/video/telechips \
	-I${STAGING_KERNEL_BUILDDIR}/include \
"

EXTRA_OECONF += "PROCESSOR=${TCC_ARCH_FAMILY}"

CFLAGS:append = " ${ADD_INCLUDE_PATH}"
CFLAGS:append = " -DTCC_V4L2SINK_DRIVER_USE"

PACKAGECONFIG[v4l2] = "-Dv4l2=enabled -Dv4l2-probe=false,-Dv4l2=disabled -Dv4l2-probe=false"
