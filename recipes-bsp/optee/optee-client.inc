# require optee-common.inc

LICENSE = "Telechips"
SECTION = "optee"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta-telechips-bsp/licenses/Telechips;md5=e23a23ed6facb2366525db53060c05a4"
inherit tcc_bsp_feature_check
REQUIRED_TCC_BSP_FEATURES = "optee"


SUMMARY = "OP-TEE Client API"
DESCRIPTION = "Open Portable Trusted Execution Environment - Normal World Client side of the TEE"
HOMEPAGE = "https://www.op-tee.org/"

LICENSE = "BSD-2-Clause"

inherit systemd update-rc.d cmake

OPTEE_CLIENT_SRC_URL = "${TELECHIPS_AUTOMOTIVE_TEE_GIT}/optee-client.git"
SRC_URI = " \
    ${OPTEE_CLIENT_SRC_URL};protocol=${ALS_GIT_PROTOCOL};branch=${OPTEE_BRANCH} \
    file://tee-supplicant.service \
    file://tee-supplicant.sh \
"

UPSTREAM_CHECK_GITTAGREGEX = "^(?P<pver>\d+(\.\d+)+)$"

S = "${WORKDIR}/git"

EXTRA_OECMAKE = " \
    -DBUILD_SHARED_LIBS=ON \
    -DCFG_TEE_CLIENT_LOAD_PATH='/usr/lib' \
    -DCFG_TEE_FS_PARENT_PATH='/opt/tee' \
    -DWITH_TEEACL=OFF \
    -DRPMB_EMU=OFF \
"

EXTRA_OECMAKE:append:toolchain-clang = " -DCFG_WERROR=0"

do_install:append() {
    install -D -p -m0644 ${WORKDIR}/tee-supplicant.service ${D}${systemd_system_unitdir}/tee-supplicant.service
    install -D -p -m0755 ${WORKDIR}/tee-supplicant.sh ${D}${sysconfdir}/init.d/tee-supplicant

    sed -i -e s:@sysconfdir@:${sysconfdir}:g \
           -e s:@sbindir@:${sbindir}:g \
              ${D}${systemd_system_unitdir}/tee-supplicant.service \
              ${D}${sysconfdir}/init.d/tee-supplicant
}

SYSTEMD_SERVICE:${PN} = "tee-supplicant.service"

INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME:${PN} = "tee-supplicant"
INITSCRIPT_PARAMS:${PN} = "start 10 1 2 3 4 5 . stop 90 0 6 ."
