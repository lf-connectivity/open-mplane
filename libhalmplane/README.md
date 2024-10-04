# libhalmplane: Open M-Plane HAL Layer and Library
The Open M-Plane hardware abstraction layer (HAL) exposes a common interface to
management plane (M-Plane) servers for hardware configuration. The HAL is
composed of a set of declarations in the form of C header files. Each HAL
implementation defines each function contained in the C headers. Altogether the
HAL definition and implementation is called *libhalmplane*.

**More detailed software documentation can be generated using Doxygen:**
```
$ make docs
```

## File Structure
- `inc`: The C header files that compose the HAL.
- `example`: Reference source code which provides an example of what a HAL
  implementation looks like.
- `zcu111`: Source code for a ZCU111 implementation of the HAL.
- `hal-common`: Source code which may be shared across different platform
  implementations.
- `x86`: Source code for an x86 implementation of the HAL which has no radio
  frontend. This implementation is included for testing M-Plane server function.

## Building
*libhalmplane* can be built with the Makefile target `make build/$TARGET`
where `$TARGET` is the name of one of the HAL implementation source folders. A
shared library is generated and may be installed on a host system with the
`make install/$TARGET` Makefile target.

*libhalmplane* is also incorporated into the `yang-manager-server` build.

See `modular/README.md` for a detailed explanation of using the `modular` board type.
