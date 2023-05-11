# Cmake file for ByteTransfer

add_sources (SOURCES
	src/dummy.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(ByteTransfer)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")

    # Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/ByteTransfer_unittest.cpp
	)
	addGtest(ByteTransfer_GTEST "${libs}" ${gtest_src})

    # Add code coverage
	include (coverage)
	addCoverage(ByteTransfer_GTEST)
    # Add memory leak check
	include (valgrind)
	addMemcheck(ByteTransfer_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

