# Cmake file for WebSocket

add_sources (SOURCES
	src/SocketProxy.cpp
	src/WebSocketPacket.cpp
	src/WebSocketServerHandler.cpp
	src/WebSocketServer.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(WebSocket)

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
#	addGtest(WebSocket_GTEST "${libs}" ${gtest_src})


#	addCoverage(WebSocket_GTEST)
#	addMemcheck(WebSocket_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

