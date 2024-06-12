# Base this image on core-image-minimal
require recipes-core/images/core-image-minimal.bb

# Include modules in rootfs
IMAGE_INSTALL += " \
    bash \
    climp \
    libffi \
    lua \
    lua-argparse \
    lua-luaunit \
    lua-penlight \
    luajit \
    os-release \
    vim \
    virtual/halmplane \
    netopeer2 \
    mplane-server \
    "

# Set en_US as the default locale
IMAGE_LINGUAS += "en-us"
