DESCRIPTION = "Script to enable removable disk after application ready."
LICENSE = "Telechips"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta-telechips-bsp/licenses/Telechips;md5=e23a23ed6facb2366525db53060c05a4"
SECTION = "bsp"

SRC_URI = "file://enable-removable-disk.sh \
		   ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'file://enable-removable-disk.service', '', d)} \
"

inherit update-rc.d systemd

# for systemd
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE:${PN} = "${BPN}.service"

# for sysvinit
INIT_NAME = "${BPN}"
INITSCRIPT_NAME = "${INIT_NAME}"
INITSCRIPT_PARAMS = "start 99 5 ."

do_install() {
	if ${@bb.utils.contains('DISTRO_FEATURES', 'sysvinit', 'true', 'false', d)}; then
		install -d ${D}${sysconfdir}/init.d/
		install -m 0755 ${WORKDIR}/enable-removable-disk.sh	${D}${sysconfdir}/init.d/${INIT_NAME}
	else
		install -d ${D}${bindir}
		install -d ${D}${systemd_unitdir}/system

		install -m 0755 ${WORKDIR}/enable-removable-disk.sh ${D}${bindir}
		install -m 0644 ${WORKDIR}/enable-removable-disk.service ${D}${systemd_unitdir}/system/${BPN}.service
	fi
}
