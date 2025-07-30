# Hardware Deployment Guide

This document outlines how to build and deploy the Open M‑Plane server on supported hardware targets and how to connect to it with the client utilities.

## Supported Boards

The M‑Plane software can run on multiple hardware platforms:

- **ZCU111 RFSoC** board using the provided PetaLinux project.
- **x86** (generic PC or virtual machine).
- **Modular** board type for loading different HAL modules at run time.

## Building Images with `meta-mplane`

### x86

1. Sync the Yocto layers:
   ```bash
   ./sync_yocto.sh
   ```
2. Initialise the build environment for x86:
   ```bash
   source fb-oru-init-build-env meta-x86
   ```
3. Build the image:
   ```bash
   bitbake mplane-image-x86
   ```
4. Prepare a target directory and copy the root filesystem:
   ```bash
   mkdir -p ../../mplane-server/var/volatile/log && cd ../../mplane-server/
   rsync -racvP --stats ../open-mplane/meta-mplane/build/tmp/work/mplanex86-poky-linux/mplane-image-x86/1.0-r0/rootfs/ .
   ```
5. Bind mount required pseudo filesystems and chroot:
   ```bash
   for i in /dev /proc /run /sys; do sudo mount --bind $i ${i:1}; done
   sudo chroot $(pwd) /bin/bash
   ```
6. Run the setup scripts inside the chroot and start the server:
   ```bash
   usr/share/netopeer2/scripts/setup.sh
   usr/share/netopeer2/scripts/merge_hostkey.sh
   usr/share/netopeer2/scripts/merge_config.sh
   usr/share/mplane-server/scripts/o-ran-user-config.sh
   mplane-server-app --cfg-data-path /usr/share/mplane-server --netopeer-path /usr/local/bin --yang-mods-path /usr/share/mplane-server/modules --netopeerdbg 2
   ```

### ZCU111

1. Sync the Yocto layers:
   ```bash
   ./sync_yocto.sh
   ```
2. Create a PetaLinux project using the supplied BSP:
   ```bash
   petalinux/create_petalinux_project.sh <BSP> zcu111
   ```
3. Build the project:
   ```bash
   petalinux-build
   ```
4. Generate an application archive that contains the runtime files:
   ```bash
   utils/zcu111_archive.sh <build_dir>
   ```
5. Copy the resulting `app.tgz` to the board (e.g. `/nandflash/app-images`) and boot using the PetaLinux image. The startup scripts unpack the archive and launch the server on boot.

### Modular Board

Set `BUILD_BOARD=modular` when invoking BitBake so that the HAL module can be selected at runtime:
```bash
BUILD_BOARD=modular BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE BUILD_BOARD" bitbake mplane-image-x86
```
Modules are enabled by editing `/usr/share/mplane-server/YangConfig.xml` and specifying the desired `libhalmplane-mod-*.so` file.

## Connecting Clients

After `mplane-server-app` is running, use the client utilities from this repository:

1. Build the [mplane_client](mplane_client/README.md) following its README.
2. Use the [`mpclient-demo`](mplane_client/example/README.md) or the CLI tool [`climp`](climp/README.md) to issue NETCONF requests. Both tools require network access to the server's NETCONF port (830 by default).

These steps provide a basic end‑to‑end environment where the client can communicate with the server over NETCONF.
