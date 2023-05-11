# Cmake file for yang-manager-server/OranFm

add_sources (SOURCES
	src/OranFm.cpp
)


if (${TARGET} STREQUAL "x86_64")

	addRepoLib(libs xcommon)
	addRepoLib(libs common)

	addRepoLib(libs hardware common)
	addRepoLib(libs hardware ${BUILD_BOARD})
	addRepoLib(libs hardware ${BUILD_BOARD}_${BUILD_APPLICATION})

	addRepoLib(libs services common)
	addRepoLib(libs services ${BUILD_BOARD})
	addRepoLib(libs services ${BUILD_APPLICATION})

	# Uses tinyxml2
	addRosLib(libs tinyxml2)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
	    gtest/tests.cpp		
	    gtest/OranFm_unittest.cpp

	    # Test mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestHardwareSettingsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaComms.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsg.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsgFactory.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsgQFactory.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaMsgTokens.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
	    ${TEST_HW_COMMON}/TestFpgaMock.cpp

	)
	addGtest(OranFm_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(OranFm_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(OranFm_GTEST)


endif (${TARGET} STREQUAL "x86_64")
