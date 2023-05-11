# mplane_server
This directory contains code for a standalone M-Plane server application that
can be built independently from any specific hardware implementation. This is
derived from the original code found in the top-level `fb-oru` directory which
was built for specific hardware platforms.

Hardware-specific functionality needs to be implemented according to a defined
HAL interface, found in the top-level `libhalmplane` directory.

Yocto recipes for the M-Plane server application and its dependencies are found
in the top-level `meta-mplane` directory.

The server application is compatible with any NETCONF client. `netopeer2-cli`
is a simple NETCONF client that may be a convenient tool for testing.

## Usage
The M-Plane server application has the following command-line options:
```
  --help                       Show help

  --call-home-clients STRING   File path containing call home client information
  --cfg-data-path STRING       Path to YANG configuration data (required)
  --grouplog STRING            Logging for groups (name=level:name=level..) [Env variable: GROUPLOG]
  --instlog STRING             Logging for instances (name=level:name=level..) [Env variable: INSTLOG]
  --netopeer-path STRING       Path to Netopeer2 application (required)
  --netopeerdbg INT            NETCONF server debug level (0-2) [Env variable: NETCONFDBG] [Default: 1]
  --yang-mods-path STRING      Path to YANG modules (required)
```

An example usage of the application with defaults installed by the Yocto recipes
looks like:
```bash
$ mplane-server-app \
  --cfg-data-path /usr/share/mplane-server \
  --netopeer-path /usr/local/bin \
  --yang-mods-path /usr/share/mplane-server/modules
```

The stdout output of the program will be directed to "/var/log/console.log", and
most logs can be found in the syslog output.

The `mplane-server-app` will try to start an instance of `netopeer2-server` when
it starts. If that fails for whatever reason, such as when another instance of
`netopeer2-server` already running, the `mplane-server-app` will exit. The
program can be terminated with SIGINT, and it will also stop the instance of
`netopeer2-server` that it was running.

### Configuration Options
The `--call-home-clients` option takes in a file with lines of the form `{ip}={port}`, for example `0.0.0.0=4334`.

The `--cfg-data-path` option specifies a directory containing a "YangConfig.xml"
file which will specify YANG modules to enable as well as default values for
supported YANG handlers. The example file
"yang-manager-server/yang-config/YangConfig.xml" is installed by the Yocto
recipe.

If the "o-ran-usermgmt" YANG module is enabled, then at least one o-ran user
must be enabled to load the module. The set-up script provided in
"mplane_server/scripts/o-ran-user-config.sh" and installed to
"/usr/share/mplane-server/o-ran-user-config.sh" does this, providing just a root
user by default, and taking in additional users specified by a user list as
well. If the application exits or the device reboots, the script does not need
to be run again.

The `--grouplog` and `--instlog` options specify logging levels for different
groups and instances in the M-Plane server application. Groups and instances for
different code paths can be identified in the code itself.

## Implementation
Refer to [IMPLEMENTATION.md](IMPLEMENTATION.md).
