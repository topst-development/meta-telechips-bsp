require linux-telechips.inc

SRC_URI = "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/kernel-5.10.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
SRCREV = "${AUTOREV}"

SRC_URI:append = "${@bb.utils.contains('IMAGE_FEATURES', 'uboot-fit', 'file://cmdline.cfg', '', d)}"

ALS_BRANCH ??= "lts"
#SRCREV = "8db05de9ca986b4d0fa6bedb015f94019ad2799e"

LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

LINUX_VERSION = "5.10.177"
COMPATIBLE_MACHINE = "(tcc803x|tcc805x|tcc807x|tcc750x)"
KERNEL_EXTRA_ARGS:append:arm = " ARCH=arm"
KERNEL_EXTRA_ARGS:append:aarch64 = " ARCH=arm64"

KERNEL_OFFSET:arm = "0x8000"
KERNEL_OFFSET:aarch64 = "0x80000"

kernel_do_install:append() {
	if [ -e "${D}${KERNEL_SRC_PATH}/tools/gator/daemon/escape" ]; then
		rm ${D}${KERNEL_SRC_PATH}/tools/gator/daemon/escape
	fi

	rm -rf ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/char/vpu/vpu_hevc_enc_lib*
	rm -rf ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/char/vpu/vpu_lib*
	rm -rf ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/char/vpu/hevc_lib*
	rm -rf ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/char/vpu/vpu_4k_d2_lib*
	rm -rf ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/char/vpu/jpu_lib*
}
