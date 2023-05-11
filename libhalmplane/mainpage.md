The Management-Plane Hardware Abstraction Library (M-Plane HAL) allows for the
development of portable M-Plane software. The primary use-case for the M-Plane
HAL is the M-Plane server, the function of which is detailed by the O-RAN
Alliance's Working Group 4 (O-RAN WG4). M-Plane servers run on O-RU and are
controlled by clients on the O-DU and Service Management and Orchestration (SMO)
systems. Much of the functionality of the M-Plane server is hardware-specific,
and there are many required and optional features in the M-Plane specification.
The M-Plane HAL abstracts all M-Plane hardware dependencies so that the M-Plane
server may function across a variety of O-RU.

<h2>M-Plane System with HAL</h2>
The following diagram shows how the HAL is used alongside other software
provided in meta-mplane:

![HAL Software](hal_system_diagram.svg)

The yellow boxes represent recipes in the meta-mplane layer. The blue boxes
represent vendor-specific software. The HAL layer may take the form of a
shared library that is linked to the M-Plane server.

<h2>Index</h2>
This site contains the following sections documenting the M-Plane HAL:

- Modules: The M-Plane HAL functions organized according to the O-RAN WG4 YANG
  modules. This section contains the HAL function definitions.
- Classes: Details about data structures used by the M-Plane HAL.
- Files: The C-header files that compose the HAL.
