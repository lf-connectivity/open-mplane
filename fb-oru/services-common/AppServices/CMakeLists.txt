# Cmake file for common/AppServices

add_sources (SOURCES
	src/AppServices.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(AppServices)

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
	addTestCommon(TEST_SERVICES_COMMON services-common)

	include_directories(gtest)
	set(gtest_src
		gtest/AppServices_unittest.cpp
		gtest/tests.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp

	    ${TEST_HW_COMMON}/TestFpgaMsgTokens.cpp
	    ${TEST_HW_COMMON}/TestFpgaComms.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsg.cpp
	    ${TEST_HW_COMMON}/TestFpgaCommsMsgFactory.cpp

	    ${TEST_SERVICES_COMMON}/TestServicesFactory.cpp
	)
	addGtest(AppServices_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(AppServices_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(AppServices_GTEST)

endif ()

