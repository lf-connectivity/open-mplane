# Cmake file for common/HighSpeedEthernet

add_sources (SOURCES
	src/HighSpeedEthernet.cpp
	src/RtcIEEE1588.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(HighSpeedEthernet)

