# Cmake file for common/radio

add_sources (SOURCES
	src/CommonAdc.cpp
	src/CommonAldPort.cpp
	src/CommonAttenuator.cpp
	src/CommonCam.cpp
	src/CommonDac.cpp
	src/CommonDevices.cpp
	src/CommonFem.cpp
	src/CommonFibre.cpp
	src/CommonFilter.cpp
	src/CommonFpgaDev.cpp
	src/CommonGpioExp.cpp
	src/CommonModules.cpp
    src/CommonPa.cpp
	src/CommonPort.cpp
	src/CommonRadio.cpp
	src/CommonRadioInfo.cpp
	src/CommonRxPort.cpp
	src/CommonSRxPort.cpp
	src/CommonSynth.cpp
	src/CommonTxPort.cpp
	src/CommonRxAttenuatorsFactory.cpp
	src/CommonEqualiser.cpp
	src/CommonTxEqualiser.cpp
	src/CommonRxEqualiser.cpp
	src/CommonRefClock.cpp
	src/CommonTemperatureSensor.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(radio)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) AND (${BUILD_FIBRE_INTERFACE} STREQUAL "CPRI") )

	set (libs "")

    ## Uses tinyxml2
    addRosLib( libs  tinyxml2 )

	addRepoLib (libs xcommon)
	addRepoLib (libs common)

	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	

	include_directories(gtest)
	set(gtest_src
		gtest/CommonRxPortTestCase.cpp
#		gtest/CommonSRxPortTestCase.cpp
		gtest/RadioTests.cpp
		
		# Test mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
        ${TEST_HW_COMMON}/TestRemoteMsgHandlerFactory.cpp
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
        ${TEST_HW_COMMON}/TestBus.cpp
        ${TEST_HW_COMMON}/TestCommonCpriSingleton.cpp
        ${TEST_HW_COMMON}/TestRadioConfigFactory.cpp
	)
	addGtest(hardware_common_radio_GTEST "${libs}" ${gtest_src})

	# Load cppunit
	include (cppunit)

	include_directories(test)
	set(test_src
		test/CommonAdcTestCase.cpp
		test/CommonAttenuatorTestCase.cpp
		test/CommonCamTestCase.cpp
		test/CommonCpriSingleton.cpp
		test/CommonDacTestCase.cpp
		test/CommonDevicesTestCase.cpp
		test/CommonFemTestCase.cpp
		test/CommonFilterTestCase.cpp
		test/CommonModulesTestCase.cpp
		test/CommonPortTestCase.cpp
		test/CommonRadioTestCase.cpp
		test/CommonRadioTests.cpp
		test/CommonRxPortTestCase.cpp
		test/CommonSynthTestCase.cpp
		test/CommonTxPortTestCase.cpp
		test/TestAldPortSingleton.cpp
		
		# Test mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
        ${TEST_HW_COMMON}/TestRemoteMsgHandlerFactory.cpp
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
        ${TEST_HW_COMMON}/TestBus.cpp
        ${TEST_HW_COMMON}/TestRadioConfigFactory.cpp
	)
	addCppunitTest(radio_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(hardware_common_radio_GTEST)
	addCoverage(radio_TEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(hardware_common_radio_GTEST)
	addMemcheck(radio_TEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) AND (${BUILD_FIBRE_INTERFACE} STREQUAL "CPRI") )

