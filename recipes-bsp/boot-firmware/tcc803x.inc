SRC_URI:append = " file://micom_${CHIPSET}.cfg"

SRCREV = "99e64191da58ff4d67d8734f812e55ca784b077f"
CHIPSET = "${@bb.utils.contains_any('MACHINE', 'tcc8030-main tcc8030-cluster', 'tcc803x', 'tcc803xpe', d)}"

do_install() {
	install -d ${D}/boot-firmware
	install -d ${D}/boot-firmware/prebuilt

	install -m 0644 ${S}/prebuilt/ap.rom					 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/bconf.bin					 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/bl2-2.rom					 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/dram_params.bin			 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/fwdn.rom					 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/hsm.bin					 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/keypackages.bin			 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/micom-bl1.rom				 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/optee.rom					 	${D}/boot-firmware/prebuilt
	install -m 0644 ${S}/prebuilt/r5_sub_fw.bin				 	${D}/boot-firmware/prebuilt

	install -m 0644 ${S}/tcc803x_fwdn.json						${D}/boot-firmware/fwdn.json
	install -m 0644 ${S}/tcc803x_boot.json						${D}/boot-firmware/boot.json

	sed -i 's%SOURCE_DIR%${S}%g' ${WORKDIR}/micom_${CHIPSET}.cfg
	${S}/tools/d3s_snor_mkimage/tcc803x-snor-mkimage-tools -c ${WORKDIR}/micom_${CHIPSET}.cfg -o ${D}/boot-firmware/prebuilt/${CHIPSET}_snor_boot.rom
}
