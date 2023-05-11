# Cmake file for yang-manager-server/RadioDatastore

add_sources (SOURCES
	src/RadioDatastore.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(raddatastore)

