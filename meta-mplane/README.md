# meta-mplane
This directory contains a Yocto meta layer, meta-mplane, for building the
M-Plane software along with its dependencies.

Example usage:
```
$ ./sync_yocto.sh
$ source fb-oru-init-build-env meta-armv8 build-armv8
$ bitbake mplane-server
```

### Building mplane_server for x86

#### Build the target environment:
```bash
# Install the dependencies (on Ubuntu 20)
sudo apt install -y build-essential chrpath diffstat

# Sync the yocto repositories
./sync_yocto.sh

# Set the build platform as meta-x86
source fb-oru-init-build-env meta-x86

# Start the build process
bitbake mplane-image-x86
```

#### Prepare the mplane_server environment:
```bash
# Create a target directory for the root filesystem
mkdir -p ../../mplane-server/var/volatile/log && cd ../../mplane-server/

# Sync the mplane-server’s yocto rootfs build
rsync -racvP --stats ../open-mplane/meta-mplane/build/tmp/work/mplanex86-poky-linux/mplane-image-x86/1.0-r0/rootfs/ .

# Mount these directories
for i in /dev /proc /run /sys; do sudo mount --bind $i ${i:1}; done

# Chroot into this directory
sudo chroot $(pwd) /bin/bash

# Run these scripts
usr/share/netopeer2/scripts/setup.sh
usr/share/netopeer2/scripts/merge_hostkey.sh
usr/share/netopeer2/scripts/merge_config.sh
usr/share/mplane-server/scripts/o-ran-user-config.sh
```

#### Run the mplane_server:
```bash
# Open a new terminal and run the following command to display the server logs
tail -f var/log/console.log

# Run the mplane_server commands in the chrooted terminal
mplane-server-app --help
```

The terminal window displaying console.log would show the following:

```
Mplane O-RAN M-Plane

OPTIONS
  --help                       Show help

  --call-home-clients STRING   File path containing call home client information
  --cfg-data-path STRING       Path to YANG configuration data (required)
  --grouplog STRING            Logging for groups (name=level:name=level..) [Env variable: GROUPLOG]
  --instlog STRING             Logging for instances (name=level:name=level..) [Env variable: INSTLOG]
  --netopeer-path STRING       Path to Netopeer2 application (required)
  --netopeerdbg INT            NETCONF server debug level (0-2) [Env variable: NETCONFDBG] [Default: 1]
  --yang-mods-path STRING      Path to YANG modules (required)
```

```bash
# Start the mplane_server
mplane-server-app --cfg-data-path /usr/share/mplane-server --netopeer-path /usr/local/bin --yang-mods-path /usr/share/mplane-server/modules --netopeerdbg 2
```

console.log would display:
```
… [log truncated]
[INF]: SR: Successful processing of "done" event with ID 7 priority 0 (remaining 0 subscribers).
MSG /usr/src/debug/mplane-server/1.0-r0/mplane_server/services/ORANRRH/AppControl/src/OranRrhAppControl.cpp::start():46 [mServicesMonitor->startMonitoring]
MSG /usr/src/debug/mplane-server/1.0-r0/mplane_server/services/ORANRRH/AppControl/src/OranRrhAppControl.cpp::start():53 [mApplicationServices->start]
MSG /usr/src/debug/mplane-server/1.0-r0/mplane_server/services/ORANRRH/AppControl/src/OranRrhAppControl.cpp::start():60 [mServicesMonitor->applicationStable]
END /usr/src/debug/mplane-server/1.0-r0/mplane_server/services/ORANRRH/AppControl/src/OranRrhAppControl.cpp::start()
```

Check the port to verify:
```
sudo lsof -i:830 +c0
```

```
COMMAND         PID   USER  FD  TYPE DEVICE SIZE/OFF NODE NAME
netopeer2-serve 82858 root  27u IPv4 107743 0t0      TCP  *:830 (LISTEN)
```

You can also use the [mpclient-demo](https://github.com/lf-connectivity/open-mplane/tree/main/mplane_client/example)
or [M-Plane Demo](https://github.com/lf-connectivity/open-mplane/tree/main/mplane_client/example/demo) to connect to the server


#### Rebuild Process:

If you make any changes to the server source, you’ll have to rebuild the server:
```bash
# Change to meta-mplane directory
cd open-mplane/meta-mplane/

# Set the build platform as meta-x86 (only once during a shell session)
source fb-oru-init-build-env meta-x86

# Start the build process
bitbake mplane-image-x86

# Open a new terminal tab and cd to the previously created mplane-server directory
cd ../../mplane-server/

# Mount these directories if they aren’t already mounted (rebooting the system will unmount them)
for i in /dev /proc /run /sys; do sudo mount --bind $i ${i:1}; done

# Sync with the updated yocto rootfs
rsync -racvP --stats --exclude={dev,proc,run,sys} ../open-mplane/meta-mplane/build/tmp/work/mplanex86-poky-linux/mplane-image-x86/1.0-r0/rootfs/ .

# Chroot into this directory
sudo chroot $(pwd) /bin/bash

# Now you can start using mplane_server commands
mplane-server-app --cfg-data-path /usr/share/mplane-server --netopeer-path /usr/local/bin --yang-mods-path /usr/share/mplane-server/modules --netopeerdbg 2
```

Tip: Maintain three terminal tabs for bitbake, rsync, and chroot commands. This way, you can stay inside the chroot environment while building and syncing in the other shells.

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
