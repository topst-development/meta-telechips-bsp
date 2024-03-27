#@TYPE: Machine
#@NAME: Telechips TCC805x Family
#@DESCRIPTION: Machine configuration for the Telechips EVM Board

require conf/machine/include/arm/armv8a/tune-cortexa72.inc
require conf/machine/tcc-family.inc

GST_ARCH_FAMILY_NAME = "TCC_805x"
LCD_TYPE ??= "TIANMA"
LCD_WIDTH ??= "1920"
LCD_HEIGHT ??= "720"

BOOT_STORAGE ??= "emmc"
SERIAL_CONSOLES = "115200;ttyAMA0"
KERNEL_CONSOLE = "ttyAMA0"

EXTRA_IMAGEDEPENDS += "u-boot-tcc"

UBOOT_NAME ??= "ca72_bl3"
UBOOT_SUFFIX = "rom"
UBOOT_MACHINE ??= "tcc805x_defconfig"
UBOOT_MAKE_TARGET = "tcc805x"

KBUILD_DEFCONFIG ??= "tcc805x_defconfig"
KERNEL_BASE_ADDR = "0x20000000"

UPDATE_BOOTLOADER_NAME = "${UBOOT_NAME}.${UBOOT_SUFFIX}"
UPDATE_KERNEL_NAME = "tc-boot-${MACHINE}.img"
UPDATE_ROOTFS_NAME = "${IMAGE_LINK_NAME}.${DEFAULT_IMAGE_FSTYPE}"
UPDATE_SNOR_NAME = "tcc8050_snor.cs.rom"
UPDATE_DTB_NAME = "${@d.getVar("KERNEL_DEVICETREE").split("/")[-1]}"

# GPU configuration
PREFERRED_PROVIDER_virtual/egl			= "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'mesa', 'powervr', d)}"
PREFERRED_PROVIDER_virtual/libgles1		= "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'mesa', 'powervr', d)}"
PREFERRED_PROVIDER_virtual/libgles2		= "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'mesa', 'powervr', d)}"
PREFERRED_PROVIDER_virtual/mesa			= "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'mesa', 'powervr', d)}"
PREFERRED_PROVIDER_libglapi				= "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'mesa', '', d)}"
PREFERRED_PROVIDER_libgbm				= "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'mesa', '', d)}"
PREFERRED_PROVIDER_libwayland-egl		= "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'mesa', '', d)}"
PREFERRED_PROVIDER_vulkan-loader		= "powervr"

GPU_DRIVER_MODE ??= "${@bb.utils.contains_any("TCC_BSP_FEATURES", 'gpu-vz', 'guest', 'native', d)}"

# Telechips EVB UFS Size
TCC_UFS_STORAGE_SIZE ?= "31998345216"
# Telechips EVB eMMc Size
TCC_EMMC_STORAGE_SIZE ?= "7818182656"
