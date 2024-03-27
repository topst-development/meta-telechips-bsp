require ${BPN}.inc

SRC_URI = "${TELECHIPS_AUTOMOTIVE_BSP_GIT}/gpu.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH};"
SRC_URI += "file://pkgconfig"

SRCREV = "3ad4ff37a66710f703fb17df852ae8dd3df84e0f"

PATCHTOOL = "git"
COMPATIBLE_MACHINE = "tcc805x"
