SUMMARY = "Packages used by the Open M-Plane server"

inherit packagegroup

RRECOMMENDS_${PN} = "\
    bash \
    climp \
    libffi \
    lua \
    lua-argparse \
    lua-luaunit \
    lua-penlight \
    luajit \
    mplane-server \
    netopeer2 \
    packagegroup-mplane-utils \
    os-release \
    "
