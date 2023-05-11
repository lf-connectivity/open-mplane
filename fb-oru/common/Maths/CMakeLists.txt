# Cmake file for Maths

add_sources (SOURCES
	src/Maths.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Maths)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	addTestCommon(TEST_COMMON common)

	include (coverage)
	include (valgrind)


	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Maths_unittest.cpp
	)
	addGtest(Maths_GTEST "" ${gtest_src})

	addCoverage(Maths_GTEST)
	addMemcheck(Maths_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

