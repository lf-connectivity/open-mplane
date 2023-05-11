# Cmake file for yang-manager-server/yang-manager-service

add_sources (SOURCES
	src/YangMgrService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(yangmanagerservice)

