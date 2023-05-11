# Cmake file for common/FpgaCommsMsg

add_sources (SOURCES
	src/FpgaCommsMsgFactory.cpp
	src/FpgaCommsMsgBase.cpp
	src/FpgaCommsMsgCmd.cpp
	src/FpgaCommsMsgEvent.cpp
	src/FpgaCommsMsgLog.cpp
	src/FpgaCommsMsgMatlab.cpp
	src/FpgaCommsMsgReply.cpp
	src/FpgaCommsMsgText.cpp
	src/FpgaCommsMsgMonitor.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FpgaCommsMsg)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")
    addRepoLib(libs xcommon)
    addRepoLib(libs xcommon)
    addRepoLib(libs common)
    
	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/test_fixture.cpp
		gtest/TestTokens.cpp
		gtest/FpgaCommsMsg_unittest.cpp
		
		# Test
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(FpgaCommsMsg_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FpgaCommsMsg_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(FpgaCommsMsg_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

