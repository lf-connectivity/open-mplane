# Cmake file for NetDevice

add_sources (SOURCES
	src/NetDevice.cpp
	src/NetVlanDevice.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(NetDevice)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	addTestCommon(TEST_COMMON common)

	include (coverage)
	include (valgrind)


	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/NetDevice_unittest.cpp
	)
	addGtest(NetDevice_GTEST "" ${gtest_src})

	addCoverage(NetDevice_GTEST)
	addMemcheck(NetDevice_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

