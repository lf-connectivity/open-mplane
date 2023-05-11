# Cmake file for PathUtils

add_sources (SOURCES
	src/PathUtils.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(PathUtils)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/PathUtils_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(PathUtils_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(PathUtils_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(PathUtils_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

