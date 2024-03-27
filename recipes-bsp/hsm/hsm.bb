# Check the Telechips license
LICENSE = "Telechips"
SECTION = "hsm"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta-telechips-bsp/licenses/Telechips;md5=e23a23ed6facb2366525db53060c05a4"


# Download hsm_test code through git url
SRC_URI = "${TELECHIPS_AUTOMOTIVE_GIT}/hsm.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"

SRCREV = "d3ce060e17f1f5e8b038b7803f07abe403ebfc41"
do_compile[noexec] = "1"

INSANE_SKIP:${PN}-dev = "ldflags already-stripped dev-elf dev-deps"
INSANE_SKIP:${PN} = "ldflags dev-so dev-deps already-stripped"

S = "${WORKDIR}/git"
B = "${WORKDIR}"

HSM_BIT:arm = "32"
HSM_BIT:aarch64 = "64"

HSM_CHIP = "${@bb.utils.contains_any('TCC_ARCH_FAMILY', 'tcc803x tcc803xp', 'M4', 'SC000', d)}"

do_install() {
	install -d ${D}${bindir}
	if ${@bb.utils.contains_any('TCC_ARCH_FAMILY', "tcc803x tcc803xp tcc805x tcc807x", 'true', 'false', d)}; then
		make -C ${S}/hsm_test/${HSM_CHIP} TARGET_BIT=${HSM_BIT} CHIP=${HSM_CHIP} YOCTO_BUILD=y
		install -m 0755 ${S}/hsm_test/${HSM_CHIP}/out/hsm_test_${HSM_BIT}_${HSM_CHIP} ${D}${bindir}/
	fi
}
