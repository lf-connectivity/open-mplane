# Cmake file for FileLock - only used for HOST testbenches

if (${TARGET} STREQUAL "x86_64")

add_sources (SOURCES
	src/FileLock.cpp
	src/FileLockSockets.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FileLock)

endif()


## There's no simple way to test this because you need to run multiple processes and google test doesn't play
## very well with fork. So I've just manually tested
#if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
#
#    set (libs "")
#    addRepoLib (libs xcommon)
#
#	addTestCommon(TEST_COMMON common)
#
	# Load google test
#	include (gtest)
#
#	include_directories(gtest)
#	set(gtest_src
#		gtest/FileLock_unittest.cpp
#
		# Test Mock
#		${TEST_COMMON}/TestIloggerFactory.cpp
#	)
#	addGtest(FileLock_GTEST "${libs}" ${gtest_src})
#
	# Add code coverage
#	include (coverage)
#	addCoverage(FileLock_GTEST)
	# Add memory leak check
#	include (valgrind)
#	addMemcheck(FileLock_GTEST)
#
#endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

