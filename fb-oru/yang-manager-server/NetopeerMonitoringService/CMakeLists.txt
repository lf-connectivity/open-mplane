# Cmake file for yang-manager-server/NetopeerMonitoringService

add_sources (SOURCES
	src/NetopeerMonService.cpp
	src/NetopeerMonServiceSingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(NetopeerMonitoringService)

if (${TARGET} STREQUAL "x86_64")

	addRepoLib(libs xcommon)
	addRepoLib(libs common)

	addRepoLib(libs hardware common)
	addRepoLib(libs hardware ${BUILD_BOARD})

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
	    gtest/tests.cpp		
	    gtest/NetopeerMonService_unittest.cpp

	    # Test mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(NetopeerMonitoringService_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(NetopeerMonitoringService_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(NetopeerMonitoringService_GTEST)


endif (${TARGET} STREQUAL "x86_64")