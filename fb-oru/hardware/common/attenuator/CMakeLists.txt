# Cmake file for common/attenuator

add_sources (SOURCES
	src/AttnBase.cpp
	src/RFSA3714.cpp
	src/NxpBap70Q.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(attenuator)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    addRepoLib(libs xcommon)
    addRepoLib(libs common)

	# Load google test
	include (gtest)

    addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/Tests.cpp
		gtest/RFSA3714TestCase.cpp
		gtest/NxpBap70QTestCase.cpp
		
		${TEST_HW_COMMON}/TestBus.cpp
	)
	addGtest(attenuator_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(attenuator_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(attenuator_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

