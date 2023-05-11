# Cmake file for MovingAvg

add_sources (SOURCES
	src/MovingAvg-dummy.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(MovingAvg)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/MovingAvg_unittest.cpp
		gtest/MovingAvgTests.cpp
	)
	addGtest(MovingAvg_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(MovingAvg_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(MovingAvg_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

