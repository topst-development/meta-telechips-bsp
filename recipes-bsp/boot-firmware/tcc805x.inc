SRC_URI:append = " file://micom.cfg"

SRCREV = "72473f08fed5befa2845316cce8b38ff96e22ced"

TCC8050_MACHINE_LIST = "tcc8050-main tcc8053-main tcc8050-cluster tcc8053-cluster tcc8050-dvrs tcc8053-dvrs"
CHIP_NAME = "${@bb.utils.contains_any('MACHINE', '${TCC8050_MACHINE_LIST}', 'tcc8050', 'tcc8059', d)}"
R5_FW_NAME = "${@bb.utils.contains_any('MACHINE', '${TCC8050_MACHINE_LIST}', 'r5_fw_TCC8050', 'r5_fw_TCC8059', d)}"

do_install() {
	install -d ${D}/boot-firmware
	install -d ${D}/boot-firmware/prebuilt
	install -d ${D}/boot-firmware/prebuilt/ufs

	if ${@bb.utils.contains_any('TCC_BSP_FEATURES', 'with-subcore', 'false', 'true', d)}; then
		sed -i 's%\(bootsel="\)dual%\1single%g'							${S}/tools/bconf_maker/tcc805x_bconf.xml
	fi

	python3 ${S}/tools/bconf_maker/bconf_maker_v01.py -i ${S}/tools/bconf_maker/tcc805x_bconf.xml -o ${D}/boot-firmware/prebuilt/bconf.bin

	install -m 0644 ${S}/prebuilt/bconf.bin 				${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/mcert.bin 				${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/dram_params.bin 			${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/hsm.bin	 				${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/hsm.cs.bin 				${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/fwdn.rom 					${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/optee.rom 				${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/scfw.rom                  ${D}/boot-firmware/prebuilt

	if ${@oe.utils.conditional('BOOT_STORAGE', 'ufs', 'true', 'false', d)}; then
		install -m 0644 ${S}/prebuilt/ufs/ca72_bl1.rom 		${D}/boot-firmware/prebuilt/ufs
		install -m 0644 ${S}/prebuilt/ufs/ca72_bl2.rom 		${D}/boot-firmware/prebuilt/ufs
		install -m 0644 ${S}/prebuilt/ufs/ca53_bl1.rom 		${D}/boot-firmware/prebuilt/ufs
		install -m 0644 ${S}/prebuilt/ufs/ca53_bl2.rom 		${D}/boot-firmware/prebuilt/ufs
		install -m 0644 ${S}/tcc805x_ufs_boot.json			${D}/boot-firmware/boot.json
	else
		install -m 0644 ${S}/prebuilt/ca72_bl1.rom 			${D}/boot-firmware/prebuilt
		install -m 0644 ${S}/prebuilt/ca72_bl2.rom 			${D}/boot-firmware/prebuilt
		install -m 0644 ${S}/prebuilt/ca53_bl1.rom 			${D}/boot-firmware/prebuilt
		install -m 0644 ${S}/prebuilt/ca53_bl2.rom 			${D}/boot-firmware/prebuilt
		install -m 0644 ${S}/tcc805x_boot.cs.json		 	${D}/boot-firmware/boot.json
	fi

	install -m 0644 ${S}/tcc805x_fwdn.cs.json				${D}/boot-firmware/fwdn.json

	sed -i 's%SOURCE_DIR%${S}%g' ${WORKDIR}/micom.cfg
	${S}/tools/tcc805x_snor_mkimage/tcc805x-snor-mkimage -i ${WORKDIR}/micom.cfg -o ${D}/boot-firmware/prebuilt/${CHIP_NAME}_snor.cs.rom
}
