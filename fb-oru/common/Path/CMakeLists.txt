# Cmake file for Path

add_sources (SOURCES
	src/Path.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Path)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Path_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(Path_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Path_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(Path_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

