# Build Tools
This folder contains Make and CMake files needed to build the M-Plane server software.

More documentation on these processes can be found in `buildTools/cmake/doc/design.dox`.

## Usage
The first step is to build the Reusable Operating System (ROS) for all targets:
```
cd ros
https_proxy=fwdproxy:8080 http_proxy=fwdproxy:8080 make board=HOST
make board=ZCU111 LOCAL_SRC_MIRROR=$PETALINUX
make board=ATLAS LOCAL_SRC_MIRROR=$PETALINUX
```

After this, it is possible to build the actual targets. For example, to build the x86 emulation for the ZCU111 and/or Atlas boards:
```
cd buildTools/cmake

make TARGET=x86_64 BOARD=ZCU111 CUSTOMER=MPLANE APPLICATION=ORANRRH save-settings
make TEST_SHARED=1 LAB=1 all
make pkg

make TARGET=x86_64 BOARD=ATLAS CUSTOMER=MPLANE APPLICATION=ORANRRH save-settings
make TEST_SHARED=1 LAB=1 all
make pkg
```

And to build the petalinux images which can be flashed to physical hardware:
```
cd buildTools/cmake

make FPGA=RRH TARGET=petalinux BOARD=ZCU111 CUSTOMER=MPLANE APPLICATION=ORANRRH save-settings
make TEST_SHARED=1 LAB=1 all
make pkg

make FPGA=RRH TARGET=petalinux BOARD=ATLAS CUSTOMER=MPLANE APPLICATION=ORANRRH save-settings
make TEST_SHARED=1 LAB=1 all
make pkg
```

## Note on FPGAs
The software in its current form assumes that hardware implementations of the RU take the form of an FPGA. This is evident with the FPGA variables being passed around, e.g. `FPGA_MANIFEST` or `FPGA_VENDOR`. The current configuration requires that FPGA tar archives be placed in a path formatted as `fpga/images/${BOARD}-${CUSTOMER}-${APPLICATION}`; these parameters are the same as those used in the `make` command.

The majority of the logic for finding and extracting FPGAs is located in `buildTools/cmake/make/fpgavars_example.mk` and `buildTools/cmake/inc/installFpga_example.cmake.in`, respectively. These can be treated as placeholders for the processes used to incorporate vendor-specific hardware.
