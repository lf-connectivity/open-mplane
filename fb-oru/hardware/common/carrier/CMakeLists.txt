# Cmake file for common/carrier

add_sources (SOURCES
	src/CommonCarrier.cpp
	src/CommonCarrierFail.cpp
	src/CommonCarrierHardware.cpp
	src/CommonCarrierModel.cpp
	src/CommonCarrierModelListWorker.cpp
	src/CommonCarrierModelWorker.cpp
	src/CommonCarrierServer.cpp
	src/CarrierBundle.cpp
	src/CarrierBundleList.cpp
	src/CarrierFreqMgr.cpp
	src/CarrierFreqMgr/CarrierFreq.cpp
	src/CarrierFreqMgr/CarrierFreqBand.cpp
	src/CarrierPowerMgr/CarrierPowerPath.cpp
	src/CarrierPowerMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(carrier)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

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
		gtest/CarrierFunctional_unittest.cpp
		gtest/CommonCarrierServer_fixture.cpp
		gtest/CommonCarrierServer_unittest.cpp
		gtest/CommonCarrierHardware_unittest.cpp
		gtest/CarrierFreq_unittest.cpp
		gtest/CarrierFreqBand_unittest.cpp
		gtest/CommonCarrierTests.cpp
		gtest/TestCommonAppSettingsSingleton.cpp

        # Test Mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
	    ${TEST_HW_COMMON}/TestCommonDevices.cpp
	    ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
	    ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
	    ${TEST_HW_COMMON}/TestCam.cpp
        ${TEST_HW_COMMON}/TestCamFactory.cpp
        ${TEST_HW_COMMON}/TestCommonRadio.cpp
        ${TEST_HW_COMMON}/TestCommonRadioInfoSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
        ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonSRxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCalDataSingleton.cpp
        ${TEST_HW_COMMON}/TestCalData.cpp
        ${TEST_HW_COMMON}/TestCommonCpriSingleton.cpp
        ${TEST_HW_COMMON}/TestBus.cpp
        ${TEST_HW_COMMON}/TestCommonModules.cpp
        ${TEST_HW_COMMON}/TestRadioPostInit.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestICarrierHardwareSingleton.cpp
        ${TEST_HW_COMMON}/TestICarrierHardware.cpp
	)
	addGtest(carrier_GTEST "${libs}" ${gtest_src})

	# Load cppunit
	include (cppunit)

	include_directories(test)
	set(test_src
		test/CarrierTests.cpp
		test/CommonCarrierFailTestCase.cpp
		test/CommonCarrierHardwareListTestCase.cpp
		test/CommonCarrierHardwareTestCase.cpp
		test/CommonCarrierModelTestCase.cpp
		test/CommonCarrierServerTestCase.cpp
		test/CommonCarrierTestCase.cpp
		gtest/TestCommonAppSettingsSingleton.cpp

        # Test Mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
	    ${TEST_HW_COMMON}/TestCommonDevices.cpp
	    ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
	    ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
	    ${TEST_HW_COMMON}/TestCam.cpp
        ${TEST_HW_COMMON}/TestCamFactory.cpp
        ${TEST_HW_COMMON}/TestCommonRadio.cpp
        ${TEST_HW_COMMON}/TestCommonRadioInfoSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
        ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonSRxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCalDataSingleton.cpp
        ${TEST_HW_COMMON}/TestCalData.cpp
        ${TEST_HW_COMMON}/TestBus.cpp
        ${TEST_HW_COMMON}/TestCommonCpriSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonModules.cpp
        ${TEST_HW_COMMON}/TestRadioPostInit.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp

	)
#SDP#	addCppunitTest(carrier_TEST "${libs}" ${test_src})


	# Add code coverage
	include (coverage)
#SDP#	addCoverage(carrier_GTEST)
#SDP#	addCoverage(carrier_TEST)

	# Add memory leak check
	include (valgrind)
#SDP#	addMemcheck(carrier_GTEST)
#SDP#	addMemcheck(carrier_TEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

