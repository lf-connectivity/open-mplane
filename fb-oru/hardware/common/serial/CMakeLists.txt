# Cmake file for common/serial

add_sources (SOURCES
	src/SerialData.cpp
	src/SerialDriver.cpp
	src/AisgSerialDriver.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(serial)

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
		gtest/SerialDriver_unittest.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_HW_COMMON}/AisgDriverSingleton.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp

	)
	addGtest(serial_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(serial_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(serial_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )