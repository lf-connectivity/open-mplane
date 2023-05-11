# Cmake file for TifIoctl

add_sources (SOURCES
	src/tifioctl-dummy.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(TifIoctl)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/TifIoctl_unittest.cpp
		gtest/TifIoctlTests.cpp
	)
	addGtest(TifIoctl_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(TifIoctl_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(TifIoctl_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

