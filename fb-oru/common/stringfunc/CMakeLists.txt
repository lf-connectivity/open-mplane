# Cmake file for stringfunc

add_sources (SOURCES
)

## Cppcheck
include (cppcheck)
addCppcheck(stringfunc)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/stringfunc_unittest.cpp
	)
	addGtest(stringfunc_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(stringfunc_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(stringfunc_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

