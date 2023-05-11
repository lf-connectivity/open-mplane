# Cmake file for Val

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/SetVal_unittest.cpp
		gtest/ChangeVal_unittest.cpp
	)
	addGtest(Val_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Val_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(Val_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

