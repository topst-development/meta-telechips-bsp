# Common Includes for OPTEE bitbake

LICENSE = "Telechips"
SECTION = "optee"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta-telechips-bsp/licenses/Telechips;md5=e23a23ed6facb2366525db53060c05a4"

OPTEE_SRC_URL = "${TELECHIPS_AUTOMOTIVE_TEE_GIT}/${TCC_ARCH_FAMILY}.git"
SRC_URI = "${OPTEE_SRC_URL};protocol=${ALS_GIT_PROTOCOL};branch=${OPTEE_BRANCH}"

inherit tcc_bsp_feature_check

REQUIRED_TCC_BSP_FEATURES = "optee"
