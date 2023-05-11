# Cmake file for yang-manager-server/services-ORANRRH

add_sources (SOURCES
	src/YangOranrrhServices.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(services-ORANRRH)

