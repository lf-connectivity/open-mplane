# Cmake file for services/shared/Alarms

add_sources (SOURCES
             src/RrhAlarms.cpp
             src/RrhAlarmsSingleton.cpp

             src/Cpri0MajorAlarm.cpp
             src/PllMajorAlarm.cpp
             src/RadioTempMajorAlarm.cpp
             src/RadioTempMinorAlarm.cpp
             src/RxMajorAlarm.cpp
             src/PaTempMajorAlarm.cpp
             src/PaTempMinorAlarm.cpp
             src/Cpri0MajorAlarm.cpp
             src/VswrTxAlarm.cpp
             src/TxShutdownAlarm.cpp
             src/TxDegradedAlarm.cpp
             src/TxBbIqAlarm.cpp
             src/HeartBeatAlarm.cpp
             src/TxDpdMinorAlarm.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Alarms)

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
	    gtest/Alarms_unittest.cpp
	    gtest/tests.cpp

	    ## Test Mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(RrhAlarms_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(RrhAlarms_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(RrhAlarms_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
