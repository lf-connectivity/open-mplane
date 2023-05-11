# Cmake file for ORANRRH/AppControl
message(STATUS "ORANRRH/AppControl: sysrepolibs=${sysrepolibs}")

add_sources (SOURCES
	src/OranRrhAppControl.cpp
	src/OranRrhServices.cpp
	src/OranRrhDelaysMgrSingleton.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(AppControl)

if (${TARGET} STREQUAL "x86_64")

	set (libs "")

	addRepoLib(libs common)
	addRepoLib(libs xcommon)
	addRepoLib(libs hardware common)
	addRepoLib(libs hardware ${BUILD_BOARD}_${BUILD_APPLICATION})
	addRepoLib(libs hardware ${BUILD_BOARD})
	addRepoLib(libs services common)
	
	# pcap
	addRosLib(libs pcap)


	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	addTestCommon(TEST_SC_COMMON services-common)

	include_directories(gtest)
	set(gtest_src
	    gtest/RrhServicesTestCase.cpp
	    gtest/RrhAppControlTestCase.cpp
	    gtest/RrhAppControlTestFactorys.cpp
	    gtest/RrhAppControlTests.cpp

	    ## Test Mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
	    ${TEST_HW_COMMON}/TestCommonRadio.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioInfoSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
	    ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonSRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCalDataSingleton.cpp
	    ${TEST_HW_COMMON}/TestCalData.cpp
	    ${TEST_HW_COMMON}/TestBus.cpp
	    ${TEST_HW_COMMON}/TestCommonCarrierSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonModules.cpp
	    ${TEST_HW_COMMON}/TestRadioPostInit.cpp
	    ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
	    ${TEST_SC_COMMON}/ImageManagementSingleton.cpp
	)
	
	if (FEAT_DPD2 STREQUAL "APP")
		set (gtest_src ${gtest_src}
			${TEST_HW_COMMON}/TestRemoteMsgHandlerFactory.cpp
		)
	endif()
	
	addGtest(AppControl_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(AppControl_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(AppControl_GTEST)


endif (${TARGET} STREQUAL "x86_64")

