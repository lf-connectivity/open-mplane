# Cmake file for PacketSniffer

add_sources (SOURCES
	src/PacketSniffer.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(PacketSniffer)

