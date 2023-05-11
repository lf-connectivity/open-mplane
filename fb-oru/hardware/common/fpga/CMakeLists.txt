# Cmake file for common/fpga

add_sources (SOURCES
	src/FpgaCpri.cpp
	src/FpgaMgr.cpp
#SDP#	src/FpgaMonitor.cpp
)

if (${TARGET} STREQUAL "x86_64")

    add_sources (SOURCES
    	src/OffTargetFPGA.cpp
    )

endif ()

## Cppcheck
include (cppcheck)
addCppcheck(fpga)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    addRepoLib(libs xcommon)
    addRepoLib(libs common)
    
    ## Uses tinyxml2
    addRosLib( libs  tinyxml2 )

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/FpgaMonitor_unittest.cpp
		gtest/tests.cpp


		# Test mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
	    ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestCommonDevices.cpp
        ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
        ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
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
        ${TEST_HW_COMMON}/TestCommonCarrierSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonModules.cpp
        ${TEST_HW_COMMON}/TestRadioPostInit.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
	)
##	addGtest(fpga_GTEST "${libs}" ${gtest_src})
	
	# Load cppunit
	include (cppunit)

	set(test_src
		test/CommonFPGATests.cpp
		test/OffTargetFPGATestCase.cpp
		
		# Test mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
	    ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
        ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestCommonDevices.cpp
        ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
        ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
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
        ${TEST_HW_COMMON}/TestCommonCarrierSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonModules.cpp
        ${TEST_HW_COMMON}/TestRadioPostInit.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
	)
##	addCppunitTest(fpga_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
##	addCoverage(fpga_TEST)
##	addCoverage(fpga_GTEST)

	# Add memory leak check
	include (valgrind)
##	addMemcheck(fpga_TEST)
##	addMemcheck(fpga_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

