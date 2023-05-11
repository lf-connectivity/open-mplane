# Cmake file for SSDP

add_sources (SOURCES
	src/SsdpReceiver.cpp
	src/SsdpSender.cpp
	src/Ssdp.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Ssdp)

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
		gtest/SSDP_unittest.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
#	addGtest(Ssdp_GTEST "${libs}" ${gtest_src})

#	addCoverage(Ssdp_GTEST)
#	addMemcheck(Ssdp_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

