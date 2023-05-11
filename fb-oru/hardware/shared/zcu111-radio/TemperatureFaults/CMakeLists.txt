add_sources (SOURCES
	src/BoardTxUnderTemperatureFaultMajor.cpp
	src/BoardTxOverTemperatureFaultMajor.cpp
	src/BoardTxOverTemperatureFaultMinor.cpp

    src/PaUnderTemperatureFaultMajor.cpp
    src/PaOverTemperatureFaultMajor.cpp
    src/PaOverTemperatureFaultMinor.cpp

    src/UnderTempMajorFaultOwner.cpp
    src/OverTempMajorFaultOwner.cpp
    src/OverTempMinorFaultOwner.cpp

)

## Cppcheck
include (cppcheck)
addCppcheck(TemperatureFaults)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	set (libs "")
    addRepoLib(libs xcommon)
    addRepoLib(libs common)

    addRepoLib(libs hardware common)
    addRepoLib(libs hardware ${BUILD_BOARD})

    # Uses tinyxml2
    addRosLib(libs tinyxml2)

    addTestCommon(TEST_COMMON common)
    addTestCommon(HARDWARE_TEST_COMMON hardware)

    include_directories(gtest)
    set(gtest_src
        gtest/OverTempMajorFault_unittest.cpp
        gtest/OverTempMinorFault_unittest.cpp
        gtest/UnderTempMajorFault_unittest.cpp
        gtest/tests.cpp

        # Test mocks
         ${TEST_COMMON}/TestIloggerFactory.cpp
         ${TEST_COMMON}/BootEnvSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonDevices.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonAttenuator.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonSynth.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonRefClock.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonRadio.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonAttenuator.cpp        
         ${HARDWARE_TEST_COMMON}/TestCommonRadioFactories.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonRadioInfoSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonRxPortSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonSRxPortSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonTxPortSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestCalDataSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestCalData.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonCpriSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestBus.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonCarrierSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonModules.cpp
         ${HARDWARE_TEST_COMMON}/TestRadioPostInit.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonCarrierServer.cpp
         ${HARDWARE_TEST_COMMON}/TestCommonCarrierServerSingleton.cpp
    )
    addGtest(TemperatureFaults_GTEST "${libs}" ${gtest_src})

    # Add code coverage
    include (coverage)
    addCoverage(TemperatureFaults_GTEST)

    # Add memory leak check
    include (valgrind)
    addMemcheck(TemperatureFaults_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )


