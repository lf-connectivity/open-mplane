# Cmake file for common/FpgaComms

add_sources (SOURCES
	src/FpgaPdu.cpp
	src/FpgaCommsFromPpc.cpp
	src/FpgaCommsToPpc.cpp
	src/FpgaComms.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FpgaComms)

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
		gtest/tests.cpp
		gtest/dpd_fixture.cpp
		gtest/FpgaCommsMsgQFactory.cpp
		gtest/FpgaPdu_unittest.cpp
		gtest/FpgaCommsFromPpc_unittest.cpp
		gtest/FpgaCommsToPpc_unittest.cpp

		# Test Mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_HW_COMMON}/TestFpgaKernel.cpp
		${TEST_HW_COMMON}/TestFpgaMock.cpp
		${TEST_HW_COMMON}/TestCommonDevices.cpp
		${TEST_HW_COMMON}/TestCommonAttenuator.cpp
		${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
		${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
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
#SDP#	addGtest(FpgaComms_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
#SDP#	addCoverage(FpgaComms_GTEST)

	# Add memory leak check
	include (valgrind)

	# Skip memory leak check because these tests time out under valgrind
	##addMemcheck(FpgaComms_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

