# Cmake file for common/DelaysMgr

add_sources (SOURCES
	src/DelaysMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(DelaysMgr)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/DelaysMgr_unittest.cpp
		gtest/tests.cpp

		# Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(DelaysMgr_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(DelaysMgr_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(DelaysMgr_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

