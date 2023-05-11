# Cmake file for common/MemMon

add_sources (SOURCES
	src/MemMon.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(MemMon)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)
	addRepoLib (libs hardware common)

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/MemMon_unittest.cpp
		
		# Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(MemMon_GTEST "${libs}" ${gtest_src})


	# Add code coverage
	include (coverage)
	addCoverage(MemMon_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(MemMon_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

