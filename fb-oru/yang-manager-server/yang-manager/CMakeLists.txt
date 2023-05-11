# Cmake file for yang-manager-server/yang-manager

add_sources (SOURCES
	src/YangModule.cpp
	src/YangModuleMgr.cpp
	src/YangParam.cpp
	src/YangParamUtils.cpp
	src/YangUtils.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(yangmanager)

