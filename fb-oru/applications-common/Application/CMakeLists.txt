# Cmake file for applications/applications-common/Application

add_sources (SOURCES
	src/Application.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Application)

