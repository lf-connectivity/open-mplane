# Cmake file for md5

add_sources (SOURCES
	src/md5.cpp
	src/Md5Sum.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(md5)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/md5_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(md5_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(md5_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(md5_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

