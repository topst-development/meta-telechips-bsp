FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
		file://20200312.1-tcc-gstreamer1.0-Add-error-value-of-DIVX-specout.patch \
		file://gst1.20.3_20220902.1-tcc-gstreamer1.0-can-skip-dummy-data-in-any-parser.patch \
		file://20210316.1-tcc-gstreamer1.0-buffer-ignore-warning-message-for-over-buffermaxsize.patch \
		file://20221108.1-tcc-gstreamer1.0-gstinfo-disable-warning-log.patch \
"

