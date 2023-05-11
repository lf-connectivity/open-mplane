add_sources (SOURCES

    src/RxPllLockFaultMajor.cpp
    src/TxPllLockFaultMajor.cpp
    src/DpdPllLockFaultMajor.cpp
    src/RefPllLockFaultMajor.cpp
    
    src/PclTxConvergenceFaultMajor.cpp
    src/PclTxOverPowerFaultMajor.cpp
    src/PopTripTxFaultMajor.cpp
    src/SrlTxFaultMajor.cpp
    src/VswrTxFaultMajor.cpp
    src/DpdTxFaultMajor.cpp
    src/DpdTxFaultMinor.cpp
    src/HeartBeatFaultMajor.cpp

    src/DpdPllLockMajorFaultOwner.cpp
    src/PopTripMajorFaultOwner.cpp
    src/SrlMajorFaultOwner.cpp
    src/HeartBeatFaultOwner.cpp
    src/RxPllLockMajorFaultOwner.cpp
    src/TxPllLockMajorFaultOwner.cpp
    src/DpdPllLockMajorFaultOwner.cpp
    src/RefPllLockMajorFaultOwner.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(OtherFaults)

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
        gtest/RxPllLockMajorFault_unittest.cpp
        gtest/RefPllLockMajorFault_unittest.cpp
        gtest/TxPllLockMajorFault_unittest.cpp
        gtest/DpdPllLockMajorFault_unittest.cpp
        gtest/PopTripMajorFault_unittest.cpp
        gtest/SrlTxMajorFault_unittest.cpp
        gtest/HeartbeatFault_unittest.cpp
        gtest/tests.cpp

        # Test mocks
         ${TEST_COMMON}/TestIloggerFactory.cpp
         ${TEST_COMMON}/BootEnvSingleton.cpp
         ${HARDWARE_TEST_COMMON}/TestFpgaKernel.cpp
         ${HARDWARE_TEST_COMMON}/TestFpgaMock.cpp
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
    addGtest(OtherFaults_GTEST "${libs}" ${gtest_src})

    # Add code coverage
    include (coverage)
    addCoverage(OtherFaults_GTEST)

    # Add memory leak check
    include (valgrind)
    addMemcheck(OtherFaults_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

