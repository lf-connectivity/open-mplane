# Cmake file for common/systemReboot

add_sources (SOURCES
	src/SystemReboot.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(systemReboot)

