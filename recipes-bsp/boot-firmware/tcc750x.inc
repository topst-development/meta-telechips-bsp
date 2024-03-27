SRC_URI:append = ""

#SRCREV = "476fce18ae19fe9df8836b2f83114dc3bd5aa4d2"
ALS_BRANCH = "tcc750x"
do_install() {
    install -d ${D}/boot-firmware
    install -d ${D}/boot-firmware/prebuilt
	
    install -m 0644 ${S}/prebuilt/bconf.bin             ${D}/boot-firmware/prebuilt
    install -m 0644 ${S}/prebuilt/mcert.bin             ${D}/boot-firmware/prebuilt
    install -m 0644 ${S}/prebuilt/dram_params.bin       ${D}/boot-firmware/prebuilt
    install -m 0644 ${S}/prebuilt/hsm.bin               ${D}/boot-firmware/prebuilt
    install -m 0644 ${S}/prebuilt/fwdn.rom              ${D}/boot-firmware/prebuilt
    install -m 0644 ${S}/prebuilt/optee.rom             ${D}/boot-firmware/prebuilt

    install -m 0644 ${S}/prebuilt/ca53_bl1.rom          ${D}/boot-firmware/prebuilt
    install -m 0644 ${S}/prebuilt/ca53_bl2.rom          ${D}/boot-firmware/prebuilt

    install -m 0644 ${S}/tcc750x_fwdn.json              ${D}/boot-firmware
    install -m 0644 ${S}/tcc750x_boot.json              ${D}/boot-firmware
}
