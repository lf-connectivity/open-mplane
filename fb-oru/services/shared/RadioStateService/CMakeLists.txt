# Cmake file for Felix/RadioStateService


add_sources (SOURCES
	src/RadioStateService.cpp
	src/RadioStateFactory.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RadioStateService)


# Test code only runs on ECB_FELIX builds
if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_APPLICATION} STREQUAL "RRH") )

    set (libs "")

	#addRepoLib(libs services vsi test)
	#addRepoLib(libs hardware vhi test)
    addRepoLib(libs xcommon)
    addRepoLib(libs common)
    addRepoLib(libs hardware common)
    addRepoLib(libs services common)
	addRepoLib(libs hardware ${BUILD_BOARD})
	addRepoLib(libs hardware ${BUILD_BOARD}_${BUILD_APPLICATION})

    addTestCommon(TEST_COMMON common)
	addTestCommon(SERVICES_TEST_COMMON services)
	addTestCommon(TEST_HW_COMMON hardware)
	
	# Uses tinyxml2
    addRosLib(libs tinyxml2)

	# Load google test
	include (gtest)

	include_directories(gtest)

	set(gtest_src
		gtest/RadioStateServiceTests.cpp
		gtest/TestImageManagement.cpp
		gtest/CarrierServer_fixture.cpp
        gtest/CarrierServerSingleton.cpp
        gtest/TestICpriSingleton.cpp

		## Stubs to allow the tests to compile and link.

	     ${SERVICES_TEST_COMMON}/TestTxPclFactory.cpp
	     ${SERVICES_TEST_COMMON}/TestVswrFactory.cpp
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

	addGtest(RadioStateService_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(RadioStateService_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(RadioStateService_GTEST)

endif ()
