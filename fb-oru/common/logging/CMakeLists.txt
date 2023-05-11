# Cmake file for logging

add_sources (SOURCES
	src/Loggable.cpp
	src/LogList.cpp
	src/LoggerBase.cpp
	src/LoggerSyslog.cpp
	src/LogHistoryBuffer.cpp
	src/LoggerHistorySyslog.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(logging)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/logging_fixture.cpp
		gtest/LogList_unittest.cpp
		gtest/LogHistory_unittest.cpp
		gtest/Loggable_unittest.cpp
		gtest/LoggerSyslog_unittest.cpp

		# Test Mock
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(logging_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(logging_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(logging_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

