# Cmake file for yang-manager-server/yang-handlers

add_sources (SOURCES
	src/XpathUtils.cpp
	src/YangPersist.cpp
	src/YangHandler.cpp
	src/YangHandlerMgr.cpp

	src/YangCarrierMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(yanghandlers)

