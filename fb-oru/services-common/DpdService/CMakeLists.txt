# Cmake file for common/DpdService

add_sources (SOURCES
	src/DpdService.cpp
	src/DpdControlBase.cpp
	src/DpdControlTx.cpp
	src/DpdPapr.cpp
	src/data/DpdData.cpp
	src/data/DpdAlarm.cpp
	src/data/DpdInfo.cpp
	src/data/DpdPowerMeasure.cpp
	src/data/DpdTxpower.cpp
	src/data/DpdVswr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(DpdService)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs xcommon)
	addRepoLib (libs common)
	addRepoLib (libs hardware common)

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)


	include_directories(gtest)
	set(gtest_src
		gtest/data/TestDpdAlarm.cpp
		gtest/data/TestDpdVswr.cpp
		gtest/tests.cpp
		gtest/TestDpdComms.cpp
		gtest/TestDpdCommsSingleton.cpp
		gtest/TestMsgFactory.cpp
		gtest/TestTokens.cpp
		gtest/DpdService_unittest.cpp
		
				## Test Mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
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
	)
#SDP#	addGtest(DpdService_GTEST "${libs}" ${gtest_src})


	# Add code coverage
	include (coverage)
#SDP#	addCoverage(DpdService_GTEST)

	# Add memory leak check
	include (valgrind)
#SDP#	addMemcheck(DpdService_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

