FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
        ${@bb.utils.contains('INVITE_PLATFORM', 'optee', 'file://optee.bin', '', d)} \
"

LK_MAKE_PARAM += "${@bb.utils.contains('INVITE_PLATFORM', 'optee', 'OPTEE_USE=1', '', d)}"

do_configure:append() {
        if ${@bb.utils.contains('INVITE_PLATFORM', 'optee', 'true', 'false', d)}; then
                cp -ap ${WORKDIR}/optee.bin ${S}/platform/${TCC_ARCH_FAMILY}/
        fi
}

