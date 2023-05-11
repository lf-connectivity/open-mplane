# Cmake file for common/FpgaMsgTokens

add_sources (SOURCES
	src/FpgaMsgTokens.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FpgaMsgTokens)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")
    addRepoLib(libs xcommon)
    addRepoLib(libs xcommon)
    addRepoLib(libs common)
    
	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/test_fixture.cpp
		gtest/TestTokens.cpp
		gtest/FpgaMsgTokens_unittest.cpp
		
		# Test
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(FpgaMsgTokens_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FpgaMsgTokens_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(FpgaMsgTokens_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

