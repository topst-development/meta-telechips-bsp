require recipes-bsp/lk/lk.inc

SRC_URI += "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/lk-dt.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
SRCREV = "eb013c6714b4568e6955a2a85e37fd5e8edacb08"

do_configure:append() {
	if ${@bb.utils.contains('INVITE_PLATFORM', 'sw-audio-dsp', 'true', 'false', d)}; then
		sed -i 's/#\(TCC_AUDIO_DSP_USE := 1\)/\1/g'  ${S}/target/${LK_TARGET_NAME}/rules.mk
	fi
}
