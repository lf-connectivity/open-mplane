# Cmake file for common/WatchdogCount

add_sources (SOURCES
	src/WatchdogCount.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(watchdogCount)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/WatchdogCount_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(WatchdogCount_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(WatchdogCount_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(WatchdogCount_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

