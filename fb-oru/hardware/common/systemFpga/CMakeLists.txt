# Cmake file for common/systemFpga

add_sources (SOURCES
	src/SystemFpga.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(systemFpga)

