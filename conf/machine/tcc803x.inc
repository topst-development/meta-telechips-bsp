#@TYPE: Machine
#@NAME: Telechips TCC803x Family
#@DESCRIPTION: Machine configuration for the Telechips EVB

# don't reverse the order of 'DEFAULTTUNE' and 'require conf/machine/include/tune-cortexa53.inc'
DEFAULTTUNE ?= "${@bb.utils.contains('ARCHITECTURE', 'arm', 'cortexa53-arm', 'cortexa53', d)}"
require conf/machine/include/arm/armv8a/tune-cortexa53.inc
require conf/machine/include/tune-cortexa53-arm.inc
require conf/machine/tcc-family.inc

GST_ARCH_FAMILY_NAME = "TCC_803x"
LCD_TYPE ??= "TIANMA"
LCD_WIDTH ??= "1920"
LCD_HEIGHT ??= "720"

SERIAL_CONSOLES = "115200;ttyAMA0"
KERNEL_CONSOLE = "ttyAMA0"

CONFLICT_MACHINE_FEATURES = "ufs"

EXTRA_IMAGEDEPENDS += "u-boot-tcc"

UBOOT_NAME ??= "u-boot"
UBOOT_SUFFIX = "rom"
UBOOT_MACHINE ??= "tcc803x_defconfig"
UBOOT_MAKE_TARGET = "tcc803x"

KBUILD_DEFCONFIG ??= "tcc803x_defconfig"
KERNEL_BASE_ADDR = "0x20000000"

UPDATE_BOOTLOADER_NAME = "${UBOOT_NAME}.${UBOOT_SUFFIX}"
UPDATE_KERNEL_NAME = "tc-boot.img"
UPDATE_ROOTFS_NAME = "${IMAGE_LINK_NAME}.${DEFAULT_IMAGE_FSTYPE}"
UPDATE_SNOR_NAME = "tcc803x_snor_boot.rom"
UPDATE_DTB_NAME = "${@d.getVar("KERNEL_DEVICETREE").split("/")[-1]}"

# GPU configuration
PREFERRED_PROVIDER_virtual/egl			= "telechips-egl"
PREFERRED_PROVIDER_virtual/libgles1		= "telechips-egl"
PREFERRED_PROVIDER_virtual/libgles2		= "telechips-egl"
PREFERRED_PROVIDER_virtual/mesa			= "telechips-egl"
PREFERRED_PROVIDER_libglapi			= "telechips-egl"
PREFERRED_PROVIDER_libgbm			= "telechips-egl"
PREFERRED_PROVIDER_libwayland-egl		= "telechips-egl"

# Telechips EVB UFS Size
TCC_UFS_STORAGE_SIZE ?= "31998345216"
# Telechips EVB eMMc Size
TCC_EMMC_STORAGE_SIZE ?= "7818182656"
