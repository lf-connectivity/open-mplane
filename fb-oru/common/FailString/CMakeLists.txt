# Cmake file for FailString

add_sources (SOURCES
	src/FailString.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FailString)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/FailString_unittest.cpp
		gtest/FailStringTests.cpp
	)
	addGtest(FailString_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FailString_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(FailString_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

