# Cmake file for common/radioConfig

add_sources (SOURCES
    src/NullRadioConfig.cpp
    src/RadioConfig.cpp
    src/RadioConfigFpgaHelper.cpp
    src/RadioConfigDevice.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(radioConfig)

if (${TARGET} STREQUAL "x86_64")

	set (libs "")

	addRepoLib (libs xcommon)
	addRepoLib (libs common)

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/RadioConfig_unittest.cpp
		gtest/TestRadioConfigFactory.cpp
		gtest/tests.cpp

		# Test mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(radioConfig_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(radioConfig_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(radioConfig_GTEST)


endif (${TARGET} STREQUAL "x86_64")

