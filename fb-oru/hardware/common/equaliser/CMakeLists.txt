# Cmake file for hardware/common/equaliser

add_sources (SOURCES
	src/RxEqualiser.cpp
	src/TxEqualiser.cpp
)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)

    ## Uses tinyxml2
    addRosLib(libs tinyxml2)

	addTestCommon(TEST_HW_COMMON hardware)
	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/TestRxEqualiserTestCase.cpp
		gtest/TestTxEqualiserTestCase.cpp
		gtest/EqTests.cpp

		# Test Mock
		${TEST_HW_COMMON}/TestCalDataSingleton.cpp
		${TEST_HW_COMMON}/TestCalData.cpp
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
	    ${TEST_HW_COMMON}/TestCommonModules.cpp
	    ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
	    ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
	    ${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
	    ${TEST_HW_COMMON}/TestFpgaMock.cpp
	    ${TEST_HW_COMMON}/TestCommonDevices.cpp
	    ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
	    ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
	    ${TEST_HW_COMMON}/TestAttenuatorDriver.cpp
	    ${TEST_HW_COMMON}/TestCommonRadio.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioInfoSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
	    ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonSRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRadioConfigFactory.cpp

	)
	addGtest(Equaliser_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Equaliser_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(Equaliser_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
