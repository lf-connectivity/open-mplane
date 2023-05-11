# Cmake file for Process

add_sources (SOURCES
	src/Process.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Process)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Process_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(Process_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Process_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(Process_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

