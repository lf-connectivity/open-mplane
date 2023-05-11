# Cmake file for common/regData

add_sources (SOURCES
	src/RegData.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(regData)

