# Cmake file for Feature

add_sources (SOURCES
	src/GenericFeature.cpp
	src/Feature.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Feature)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/GenericFeature_unittest.cpp
		gtest/Feature_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(Feature_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Feature_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(Feature_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

