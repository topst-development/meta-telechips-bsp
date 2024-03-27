require linux-telechips.inc

SRC_URI = "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/kernel-5.4.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
SRCREV = "4d7d57747b19d16d306bfee06d2204f4ea356820"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"

LINUX_VERSION = "5.4.254"
COMPATIBLE_MACHINE = "(tcc750x|tcc897x)"
KERNEL_EXTRA_ARGS:arm:append = " ARCH=arm"
KERNEL_EXTRA_ARGS:aarch64:append = " ARCH=arm64"

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
