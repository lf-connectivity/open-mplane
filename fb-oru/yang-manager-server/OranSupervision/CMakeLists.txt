# Cmake file for yang-manager-server/OranSupervision

add_sources (SOURCES
	src/CUPlaneMonitor.cpp
	src/CUPlaneMonitorSingleton.cpp

	src/MPlaneConnectivityService.cpp
	src/MPlaneConnectivityServiceSingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(oransupervision)

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
	    gtest/MPlaneConnectivity_unittest.cpp

	    # Test mocks
	    gtest/RadioDatastoreSysrepoMock.cpp
	    gtest/SysrepoUtilsMock.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(OranSupervision_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(OranSupervision_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(OranSupervision_GTEST)


endif (${TARGET} STREQUAL "x86_64")
