# Cmake file for ART/UpdateService

add_sources (SOURCES
	src/Zcu111OranRrhUpdateService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Zcu111OranRrhUpdateService)

