# Cmake file for socket

add_sources (SOURCES
	src/Socket.cpp
	src/MulticastSocket.cpp
	src/SocketClient.cpp
	src/SocketHandler.cpp
	src/SocketServer.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(socket)

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
		gtest/MulticastSocket_unittest.cpp
	)
	addGtest(socket_GTEST "${libs}" ${gtest_src})

	addCoverage(socket_GTEST)
	addMemcheck(socket_GTEST)


	# Load cppunit
	include (cppunit)

	include_directories(test)
	set(test_src
		test/SocketsTestCase.cpp
		test/SocketsTests.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addCppunitTest(socket_TEST "${libs}" ${test_src})

	# Add code coverage
	addCoverage(socket_TEST)
	# Add memory leak check
	addMemcheck(socket_TEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

