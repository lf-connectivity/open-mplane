# Cmake file for common/Model

add_sources (SOURCES
    src/CommonModelI2cTestHandler.cpp
    src/CommonModelImagesOsTestHandler.cpp
    src/CommonModelImagesLibTestHandler.cpp
    src/CommonModelSystemTcpTestHandler.cpp
    src/CommonModelImagesFpgaTestHandler.cpp
    src/CommonModelSystemTestHandler.cpp
    src/CommonModelImagesTestHandler.cpp
    src/CommonModelSystemLoggingTestHandler.cpp
    src/CommonModelSystemBootTestHandler.cpp
    src/CommonModelSystemMemTestHandler.cpp
    src/CommonModelImagesAppTestHandler.cpp
    src/CommonModelAlarmsTestHandler.cpp
    src/CommonModelCalTestHandler.cpp
#    src/CommonModelCpriTestHandler.cpp
    src/TestInterface.cpp
)





## Cppcheck
include (cppcheck)
addCppcheck(Model)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "common")
	addRepoLib(libs xcommon)

    # common hardware
	addRepoLib(libs hardware common)

    # use helper lib
	addRepoLib(libs swtools shared)
	addRepoLib(libs tif-common)
	addRepoLib(libs tif helper/common)

	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	addTestCommon(TEST_TIF_COMMON tif)
	addTestCommon(TEST_SERVICES_COMMON services)

	addShared(TIF_SHARED tif)

	include_directories(gtest)
	set(gtest_src
		gtest/cal_unittest.cpp
#		gtest/cpri_unittest.cpp
		gtest/i2c_unittest.cpp
		gtest/images_unittest.cpp
		gtest/system_unittest.cpp
		gtest/cal_unittest.cpp
		gtest/tcp_unittest.cpp
		gtest/tif_unittest.cpp
		gtest/tests.cpp
		gtest/model_fixture.cpp

		# Test mocks
	    ${TEST_COMMON}/TestImageManagement.cpp
	    ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
	    ${TEST_HW_COMMON}/TestCommonFpga.cpp
	    ${TEST_HW_COMMON}/TestIRefFactory.cpp
	    ${TEST_HW_COMMON}/TestCam.cpp
        ${TEST_HW_COMMON}/TestCamFactory.cpp
	    ${TEST_HW_COMMON}/TestSystemClockInput.cpp
	    ${TEST_HW_COMMON}/TestSystemClockInputSingleton.cpp
	    ${TEST_SERVICES_COMMON}/TestMemMonSingleton.cpp
	    ${TEST_TIF_COMMON}/TestIMeasRssi.cpp
	    ${TEST_TIF_COMMON}/TestIMeasRssiFactory.cpp
	    ${TEST_TIF_COMMON}/TestIMeasAdc.cpp
	    ${TEST_TIF_COMMON}/TestIMeasAdcFactory.cpp
	    ${TEST_TIF_COMMON}/TestLimitsSettings.cpp
	    ${TEST_TIF_COMMON}/TestIFrequencyConst.cpp
	    ${TEST_TIF_COMMON}/TestIFrequencyConstSingleton.cpp
	)
#SDP#	addGtest(Model_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
#SDP#	addCoverage(Model_GTEST)

	# Add memory leak check
	include (valgrind)
#SDP#	addMemcheck(Model_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

