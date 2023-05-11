# Cmake file for device

add_sources (SOURCES
	src/Device.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(device)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Device_unittest.cpp
		gtest/DeviceTests.cpp
	)
	addGtest(Device_GTEST "" ${gtest_src})


	# Add code coverage
	include (coverage)
	addCoverage(Device_GTEST)
	
	# Add memory leak check
	include (valgrind)
	addMemcheck(Device_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

