# Cmake file for common/TxService

add_sources (SOURCES
    src/VswrMon.cpp
    src/VswrMonFactory.cpp
	src/TxPowerControl.cpp
    src/TxPowerControlFactory.cpp
	src/TxService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(TxService)

if (${TARGET} STREQUAL "x86_64" )
	set (libs "")

	## Uses tinyxml2
    addRosLib(libs tinyxml2)

	addRepoLib (libs xcommon)
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
		gtest/TxPowerControl_unittest.cpp
		gtest/TxServicesTests.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp

	    ${TEST_HW_COMMON}/TestFpgaMsgTokens.cpp
	    ${TEST_HW_COMMON}/TestFpgaComms.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsg.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsgFactory.cpp
	)
	addGtest(TxService_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(TxService_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(TxService_GTEST)

endif ()

