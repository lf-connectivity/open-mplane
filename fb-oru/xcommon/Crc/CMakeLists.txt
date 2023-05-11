# Cmake file for Crc

add_sources (SOURCES
	src/Crc.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Crc)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Crc_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(Crc_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Crc_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(Crc_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

