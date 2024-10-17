# *libhalmplane* `modular` Board

This board will allow selecting the halmplane driver for any other compatible
board by specifying the filename of its shared library in the server configuration.

## Building
`mplane_server` must be build with BUILD_BOARD=modular

```
BUILD_BOARD=modular BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE BUILD_BOARD" bitbake mplane-image-x86
```

To rebuild with a different builtin board type it may be necessary to rebuild that explicitly
to invalidate the build hash even though the source files have not changed.
```
BUILD_BOARD=example BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE BUILD_BOARD" bitbake -C configure halmplane
```

To select a module in config file, edit `/usr/share/mplane-server/YangConfig.xml`
in the `<halmplane-board-modular>` element.

To build a specific module
```
BUILD_BOARD=example BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE BUILD_BOARD" bitbake -C configure halmplanemodule
```

Each module has by default a filename of the form `libhalmplane-mod-<BUILD_BOARD>.so` with symlinks
generated that reflect the version. This will allow parallel installation of multiple modules without
packaging conflicts.

The current bitbake recipes do not support automatically installing the resulting module into the
project `rootfs`, so a command similar to
```
cp ./tmp/work/core2-64-poky-linux/halmplanemodule/1.1-r0/image/usr/lib/libhalmplane-mod-example.so.1.1.0 ./tmp/work/mplanex86-poky-linux/mplane-image-x86/1.0-r0/rootfs/usr/lib/
```
can achieve the desired outcome manually.


## Enabling a board for use as a module
To operate as a module, the only thing needed is to provide a function with prototype
```
void *function_map();
```
that is also `extern "C"`. Sample code can be found in `example/src/HalMplane.cpp`
and a complete list of supported API endpoints can be found in `modular/src/HalMplane.cpp`.
