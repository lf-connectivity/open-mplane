# Cmake file for common/systemClockInput

add_sources (SOURCES
	src/SystemClockInput.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(systemClockInput)

