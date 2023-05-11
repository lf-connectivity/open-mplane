
add_sources (SOURCES
	src/Zcu111RrhSRxPort.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Zcu111rrhorxPort)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")
    
    ## Uses tinyxml2
    addRosLib( libs  tinyxml2 )

	addRepoLib(libs common)
	addRepoLib(libs xcommon)
	
	addRepoLib (libs hardware common)
	addRepoLib (libs hardware ${BUILD_BOARD})

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Zcu111ORxPortTestCase.cpp
		gtest/Zcu111ORxPortSingleton.cpp
		gtest/tests.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_HW_COMMON}/TestFpgaMock.cpp
		${TEST_HW_COMMON}/TestFpgaKernel.cpp
		${TEST_HW_COMMON}/TestCommonRxAgc.cpp
		${TEST_HW_COMMON}/TestCommonRxAgcSingleton.cpp
		${TEST_HW_COMMON}/TestRfBandConfig.cpp
		${TEST_HW_COMMON}/TestResamplerConfig.cpp
		${TEST_HW_COMMON}/TestRemoteMsgHandlerFactory.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
	    ${TEST_HW_COMMON}/TestCommonModules.cpp
	    ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
	    ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
	    ${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
		${TEST_HW_COMMON}/TestCommonDevices.cpp
	    ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
	    ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
	    ${TEST_HW_COMMON}/TestAttenuatorDriver.cpp
	    ${TEST_HW_COMMON}/TestCommonRadio.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioInfoSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
	    ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
	)
	addGtest(orxPort_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(orxPort_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(orxPort_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
