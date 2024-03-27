DESCRIPTION = "Telechips Make Image tools"
LICENSE = "Telechips"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta-telechips/meta-core/licenses/Telechips;md5=e23a23ed6facb2366525db53060c05a4"
SECTION = "bsp"

inherit native

SRC_URI = "${TELECHIPS_AUTOMOTIVE_GIT}/tools/mktcimg.git;protocol=${ALS_GIT_PROTOCOL};branch=${ALS_BRANCH}"
SRCREV = "d7f9f9ae15e4fd07228c54e698c257afb6318cf4"

S = "${WORKDIR}/git"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/mktcimg		${D}${bindir}
}

do_configure[noexec] = "1"
do_compile[noexec] = "1"

BBCLASSEXTEND = "native"
