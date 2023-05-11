# Cmake file for FileStatus

add_sources (SOURCES
	src/NullFileStatus.cpp
	src/FileStatus.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FileStatus)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

    set (libs "")

	addRepoLib(libs xcommon)

	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/FileStatus_unittest.cpp
		gtest/tests.cpp
		
		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(FileStatus_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FileStatus_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(FileStatus_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

