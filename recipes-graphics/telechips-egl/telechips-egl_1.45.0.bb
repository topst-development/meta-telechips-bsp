require ${BPN}.inc

SRC_URI = "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/3dmali.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"

SRCREV = "207f22d0145ee52719a81cf656ac823f43f95cc1"

MALI_VER = "r${@d.getVar("PV").split(".")[1]}"

PATCHTOOL = "git"

COMPATIBLE_MACHINE = "(tcc897x|tcc803x|tcc807x)"
