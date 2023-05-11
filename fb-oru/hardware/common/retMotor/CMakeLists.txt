# Cmake file for common/retMotor

add_sources (SOURCES
	src/RetMotorControl.cpp
	src/RetMotorComm.cpp
	src/RetMotorControlFactory.cpp
	src/AisgCommand.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(retMotor)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)

    ## Uses tinyxml2
    addRosLib(libs tinyxml2)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/RetMotor_unittest.cpp

		# Test Mock
		${TEST_HW_COMMON}/TestAisgSerialDriver.cpp
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp

	)
	addGtest(retMotor_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(retMotor_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(retMotor_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )