# Cmake file for common/Discovery

add_sources (SOURCES
	src/Discovery.cpp
	src/DiscoverySingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Discovery)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)
	addRepoLib (libs hardware common)

	# Load google test
	include (gtest)

	include_directories(gtest)
#	set(gtest_src
#		gtest/data/TestDpdAlarm.cpp
#		gtest/data/TestDpdVswr.cpp
#		gtest/tests.cpp
#		gtest/TestDpdComms.cpp
#		gtest/TestDpdCommsSingleton.cpp
#		gtest/TestMsgFactory.cpp
#		gtest/TestTokens.cpp
#		gtest/Discovery_unittest.cpp
#	)
#	addGtest(Discovery_GTEST "${libs}" ${gtest_src})
#
#
	# Add code coverage
#	include (coverage)
#	addCoverage(Discovery_GTEST)
#
	# Add memory leak check
#	include (valgrind)
#	addMemcheck(Discovery_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

