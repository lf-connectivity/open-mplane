# Cmake file for Dpd2Service

add_sources (SOURCES
	src/RadioDpd2Service.cpp
	src/DpdMinorAlarm.cpp
	src/DpdMajorAlarm.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RadioDpd2Service)

