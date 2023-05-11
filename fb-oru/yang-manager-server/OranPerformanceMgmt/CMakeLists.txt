# Cmake file for yang-manager-server/OranPerformanceMgmt

add_sources (SOURCES
	src/PerformanceMgmtService.cpp
	src/TransceiverMeasurement.cpp
	src/PerformanceMgmtSingleton.cpp
	src/RxWindowMeasurement.cpp
	)

## Cppcheck
include (cppcheck)
addCppcheck(OranPerformanceMgmt)

if (${TARGET} STREQUAL "x86_64")

    addRepoLib(libs xcommon)
    addRepoLib(libs common)

    addRepoLib(libs hardware common)
    addRepoLib(libs hardware ${BUILD_BOARD})

    # Uses tinyxml2
    addRosLib(libs tinyxml2)

    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)

    # Load google test
    include (gtest)

	include_directories(gtest)
	set(gtest_src
        gtest/tests.cpp		
		gtest/PerformanceMgmt_unittest.cpp
		gtest/TestPerfMgmt.cpp

		# Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
		${TEST_HW_COMMON}/TestBus.cpp
		${TEST_HW_COMMON}/TestSfpData.cpp
		
	)
	addGtest(PerfMgmt_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(PerfMgmt_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(PerfMgmt_GTEST)


endif (${TARGET} STREQUAL "x86_64")