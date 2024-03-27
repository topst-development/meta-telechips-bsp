DESCRIPTION = "Telechips CDK library"
SECTION = "libs"
LICENSE = "Telechips"

inherit autotools pkgconfig

SRC_URI = "${TELECHIPS_AUTOMOTIVE_MULTIMEDIA_GIT}/libcdk.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
SRCREV = "0d30b559440192bf5325614c3d8447d7ecf209d3"
PATCHTOOL = "git"

DEPENDS = "glib-2.0"

ADD_INCLUDE_PATH = " \
    -I${STAGING_DIR_HOST}/usr/include/glib-2.0 \
    -I${STAGING_DIR_HOST}/usr/lib/glib-2.0/include \
"

CFLAGS:append = " ${ADD_INCLUDE_PATH}"

EXTRA_OECONF += "PROCESSOR=${TCC_ARCH_FAMILY}"
EXTRA_OECONF:append:aarch64 = " TUNE_ARCH=64bit"
EXTRA_OECONF:append:arm = " TUNE_ARCH=32bit FLOAT_ABI=${TUNE_CCARGS_MFLOAT}"

SOLIBS = ".so*"
FILES_SOLIBSDEV = ""
INSANE_SKIP:${PN} += "dev-so textrel"
