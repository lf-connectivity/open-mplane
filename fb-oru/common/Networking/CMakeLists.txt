# Cmake file for Networking

add_sources (SOURCES
	src/IpPortMgr.cpp
	src/NetAddr.cpp
	src/NetAddrMac.cpp
	src/NetAddrStatic.cpp
	src/NetAddrLinkLocal.cpp
	src/NetAddrDhcp.cpp
	src/NetAddrPolicy.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Networking)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	include (coverage)
	include (valgrind)


    # Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/Networking_unittest.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(Networking_GTEST "${libs}" ${gtest_src})


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

