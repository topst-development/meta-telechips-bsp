require optee-client.inc

#EXTRA_OECMAKE += " \
#    -DPROJECT_VERSION=3.22 \
#    -DPROJECT_VERSION_MAJOR=3 \
#"

COMPATIBLE_MACHINE = "(tcc803x|tcc805x|tcc750x|tcc807x)"
OPTEE_BRANCH = "v3.22"
SRCREV = "${AUTOREV}"
