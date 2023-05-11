# Cmake file for yang-manager-server/YangConfigParser

add_sources (SOURCES
	src/YangConfigParser.cpp
	src/YangConfigDownload.cpp
	src/YangConfig.cpp
	src/YangConfigSingleton.cpp
	src/YangElement.cpp
	src/YangElementFactories.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(ConfigParser)


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
		gtest/YangConfig_unittest.cpp
		gtest/YangConfigParser_unittest.cpp

		# Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(YangConfigParser_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(YangConfigParser_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(YangConfigParser_GTEST)


endif (${TARGET} STREQUAL "x86_64")