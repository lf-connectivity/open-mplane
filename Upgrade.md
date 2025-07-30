# Upgrade Guide

This document outlines the high level steps required to bring the Open M-Plane
project in line with newer versions of the O-RAN specifications. It focuses on
updating YANG models, HAL interfaces and third‑party dependencies such as
libyang.

## Update Dependencies
- Migrate to **libyang v2** and refresh dependent libraries (libnetconf2,
  sysrepo). Ensure that the Yocto recipes under `meta-mplane` build against the
  new versions.
- Verify that other bundled dependencies remain compatible or update them to the
  latest releases supported by libyang v2.

## Refresh YANG Models
- Replace the existing models in `mplane_server/yang-models` with the latest
  O-RAN releases. Keep any vendor specific modules in a separate directory.
- Review generated C++ bindings and adjust them for libyang v2 APIs.
- Update test data files and default configuration snippets so that the server
  loads the new modules without errors.

## HAL Interface Adjustments
- Align header files in `libhalmplane/inc` with the current O-RAN M-Plane HAL
  definitions. Remove deprecated calls and add new API functions as required.
- Update all sample implementations located under `libhalmplane` (for example the
  `x86` and `zcu111` directories) to match the new interfaces.

## Changes in `mplane_server`
- Replace legacy libyang function calls with their libyang v2 equivalents.
- Rebuild the YANG handler classes in
  `mplane_server/yang-manager-server/yang-model-handlers` to match the updated
  models.
- Revise startup scripts and systemd unit files to account for any new server
  options or configuration paths.

## Changes in `mplane_client`
- Update the NETCONF layer to use libyang v2 based tooling and rebuild gRPC
  stubs if the YANG models introduce new RPCs.
- Rework client configuration logic so that it can parse and send the updated
  YANG schemas.
- Validate that example code under `mplane_client/example` compiles with the
  refreshed dependencies.

## Testing Recommendations
- Build the complete software stack on a reference platform using the updated
  meta layer. Execute unit tests under `mplane_server` and `mplane_client`.
- Use the provided demo client to establish a NETCONF session with the server and
  exercise basic configuration operations.
- Run O-RAN conformance tests or simulators to verify compatibility with the
  targeted O-RAN release.

