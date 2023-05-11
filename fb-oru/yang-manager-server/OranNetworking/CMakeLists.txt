# Cmake file for OranNetworking

add_sources (SOURCES
	src/OranNetAddrDhcp.cpp
	src/OranNetAddrDhcpVlan.cpp
	src/DhcpOptions.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(OranNetworking)
