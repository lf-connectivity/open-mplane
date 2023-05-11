# Cmake file for Spline

add_sources (SOURCES
	src/Spline.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Spline)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Spline_unittest.cpp
		gtest/SplineTests.cpp
	)
	addGtest(Spline_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage( Spline_GTEST )
	# Add memory leak check
	include (valgrind)
	addMemcheck( Spline_GTEST )

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

