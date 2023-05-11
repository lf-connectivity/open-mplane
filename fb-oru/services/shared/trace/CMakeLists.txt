# Cmake file for shared/trace

add_sources (SOURCES
	src/TraceExampleFile.cpp
	src/TraceHelper.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(trace)

