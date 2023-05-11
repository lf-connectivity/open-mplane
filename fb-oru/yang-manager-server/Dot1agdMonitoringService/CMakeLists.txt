# Cmake file for yang-manager-server/Dot1agdMonitoringService

add_sources (SOURCES
	src/Dot1agdMonService.cpp
	src/Dot1agdMonServiceSingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Dot1agdMonitoringService)
