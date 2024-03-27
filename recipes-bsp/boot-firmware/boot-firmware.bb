DESCRIPTION = "Telechips prebuilt boot firmwares"
LICENSE = "Telechips"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta-telechips/meta-core/licenses/Telechips;md5=e23a23ed6facb2366525db53060c05a4"
SECTION = "bsp"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}/${CHIP_PATH}:"

require ${TCC_ARCH_FAMILY}.inc

inherit deploy

CHIP_PATH = "${@d.getVar("MACHINE").split("-")[0]}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/boot-firmware.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
# ALS_BRANCH ??= "${TCC_ARCH_FAMILY}"

S = "${WORKDIR}/git"
PATCHTOOL = "git"

do_deploy() {
	install -d ${DEPLOYDIR}
	cp -ap ${D}/boot-firmware ${DEPLOYDIR}
}
addtask deploy after do_install

do_configure[noexec] = "1"
do_compile[noexec] = "1"

FILES:${PN} = "boot-firmware"
