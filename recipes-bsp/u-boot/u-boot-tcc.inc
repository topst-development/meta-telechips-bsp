python __anonymous() {
    bsp_features = d.getVar('TCC_BSP_FEATURES', True)
    boot_storage = d.getVar('BOOT_STORAGE', True)
    tcc_arch_family = d.getVar('TCC_ARCH_FAMILY', True)
    src_uri = d.getVar('SRC_URI').split()

    if boot_storage == 'ufs':
        src_uri.append('file://boot-ufs.cfg')
    elif boot_storage == 'emmc':
        src_uri.append('file://boot-emmc.cfg')

    if 'display' in bsp_features:
        src_uri.append('file://display.cfg')

    if 'gpu-vz' in bsp_features:
        src_uri.append('file://gpu-vz.cfg')

    if 'with-subcore' in bsp_features and tcc_arch_family == 'tcc803x':
        src_uri.append('file://boot.cfg')

    d.setVar('SRC_URI', ' '.join(src_uri))
}
