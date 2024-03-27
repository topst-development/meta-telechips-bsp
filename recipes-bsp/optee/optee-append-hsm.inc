
SRC_URI:append:tcc803x = " \
	file://thsm.service \
"

SYSTEMD_SERVICE:${PN}:append:tcc803x = " \
	thsm.service \
"

do_install:append() {
	if ${@bb.utils.contains_any("TCC_ARCH_FAMILY", "tcc897x tcc802x tcc803x", "true", "false", d)}; then
		install -m 0755 ${S}/bin/hsmTEEtest		${D}${bindir}/
		install ${S}/lib/libcaHSM.so*		${D}${libdir}/
		install -m 0644 ${B}/TAs/9aec3623-b887-4491-a453-3de7735a3e85.ta	${D}${libdir}/optee_armtz/
	fi
}

do_install:append:tcc803x() {
	install -d ${D}${systemd_unitdir}/system
	install -m 0755 ${S}/bin/thsmDaemon		${D}${bindir}/
	install -m 0644 ${WORKDIR}/thsm.service		${D}${systemd_unitdir}/system/thsm.service
}

FILES:${PN}:append:tcc803x = " \
	${systemd_unitdir} \
	"