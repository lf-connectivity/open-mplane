# Cmake file for BootEnv

add_sources (SOURCES
	src/BootEnvDevice.cpp
	src/BootEnv.cpp
	src/SingleBootEnv.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(BootEnv)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")

	addRepoLib(libs xcommon)

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/BootEnvDevice_unittest.cpp
		gtest/BootEnv_unittest.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(BootEnv_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(BootEnv_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(BootEnv_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

