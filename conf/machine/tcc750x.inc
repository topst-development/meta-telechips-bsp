#@TYPE: Machine
#@NAME: Telechips TCC750x Family
#@DESCRIPTION: Machine configuration for the Telechips EVB

# don't reverse the order of 'DEFAULTTUNE' and 'require conf/machine/include/tune-cortexa53.inc'
DEFAULTTUNE ?= "${@bb.utils.contains('ARCHITECTURE', 'arm', 'cortexa53-arm', 'cortexa53', d)}"
require conf/machine/include/arm/armv8a/tune-cortexa53.inc
require conf/machine/include/tune-cortexa53-arm.inc
require conf/machine/tcc-family.inc

BOOT_STORAGE ??= "emmc"
SERIAL_CONSOLES = "115200;ttyAMA2"
KERNEL_CONSOLE = "ttyAMA2"

CONFLICT_MACHINE_FEATURES = "ufs"

EXTRA_IMAGEDEPENDS += "u-boot-tcc"

UBOOT_NAME ?= "u-boot"
UBOOT_SUFFIX = "rom"
UBOOT_MACHINE ??= "tcc750x_defconfig"
UBOOT_MAKE_TARGET = "tcc750x"
UBOOT_IMAGE = "${UBOOT_NAME}-${MACHINE}-${PV}-${PR}.${UBOOT_SUFFIX}"
UBOOT_BINARY = "${UBOOT_NAME}.${UBOOT_SUFFIX}"
UBOOT_SYMLINK = "${UBOOT_NAME}-${MACHINE}.${UBOOT_SUFFIX}"

KBUILD_DEFCONFIG ??= "tcc750x_defconfig"
KERNEL_BASE_ADDR = "0x20000000"

UPDATE_BOOTLOADER_NAME = "${UBOOT_NAME}.${UBOOT_SUFFIX}"
UPDATE_KERNEL_NAME = "tc-boot-${MACHINE}.img"
UPDATE_ROOTFS_NAME = "${IMAGE_LINK_NAME}.${DEFAULT_IMAGE_FSTYPE}"
#UPDATE_SNOR_NAME = "tcc750x_snor.rom"
UPDATE_DTB_NAME = "${@d.getVar("KERNEL_DEVICETREE").split("/")[-1]}"

PREFERRED_PROVIDER_virtual/kernel = "linux-telechips"

# Telechips EVB UFS Size
TCC_UFS_STORAGE_SIZE ?= "63988301824"
# Telechips EVB eMMc Size
#TCC_EMMC_STORAGE_SIZE ?= "31268536320"
TCC_EMMC_STORAGE_SIZE ?= "7818182656"
# data partition size
MAX_DATA_SIZE = "1"
HOME_DATA_SIZE = "800"

# Prevent Build error
SUBCORE_DEPLOY_DIR ?= ""
SUBCORE_BOOT_IMAGE_NAME ?= ""
SUBCORE_DTB_IMAGE_NAME ?= ""
SUBCORE_ROOTFS_IMAGE_NAME ?= ""

EXTRA_CMDLINE += "console=ttyAMA2,115200n8"