add_sources (SOURCES
    src/TxUnderPowerFaultMinor.cpp
    src/TxOverPowerFaultMajor.cpp
    src/TxOverPowerFaultMinor.cpp
    src/TxPowerMeasurementFaultMajor.cpp

    src/TxUnderPowerMinorFaultOwner.cpp
    src/TxOverPowerMajorFaultOwner.cpp
    src/TxOverPowerMinorFaultOwner.cpp


)


## Cppcheck
include (cppcheck)
addCppcheck(PowerFaults)

## Tests
if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) AND (${BUILD_APPLICATION} STREQUAL "RRH") )

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
    addTestCommon(TEST_HW_COMMON hardware)

    include_directories(gtest)
    set(gtest_src
        gtest/TxOverPowerMajorFault_unittest.cpp
        gtest/TxOverPowerMinorFault_unittest.cpp
        gtest/TxUnderPowerMinorFault_unittest.cpp
        gtest/CarrierServer_fixture.cpp
        gtest/CarrierServerSingleton.cpp
        gtest/TestICpriSingleton.cpp
        gtest/tests.cpp

        # Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
	    ${TEST_HW_COMMON}/TestCommonDevices.cpp
	    ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
	    ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
	    ${TEST_HW_COMMON}/TestCommonRadio.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioInfoSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonModules.cpp
	    ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonSRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
    	${TEST_HW_COMMON}/TestZcu111CarrierModelSingleton.cpp
    	${TEST_HW_COMMON}/TestZcu111CarrierHardwareListSingleton.cpp
    	${TEST_HW_COMMON}/TestZcu111CarrierHardwareDataSingleton.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/FpgaRegCapture_fixture.cpp
	    ${TEST_HW_COMMON}/TestCommonRxAgc.cpp
	    ${TEST_HW_COMMON}/TestCommonRxAgcSingleton.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
        ${TEST_HW_COMMON}/TestICpri.cpp
        ${TEST_HW_COMMON}/TestICpriCore.cpp
        ${TEST_HW_COMMON}/TestIFibre.cpp
    )
    addGtest(PowerFaults_GTEST "${libs}" ${gtest_src})

    # Add code coverage
    include (coverage)
    addCoverage(PowerFaults_GTEST)

    # Add memory leak check
    include (valgrind)
    addMemcheck(PowerFaults_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) AND (${BUILD_APPLICATION} STREQUAL "RRH") )