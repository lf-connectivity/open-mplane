# Cmake file for NetStatus

add_sources (SOURCES
	src/NetStatus.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(NetStatus)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	include (coverage)
	include (valgrind)


    # Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/NetStatus_unittest.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(NetStatus_GTEST "${libs}" ${gtest_src})

	addCoverage(NetStatus_GTEST)
	addMemcheck(NetStatus_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

