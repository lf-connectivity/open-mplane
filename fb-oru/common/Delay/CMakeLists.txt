# Cmake file for Delay

add_sources (SOURCES
	src/Delay.cpp
	src/DelayUnit/DelayUnitBF.cpp
	src/DelayUnit/DelayUnitNS.cpp
	src/DelayUnit/DelayUnitUI.cpp
)

## Cppcheck
#include (cppcheck)
#addCppcheck(Delay)

#if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
#	include (gtest)

#	include_directories(gtest)
#	set(gtest_src
#		gtest/Delay_unittest.cpp
#		gtest/DelayTests.cpp
#	)
#	addGtest(Delay_GTEST "" ${gtest_src})

	# Add code coverage
#	include (coverage)
#	addCoverage(Delay_GTEST)
	# Add memory leak check
#	include (valgrind)
#	addMemcheck(Delay_GTEST)

#endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

