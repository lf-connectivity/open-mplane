# meta-mplane
This directory contains a Yocto meta layer, meta-mplane, for building the
M-Plane software along with its dependencies.

Example usage:
```
$ ./sync_yocto.sh
$ source fb-oru-init-build-env meta-armv8 build-armv8
$ bitbake mplane-server
```

## Directory Contents
- `recipes-mplane`: Recipes for various M-Plane software components. The
  main M-Plane server application is built with the recipe found in the
  subdirectory `mplane-server`. Most of the other subdirectories contain recipes
  and files for the different components that comprise the fb-oru build.
- `recipes-core`: Recipes for an x86 software image with the M-Plane server.
- `recipes-support`: Recipes for third party libraries and dependencies.
- `recipes-zcu111`: Recipes specific to the ZCU111 hardware platform.
- `petalinux`: Project specifications for building petalinux for ZCU111.
- `meta` directories contain metadata for building meta layers for specific
  hardware platforms.
