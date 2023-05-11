# Cmake file for common/systemled

add_sources (SOURCES
	src/SystemLed.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(systemled)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/SystemLedTestCase.cpp
		gtest/SystemLedTests.cpp

		# Mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(systemled_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(systemled_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(systemled_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

