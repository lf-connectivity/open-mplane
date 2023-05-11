# Cmake file for FileMgr

add_sources (SOURCES
	src/FileMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FileMgr)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/FileMgr_unittest.cpp
		gtest/tests.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(FileMgr_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FileMgr_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(FileMgr_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

