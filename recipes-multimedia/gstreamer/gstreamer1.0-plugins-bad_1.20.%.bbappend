FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
	file://20200911.1-tcc-gstreamer1.0-plugins-bad-adpcmdec-don-t-check-blockalign.patch \
	file://20221107.1-tcc-gstreamer1.0-plugins-bad-mod-h264parse-h265parse.patch \
"

SRC_URI:append = " \
	file://0101-feat-waylandsink-support-scale-feature.patch \
	file://0102-feat-waylandsink-support-yuv-color-space-and-range.patch \
	${@bb.utils.contains('INVITE_PLATFORM', 'ivi-extension', 'file://0201-feat-waylandsink-support-ivi-shell-interface.patch', '', d)} \
"

PACKAGECONFIG = " \
    ${GSTREAMER_ORC} \
    ${@bb.utils.filter('DISTRO_FEATURES', 'vulkan', d)} \
    ${@bb.utils.filter('DISTRO_FEATURES', 'wayland', d)} \
    bz2 closedcaption curl dash dtls hls rsvg sbc smoothstreaming sndfile \
    ttml uvch264 webp \
"

DEPENDS += "${@bb.utils.contains('INVITE_PLATFORM', 'ivi-extension', 'wayland-ivi-extension', '', d)}"

CONFLICT_INVITE_PLATFORM = "${@oe.utils.conditional('VIDEO_SINK', 'waylandsink', 'support-4k-video', '', d)}"
