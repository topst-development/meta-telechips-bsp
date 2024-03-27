DESCRIPTION = "Telechips VPU Drivers"

SECTION = "kernel/modules"
LICENSE = "Telechips"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta-telechips-bsp/licenses/Telechips;md5=e23a23ed6facb2366525db53060c05a4"

inherit module cmake

SRC_URI = "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/vpu/vpu-kernel-library.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
SRCREV = "40034ec7150779353725a53108b75ee1fc6a7752"


PATCHTOOL = "git"
LINKER_HASH_STYLE = "sysv"

S="${WORKDIR}/git"

PACKAGES += "kernel-modules-vpu"

python __anonymous() {
    chip = d.getVar('TCC_ARCH_FAMILY')

    d.setVar('VPU_LIB_NAME', 'vpu_lib')
    d.setVar('JPU_LIB_NAME', 'jpu_lib')
    d.setVar('CONFIG_NAME', '00.vpu-lib.conf')

    if chip in ['tcc803x', 'tcc897x']:
        d.setVar('VPU_HIGH_RES_LIB_NAME', 'hevc_lib')
        d.setVar('VPU_HIGH_RES_TYPE', 'hevc')
    if chip in ['tcc805x', 'tcc807x']:
        d.setVar('VPU_HIGH_RES_LIB_NAME', 'vpu_4k_d2_lib')
        d.setVar('VPU_HIGH_RES_TYPE', 'vpu_4k_d2')
    if chip in ['tcc750x', 'tcc805x', 'tcc807x']:
        d.setVar('VPU_HEVC_ENC_LIB_NAME', 'vpu_hevc_enc_lib')
}

VPU_INSTALL_DIR = "${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/char/vpu/lib"

do_configure:prepend() {
	export KERNEL_BUILD_DIR=${STAGING_KERNEL_BUILDDIR}
	export CHIPSET=${TCC_ARCH_FAMILY}
}

do_configure:prepend() {
	export KERNEL_BUILD_DIR=${STAGING_KERNEL_BUILDDIR}
	export CHIPSET=${TCC_ARCH_FAMILY}
}

do_install() {
    install -d ${VPU_INSTALL_DIR}
    install -d ${D}${sysconfdir}/modules-load.d

    if ${@bb.utils.contains('TCC_ARCH_FAMILY', 'tcc750x', 'false', 'true', d)}; then
        install -m 0644 ${WORKDIR}/build/vpu_*/${VPU_LIB_NAME}.ko									${VPU_INSTALL_DIR}/${VPU_LIB_NAME}.ko
	    install -m 0644 ${WORKDIR}/build/jpu_*/${JPU_LIB_NAME}.ko									${VPU_INSTALL_DIR}/${JPU_LIB_NAME}.ko
        install -m 0644 ${WORKDIR}/build/${VPU_HIGH_RES_TYPE}*/${VPU_HIGH_RES_LIB_NAME}.ko			${VPU_INSTALL_DIR}/${VPU_HIGH_RES_LIB_NAME}.ko

        echo "${VPU_LIB_NAME}"    			>> ${D}${sysconfdir}/modules-load.d/${CONFIG_NAME}
        echo "${VPU_HIGH_RES_LIB_NAME}"		>> ${D}${sysconfdir}/modules-load.d/${CONFIG_NAME}
        echo "${JPU_LIB_NAME}"				>> ${D}${sysconfdir}/modules-load.d/${CONFIG_NAME}
    fi

	if [ -n "${VPU_HEVC_ENC_LIB_NAME}" ]; then
		install -m 0644 ${WORKDIR}/build/vpu_hevc_enc/${VPU_HEVC_ENC_LIB_NAME}.ko	${VPU_INSTALL_DIR}/${VPU_HEVC_ENC_LIB_NAME}.ko
		echo "${VPU_HEVC_ENC_LIB_NAME}"    >> ${D}${sysconfdir}/modules-load.d/${CONFIG_NAME}
	fi
}

FILES:${PN} += "${sysconfdir}/modules-load.d/${CONFIG_NAME}"
RPROVIDES:${PN} += "kernel-modules-vpu"

OECMAKE_GENERATOR = "Unix Makefiles"
