# Cmake file for MsgQ

add_sources (SOURCES
	src/MsgQ.cpp
	src/PseudoMsgQ.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(MsgQ)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/MsgQ_unittest.cpp
		gtest/PseudoMsgQ_unittest.cpp
	)
	addGtest(MsgQ_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(MsgQ_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(MsgQ_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

