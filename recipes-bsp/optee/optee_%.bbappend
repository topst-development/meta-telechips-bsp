# optee_%.bbappend
#

inherit systemd deploy

require optee-append.inc
require optee-append-hsm.inc

TEEOS_IMAGE = "optee.rom"

do_install:append() {
	# optee unit test
	if ${@bb.utils.contains('TCC_BSP_FEATURES', 'optee-xtest', 'true', 'false', d)}; then
		install -m 0755 ${B}/xtest/${TEE_TARGET}/xtest	${D}${bindir}/
		cp -rf  ${B}/xtest/TAs/*.ta			${D}${libdir}/optee_armtz/
	fi
}

do_deploy() {
	if ${@bb.utils.contains_any("TCC_ARCH_FAMILY", "tcc897x", "false", "true", d)}; then
		install -d ${DEPLOYDIR}
		install -m 0644 ${B}/OS/${TEEOS_IMAGE} ${DEPLOYDIR}
	fi
}

addtask deploy before do_build after do_install
