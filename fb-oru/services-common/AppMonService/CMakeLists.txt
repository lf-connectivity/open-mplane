# Cmake file for common/AppMonService

add_sources (SOURCES
    src/AppMonService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(AppMonService)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	addRepoLib(libs xcommon)
	addRepoLib(libs common)

	addRepoLib(libs hardware common)
	addRepoLib(libs hardware ${BUILD_BOARD})

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
	    gtest/tests.cpp
	    gtest/TestAppMonService_unittest.cpp
	    gtest/TestAppMonServiceSingleton.cpp
	    gtest/TestAppMonService.cpp

	    # Test mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(TestAppMonService_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(TestAppMonService_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(TestAppMonService_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
