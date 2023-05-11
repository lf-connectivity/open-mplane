# Cmake file for fft



## Cppcheck
include (cppcheck)
addCppcheck(fft)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/fft_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(fft_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(fft_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(fft_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )