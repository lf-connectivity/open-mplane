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
* **fb-oru** - Code for the operating system and applications of an O-RU. This
  includes the legacy implementation of the M-Plane server, which has most of
  its code contained in `fb-oru/yang-manager-server`.

## License
Open M-Plane is MIT licensed, as found in the LICENSE file.
