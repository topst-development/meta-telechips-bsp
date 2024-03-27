SUMMARY = "Universal Boot Loader for embedded devices"
HOMEPAGE = "http://www.denx.de/wiki/U-Boot/WebHome"
SECTION = "bootloaders"
PROVIDES = "virtual/bootloader"

LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://Licenses/README;md5=5a7450c57ffe5ae63fd732446b988025"

SRC_URI = "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/u-boot.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"

SRC_URI += "${@bb.utils.contains('IMAGE_FEATURES', 'uboot-fit', 'file://fit.cfg', '', d)}"

#ALS_BRANCH ??= "lts"
SRCREV = "69d7a57cf973faa5125a867f75a87fccc605963a"

S = "${WORKDIR}/git"
B = "${S}"

require recipes-bsp/u-boot/u-boot.inc u-boot-tcc.inc

DEPENDS += "bison-native"

EXTRA_OEMAKE = 'CROSS_COMPILE=${TARGET_PREFIX} CC="${TARGET_PREFIX}gcc ${TOOLCHAIN_OPTIONS}" V=1'
EXTRA_OEMAKE += 'HOSTCC="${BUILD_CC} ${BUILD_CFLAGS} ${BUILD_LDFLAGS}"'
EXTRA_OEMAKE += 'STAGING_INCDIR=${STAGING_INCDIR_NATIVE} STAGING_LIBDIR=${STAGING_LIBDIR_NATIVE}'

UBOOT_ARCH_ARGS:arm = "ARCH=arm"
UBOOT_ARCH_ARGS:aarch64 = "ARCH=arm64 "

UBOOT_IMAGE = "${UBOOT_NAME}-${MACHINE}-${PV}-${PR}.${UBOOT_SUFFIX}"
UBOOT_BINARY = "${UBOOT_NAME}.${UBOOT_SUFFIX}"
UBOOT_SYMLINK = "${UBOOT_NAME}-${MACHINE}.${UBOOT_SUFFIX}"

PATCHTOOL = "git"

do_configure() {
	if [ "${@bb.utils.contains('DISTRO_FEATURES', 'ld-is-gold', 'ld-is-gold', '', d)}" = "ld-is-gold" ] ; then
		sed -i 's/$(CROSS_COMPILE)ld$/$(CROSS_COMPILE)ld.bfd/g' ${S}/config.mk
	fi

	if [ -n "${EXTERNALSRC}" ] ; then
		export KBUILD_OUTPUT=${EXTERNALSRC}/${MACHINE}/
	fi
	export ${UBOOT_ARCH_ARGS} DEVICE_TREE=${UBOOT_DEVICE_TREE}
	oe_runmake ${UBOOT_MACHINE}
	if [ -n "${EXTERNALSRC}" ] ; then
		${S}/scripts/kconfig/merge_config.sh -O ${KBUILD_OUTPUT} -m ${KBUILD_OUTPUT}.config ${@" ".join(find_cfgs(d))}
	else
		${S}/scripts/kconfig/merge_config.sh -m .config ${@" ".join(find_cfgs(d))}
	fi
	cml1_do_configure
}

do_compile() {
	unset LDFLAGS
	unset CFLAGS
	unset CPPFLAGS
	if [ -n "${EXTERNALSRC}" ] ; then
		export KBUILD_OUTPUT=${EXTERNALSRC}/${MACHINE}/
	fi
	export ${UBOOT_ARCH_ARGS} DEVICE_TREE=${UBOOT_DEVICE_TREE}

	oe_runmake
}

do_install() {
	install -d ${D}/boot

	if [ -n "${EXTERNALSRC}" ] ; then
		export KBUILD_OUTPUT=${EXTERNALSRC}/${MACHINE}/
		install -m 0644 ${KBUILD_OUTPUT}${UBOOT_NAME}.${UBOOT_SUFFIX}	${D}/boot/${UBOOT_IMAGE}
	else
		install -m 0644 ${S}/${UBOOT_NAME}.${UBOOT_SUFFIX}	${D}/boot/${UBOOT_IMAGE}
	fi
}

FILES:${PN} = "/boot"

do_deploy() {
    install -d ${DEPLOYDIR}

    if [ "${UBOOT_SIGN_ENABLE}" != "1" ]; then
        install -m 0644 ${D}/boot/${UBOOT_IMAGE} ${DEPLOYDIR}
    fi

	cd ${DEPLOYDIR}
    rm -f ${UBOOT_BINARY} ${UBOOT_SYMLINK}
    ln -sf ${UBOOT_IMAGE} ${UBOOT_BINARY}
    ln -sf ${UBOOT_IMAGE} ${UBOOT_SYMLINK}
	cd -
}

do_clean_extworkdir() {
	if [ -n "${EXTERNALSRC}" ]; then
		rm -rf ${EXTERNALSRC}/arch/*/include/asm/telechips
		rm -rf ${EXTERNALSRC}/${MACHINE}
	fi
}

addtask deploy before do_build after do_install
addtask clean_extworkdir after do_buildclean before do_clean
