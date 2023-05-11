add_sources (SOURCES
	src/ORanLogFile.cpp
	src/ORanLogFileMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(oranlogfile)

