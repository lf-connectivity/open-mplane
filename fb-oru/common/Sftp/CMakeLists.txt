# Cmake file for SftpPath

add_sources (SOURCES
	src/SftpPath.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(SftpPath)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/SftpPath_unittest.cpp
	)
	addGtest(SftpPath_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(SftpPath_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(SftpPath_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

