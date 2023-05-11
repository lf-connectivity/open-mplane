# Cmake file for common/RrhFreqPolicy

add_sources (SOURCES
	src/RrhFreqPolicy.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RrhFreqPolicy)


