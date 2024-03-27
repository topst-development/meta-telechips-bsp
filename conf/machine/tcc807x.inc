#@TYPE: Machine
#@NAME: Telechips TCC807x Family
#@DESCRIPTION: Machine configuration for the Telechips EVM Board

require conf/machine/include/arm/armv8-2a/tune-cortexa76-cortexa55.inc
require conf/machine/tcc-family.inc

GST_ARCH_FAMILY_NAME = "TCC_807x"
LCD_TYPE ??= "TIANMA"
LCD_WIDTH ??= "1920"
LCD_HEIGHT ??= "720"

BOOT_STORAGE ??= "emmc"
SERIAL_CONSOLES = "115200;ttyAMA0"
KERNEL_CONSOLE = "ttyAMA0"

EXTRA_IMAGEDEPENDS += "u-boot-tcc"

UBOOT_NAME ??= "ap0_bl3"
UBOOT_SUFFIX = "rom"
UBOOT_MACHINE ??= "tcc807x_defconfig"
UBOOT_MAKE_TARGET = "tcc807x"

KBUILD_DEFCONFIG ??= "tcc807x_defconfig"
KERNEL_BASE_ADDR = "0x20000000"

UPDATE_BOOTLOADER_NAME = "${UBOOT_NAME}.${UBOOT_SUFFIX}"
UPDATE_KERNEL_NAME = "tc-boot-${MACHINE}.img"
UPDATE_ROOTFS_NAME = "${IMAGE_LINK_NAME}.${DEFAULT_IMAGE_FSTYPE}"
UPDATE_DTB_NAME = "${@d.getVar("KERNEL_DEVICETREE").split("/")[-1]}"

# GPU configuration
PREFERRED_PROVIDER_virtual/egl			= "telechips-egl"
PREFERRED_PROVIDER_virtual/libgles1		= "telechips-egl"
PREFERRED_PROVIDER_virtual/libgles2		= "telechips-egl"
PREFERRED_PROVIDER_virtual/mesa			= "telechips-egl"
PREFERRED_PROVIDER_libglapi				= "telechips-egl"
PREFERRED_PROVIDER_libgbm				= "telechips-egl"
PREFERRED_PROVIDER_libwayland-egl		= "telechips-egl"

# Telechips EVB UFS Size
TCC_UFS_STORAGE_SIZE ?= "63988301824"
# Telechips EVB eMMc Size
TCC_EMMC_STORAGE_SIZE ?= "31268536320"
