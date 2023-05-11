# Cmake file for cubicSpline

add_sources (SOURCES
	src/matlab_cubic_spline.cpp
	src/matlab_cubic_spline_emxAPI.cpp
	src/matlab_cubic_spline_emxutil.cpp
	src/matlab_cubic_spline_initialize.cpp
	src/matlab_cubic_spline_terminate.cpp
	src/spline.cpp
	src/rtGetInf.cpp
	src/rtGetNaN.cpp
	src/rt_nonfinite.cpp
	src/cubicSpline.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(cubicSpline)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/cubicSplineTestCase.cpp
		gtest/cubicSpline_tests.cpp
	)
	addGtest(cubicSpline_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(cubicSpline_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(cubicSpline_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )