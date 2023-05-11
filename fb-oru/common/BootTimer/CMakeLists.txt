# Cmake file for BootTimer

add_sources (SOURCES
	src/BootTimer.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(BootTimer)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/BootTimer_unittest.cpp
	)
	addGtest(BootTimer_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(BootTimer_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(BootTimer_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

