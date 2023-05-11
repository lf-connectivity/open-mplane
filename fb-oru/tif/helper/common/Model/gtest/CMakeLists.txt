if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "common")
	addRepoLib(libs xcommon)

    set (TEST_TIF_DIR test-interfaces/Helper/Model)
    include_directories(${TEST_TIF_DIR}/inc)
message(STATUS "TEST_TIF_DIR: ${TEST_TIF_DIR}/inc")
    set (TEST_TIF_SRC
        ${TEST_TIF_DIR}/src/HelperLedTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperArbTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperAlarmsTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperCpriTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperTenMHzRefTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperI2CTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperArbCaptureTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperImagesOsTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperPimTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperBistTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperSystemTcpTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperSystemTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperCalTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperTestInterface.cpp
        ${TEST_TIF_DIR}/src/HelperImagesFpgaTestHandler.cpp
#        ${TEST_TIF_DIR}/src/HelperDpdTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperImagesLibTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperArbRfTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperArbCpriTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperImagesTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperDevicesRxadcTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperFpgaTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperArbPlaybackTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperCarrierTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperImagesAppTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperSPITestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperSystemLoggingTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperPaTestHandler.cpp
        ${TEST_TIF_DIR}/src/HelperFreqConstTestHandler.cpp

    )

	addRepoLib(libs hardware common)
	addRepoLib(libs swtools shared)
	addRepoLib(libs tif-common)

    # Need to link against this library
	list (APPEND libs tifHelperCommon)

	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	addTestCommon(TEST_SERVICES_COMMON services)
	addTestCommon(TEST_TIF_COMMON tif)

	addShared(TIF_SHARED tif)

	include_directories(gtest)
	set(gtest_src
		tests.cpp
		model_fixture.cpp
		alarms_unittest.cpp
		arb_unittest.cpp

        imagesfpga_unittest.cpp
        fpga_unittest.cpp
        devicesrxadc_unittest.cpp
        imagesapp_unittest.cpp
        led_unittest.cpp
        caltx_unittest.cpp
        calrx_unittest.cpp
        tenmhzref_unittest.cpp
        imageslib_unittest.cpp
        systemtcp_unittest.cpp
        pim_unittest.cpp
        i2c_unittest.cpp
        cal_unittest.cpp
        systemlogging_unittest.cpp
        pa_unittest.cpp
        freqconst_unittest.cpp

        TestMemMonSingleton.cpp


		${TEST_TIF_SRC}

    	# Test mocks
	    ${TEST_COMMON}/TestImageManagement.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
	    ${TEST_HW_COMMON}/TestCommonFpga.cpp
	    ${TEST_HW_COMMON}/TestSystemClockInput.cpp
	    ${TEST_HW_COMMON}/TestSystemClockInputSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaMsgTokens.cpp
	    ${TEST_HW_COMMON}/TestFpgaComms.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsg.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsgFactory.cpp
	    ${TEST_HW_COMMON}/TestICarrierModel.cpp
	    ${TEST_HW_COMMON}/TestICarrierModelSingleton.cpp
	    ${TEST_HW_COMMON}/TestCam.cpp
        ${TEST_HW_COMMON}/TestCamFactory.cpp
        ${TEST_HW_COMMON}/TestILed.cpp
        ${TEST_HW_COMMON}/TestILed.cpp
        ${TEST_HW_COMMON}/TestILedSingleton.cpp
	    ${TEST_TIF_COMMON}/TestLimitsSettings.cpp
        ${TEST_TIF_COMMON}/TestIFrequencyConst.cpp
        ${TEST_TIF_COMMON}/TestIFrequencyConstSingleton.cpp
        ${TEST_TIF_COMMON}/TestTxPclFactory.cpp
        ${TEST_TIF_COMMON}/TestVswrFactory.cpp
	)
	addGtestNolib(helperCommonModel_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(helperCommonModel_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(helperCommonModel_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

