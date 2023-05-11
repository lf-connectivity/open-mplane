# Cmake file for common/DigitalPowerService

add_sources (SOURCES
	src/DigitalPowerService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(DigitalPowerService)

