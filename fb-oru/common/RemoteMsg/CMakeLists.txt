# Cmake file for RemoteMsg

add_sources (SOURCES
	src/RemoteMsg.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RemoteMsg)

