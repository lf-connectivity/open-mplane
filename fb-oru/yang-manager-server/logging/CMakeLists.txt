add_sources (SOURCES
	src/LoggerFactory.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(yms-logging)