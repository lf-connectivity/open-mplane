# Cmake file for common/trace

add_sources (SOURCES
	src/TraceFile.cpp
	src/TraceLoghistoryFile.cpp
	src/TraceMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(trace)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
	    gtest/TraceFile_unittest.cpp
	    gtest/TraceLoghistoryFile_unittest.cpp
	    gtest/TraceMgr_unittest.cpp
	    gtest/tests.cpp
	)
	addGtest(trace_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(trace_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(trace_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

