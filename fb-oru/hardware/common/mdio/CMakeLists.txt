# Cmake file for common/mii

add_sources (SOURCES
	src/Mdio.cpp
	src/MdioFactory.cpp
)




## Cppcheck
include (cppcheck)
addCppcheck(mdio)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")
    addRepoLib(libs xcommon)
    addRepoLib(libs common)

    # Load google test
    include (gtest)
	
	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	
	include_directories(gtest)
	set(gtest_src
		gtest/MdioTestCase.cpp
		gtest/Tests.cpp


        # Test Mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
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
        ${TEST_HW_COMMON}/TestCommonCarrierSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonModules.cpp
        ${TEST_HW_COMMON}/TestRadioPostInit.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
	)
    addGtest(mdio_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(mdio_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(mdio_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

