# Cmake file for yang-manager-server/OranAlarms

add_sources (SOURCES
	src/OranAlarms.cpp
	src/OranAlarmsSingleton.cpp

	src/CUPlaneConnectivityMajorAlarm.cpp
	src/CUPlaneConnectivityMinorAlarm.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(OranAlarms)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	set (libs "")
	addRepoLib(libs xcommon)
	addRepoLib(libs common)
	addRepoLib(libs hardware common)
	addRepoLib(libs hardware ${BUILD_BOARD}_${BUILD_APPLICATION})
	addRepoLib(libs hardware ${BUILD_BOARD})
	addRepoLib(libs services common)

	addTestCommon(TEST_COMMON common)
	addTestCommon(HARDWARE_TEST_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
	    gtest/OranAlarms_unittest.cpp
	    gtest/tests.cpp

	    # Test Mock
	    ${TEST_COMMON}/TestIloggerFactory.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(OranAlarms_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(OranAlarms_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(OranAlarms_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
