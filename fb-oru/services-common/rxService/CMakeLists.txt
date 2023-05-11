# Cmake file for common/rxService

add_sources (SOURCES
	src/RxService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(rxService)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)
	addRepoLib (libs hardware common)

	# Load cppunit
	include (cppunit)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	addTestCommon(TEST_SC_COMMON services-common)

	include_directories(test)
	set(test_src
		test/RxServiceTestCase.cpp
		test/RxServiceTests.cpp

		# Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_HW_COMMON}/TestFpgaKernel.cpp
		${TEST_HW_COMMON}/TestFpgaMock.cpp
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
        ${TEST_HW_COMMON}/TestCommonCarrierSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonModules.cpp
        ${TEST_HW_COMMON}/TestRadioPostInit.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
		${TEST_HW_COMMON}/TestCommonDevices.cpp
		${TEST_HW_COMMON}/TestCommonAttenuator.cpp
		${TEST_HW_COMMON}/TestCommonSynth.cpp
		${TEST_HW_COMMON}/TestCommonRefClock.cpp
		${TEST_HW_COMMON}/TestCommonFaults.cpp
		${TEST_HW_COMMON}/TestCommonFaultsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaMsgTokens.cpp
	    ${TEST_HW_COMMON}/TestFpgaComms.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsg.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsgFactory.cpp
	    ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
	    ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
		${TEST_SC_COMMON}/TestICpriController.cpp
		${TEST_SC_COMMON}/TestICpriControllerSingleton.cpp
		${TEST_SC_COMMON}/TestICpriPortHandler.cpp
		${TEST_HW_COMMON}/TestDpdControlSingleton.cpp
		${TEST_SC_COMMON}/NetStatusFactory.cpp
		${TEST_SC_COMMON}/ImageManagementSingleton.cpp
	)
	addCppunitTest(rxService_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(rxService_TEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(rxService_TEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

