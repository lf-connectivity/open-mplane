# Cmake file for common/FibreControlService

add_sources (SOURCES
	src/CpriController.cpp
	src/CpriPortHandling.cpp
	src/FibreControlService.cpp
	src/ICpriOAM.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FibreControlService)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	
	## Uses tinyxml2
    addRosLib(libs tinyxml2)
	
	addRepoLib (libs xcommon)
	addRepoLib (libs common)
	addRepoLib (libs hardware common)
	
    addRepoLib(libs hardware ${BUILD_BOARD})
    addRepoLib(libs hardware ${BUILD_BOARD}_${BUILD_APPLICATION})

	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/FibreControlServiceTests.cpp
		
		# Test mocks
		${TEST_HW_COMMON}/TestBus.cpp
	    ${TEST_HW_COMMON}/TestCommonCpriSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaMock.cpp
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
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
#	addGtest(FibreControlService_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	#addCoverage(FibreControlService_GTEST)

	# Add memory leak check
	include (valgrind)
	#addMemcheck(FibreControlService_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

