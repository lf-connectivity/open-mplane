# Open M-Plane
This repository contains software implementing portions of the Management Plane
(M-Plane) according to O-RAN Alliance specifications. The M-Plane is part of the
Open Fronthaul Interface specified by O-RAN Workgroup 4.

## Repository Contents
* **meta-mplane** - Yocto meta layer for building the M-Plane software along
  with its dependencies.
* **libhalmplane** - Hardware abstraction layer to integrate
  hardware-dependent configurations with the M-Plane server.
* **mplane_server** - Standalone M-Plane server application, largely based on
  the implementation in `fb-oru`.
* **mplane_client** - M-Plane client implementation.
* **climp** - A command-line interface utility for M-Plane operations.

## Client and Server Configuration Workflow
* Follow the [meta-mplane](https://github.com/lf-connectivity/open-mplane/tree/main/meta-mplane)
  setup guide to build and run the mplane_server
* Build the [mplane_client](https://github.com/lf-connectivity/open-mplane/tree/main/mplane_client)
  on your host or using Docker
* Use the [mpclient-demo](https://github.com/lf-connectivity/open-mplane/tree/main/mplane_client/example)
  or the [M-Plane Demo](https://github.com/lf-connectivity/open-mplane/tree/main/mplane_client/example/demo)
  to connect and communicate with the server

## License
Open M-Plane is MIT licensed, as found in the LICENSE file.
