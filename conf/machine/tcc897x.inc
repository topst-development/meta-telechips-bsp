#@TYPE: Machine
#@NAME: Telechips TCC897x Family
#@DESCRIPTION: Machine configuration for the Telechips EVM Board

require conf/machine/include/arm/armv7a/tune-cortexa7.inc
require tcc-family.inc

LK_PROJECT_NAME = "tcc897x_evm_emmc"
LK_TARGET_NAME = "tcc897x_evm"
LK_RULE_NAME = "tcc8970_evm_d3_08x4_sv0.1.mk"
GST_ARCH_FAMILY_NAME = "TCC_897x"
LCD_WIDTH ??= "1024"
LCD_HEIGHT ??= "600"

SERIAL_CONSOLE = "115200;ttyS0"
KERNEL_CONSOLE = "ttyS0"

CONFLICT_MACHINE_FEATURES = "ufs"

EXTRA_IMAGEDEPENDS += "lk-dt"

LINUX_VERSION = "5.4.254"
LINUXLIBCVERSION = "5.4"

# GPU configuration
PREFERRED_PROVIDER_virtual/egl      = "telechips-egl"
PREFERRED_PROVIDER_virtual/libgles1 = "telechips-egl"
PREFERRED_PROVIDER_virtual/libgles2 = "telechips-egl"
PREFERRED_PROVIDER_virtual/mesa     = "telechips-egl"
PREFERRED_PROVIDER_virtual/libgl    = "telechips-egl"
PREFERRED_PROVIDER_libglapi         = "telechips-egl"
PREFERRED_PROVIDER_libgbm           = "telechips-egl"
PREFERRED_PROVIDER_libwayland-egl   = "telechips-egl"

FWDN_VERSION = "7"
DATA_PART_FSTYPE = "vfat"

SKIP_RECIPE[boot-firmware] = "not buildable with tcc897x"
