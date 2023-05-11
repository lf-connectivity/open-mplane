# fb-oru
This directory contains software for the operating system, services, and
applications of an O-RAN Radio Unit (O-RU). The contents comprise a completely
integrated software architecture meant for specific hardware platforms.

Some original portions of the software are excluded due to licensing and
copyright constraints, so the code is not fully buildable as-is. The source code
is provided as a reference for a nearly-complete software implementation.

**More detailed software documentation can be generated using Doxygen:**
```
$ cd buildTools/cmake
$ make TARGET=petalinux BOARD=ZCU111 CUSTOMER=MPLANE APPLICATION=ORANRRH save-settings
$ DOCS_ONLY=1 BUILD_TYPE=radio make doxygen
```
