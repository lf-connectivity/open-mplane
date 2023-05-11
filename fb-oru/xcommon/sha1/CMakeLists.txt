# Cmake file for sha1

add_sources (SOURCES
	src/Sha1.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(sha1)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Sha1_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(sha1_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(sha1_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(sha1_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

