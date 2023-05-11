# Cmake file for yang-manager-server/OranDelays

add_sources (SOURCES
	src/OranDelays.cpp
	src/OranDelaysSingleton.cpp

)

## Cppcheck
include (cppcheck)
addCppcheck(oranDelays)

if (${TARGET} STREQUAL "x86_64")

    addRepoLib(libs xcommon)
    addRepoLib(libs common)

    addRepoLib(libs hardware common)
    addRepoLib(libs hardware ${BUILD_BOARD})

    # Uses tinyxml2
    addRosLib(libs tinyxml2)

    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)

    # Load google test
    include (gtest)

	include_directories(gtest)
	set(gtest_src
        gtest/tests.cpp		
		gtest/OranDelays_unittest.cpp

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
	addGtest(oranDelays_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(oranDelays_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(oranDelays_GTEST)


endif (${TARGET} STREQUAL "x86_64")