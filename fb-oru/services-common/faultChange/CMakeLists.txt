# Cmake file for common/faultChange

add_sources (SOURCES
	src/FaultChange.cpp
	src/FaultChangeSingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(faultChange)

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
		gtest/FaultChangeTests.cpp
	)
	addGTest(faultChange_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(faultChange_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(faultChange_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

