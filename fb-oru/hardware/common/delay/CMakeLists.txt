# Cmake file for common/delay

add_sources (SOURCES
	src/DelayUnit/DelayUnitCLK.cpp
	src/DelayUnit/DelayUnitCLK128.cpp
	src/DelayUnit/DelayUnitFPGA.cpp
	src/DelayUnit/DelayUnitFpgaTimer.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(delay)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Add code coverage
	include (coverage)

	# Add memory leak check
	include (valgrind)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

