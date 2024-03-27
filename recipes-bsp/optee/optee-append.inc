# optee append common includes

INSANE_SKIP:${PN}-dev = "ldflags already-stripped dev-elf dev-deps"
INSANE_SKIP:${PN} = "ldflags dev-so dev-deps already-stripped"

DEPENDS = "optee-client"

TEE_TARGET_POSTFIX = "${@bb.utils.contains('TARGET_FPU', 'hard', 'hf', '', d)}"
TEE_TARGET = "${GCCVERSION}/${@bb.utils.contains('TUNE_FEATURES', 'aarch64', \
		'aarch64', 'arm${TEE_TARGET_POSTFIX}', d)}"

TEEC_VERSION = "${@oe.utils.trim_version('${PV}', 1)}"

S = "${WORKDIR}/git/${TEE_TARGET}"
B = "${WORKDIR}/git"

do_install() {
	install -d ${D}${bindir}
	install -d ${D}${libdir}
	install -d ${D}${libdir}/optee_armtz
}

FILES:${PN} += " \
	${libdir} \
	${bindir} \
	"

PACKAGES = "${PN}"
