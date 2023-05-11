# Cmake file for common/Dpd2Service

add_sources (SOURCES
	src/Dpd2Service.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Dpd2Service)
