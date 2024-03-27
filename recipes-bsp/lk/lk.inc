DSCRIPTION = "Telechips lk boot"
SECTION = "bootloader"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit deploy

LK_NAME ?= "lk"
LK_SUFFIX ?= "rom"
LK_IMAGE ?= "${LK_NAME}-${MACHINE}-${PV}-${PR}.${LK_SUFFIX}"
LK_BINARY ?= "${LK_NAME}.${LK_SUFFIX}"
LK_SYMLINK ?= "${LK_NAME}-${MACHINE}.${LK_SUFFIX}"
LK_BUILD_DIR ?= "${B}"

S = "${WORKDIR}/git"

TOOLCHAIN_OPTIONS = " --sysroot=${RECIPE_SYSROOT}"
PATCHTOOL = "git"

LK_HWFP="${@bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'USE_HWFP=1', '', d)}"
do_preconfigure[noexec] = "1"

do_configure() {
}

do_compile() {
	export TOOLCHAIN_PREFIX=${TARGET_PREFIX}
	export SDKTARGETSYSROOT=${RECIPE_SYSROOT}
	oe_runmake ${LK_PROJECT_NAME} ${LK_MAKE_PARAM} ${LK_HW_REV} ${LK_HWFP}
}

do_install() {
    install -d ${D}/boot
	install -m 0644 ${S}/build-${LK_PROJECT_NAME}/${LK_NAME}.${LK_SUFFIX} ${D}/boot/${LK_IMAGE}
}

FILES:${PN} = "/boot"

do_deploy () {
    install -d ${DEPLOYDIR}
    install -m 0644 ${D}/boot/${LK_IMAGE} ${DEPLOYDIR}

	cd ${DEPLOYDIR}
    rm -f ${LK_BINARY} ${LK_SYMLINK}
    ln -sf ${LK_IMAGE} ${LK_BINARY}
    ln -sf ${LK_IMAGE} ${LK_SYMLINK}
	cd -
}

addtask deploy before do_build after do_install

