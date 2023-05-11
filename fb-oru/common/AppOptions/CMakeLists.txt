# Cmake file for AppOptions

add_sources (SOURCES
	src/AppOptions.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(AppOptions)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")

	addRepoLib(libs xcommon)

	addTestCommon(TEST_COMMON common)

	# uses vhi test
	include_directories(${VHI_TEST_PATH}/inc)

	# Load google test
	include (gtest)

    include_directories(gtest)
	set(gtest_src
		gtest/AppOptions_unittest.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(AppOptions_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(AppOptions_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(AppOptions_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

