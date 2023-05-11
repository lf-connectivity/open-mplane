# Cmake file for TimeoutTimer

add_sources (SOURCES
	src/TimeoutTimer.cpp
	src/NullTimeoutTimer.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(TimeoutTimer)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/TimeoutTimer_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(TimeoutTimer_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(TimeoutTimer_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(TimeoutTimer_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

