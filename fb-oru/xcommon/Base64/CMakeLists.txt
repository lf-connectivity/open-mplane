# Cmake file for Base64

add_sources (SOURCES
	src/Base64.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Base64)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")

    # Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Base64_unittest.cpp
	)
	addGtest(Base64_GTEST "${libs}" ${gtest_src})

    # Add code coverage
	include (coverage)
	addCoverage(Base64_GTEST)
    # Add memory leak check
	include (valgrind)
	addMemcheck(Base64_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

