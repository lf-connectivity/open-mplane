# Cmake file for common/RegDevice

add_sources (SOURCES
	src/RegDevice.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RegDevice)

