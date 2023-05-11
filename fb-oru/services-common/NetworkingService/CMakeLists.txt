# Cmake file for common/NetworkingService

add_sources (SOURCES
	src/NetworkingService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(NetworkingService)


