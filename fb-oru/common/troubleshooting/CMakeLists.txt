# Cmake file for common/troubleshooting

add_sources (SOURCES
	src/TroubleshootFile.cpp
	src/TroubleshootLoghistoryFile.cpp
	src/TroubleshootMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(troubleshooting)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/TroubleshootFile_unittest.cpp
		gtest/TroubleshootLoghistoryFile_unittest.cpp
		gtest/TroubleshootMgr_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(troubleshooting_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(troubleshooting_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(troubleshooting_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

