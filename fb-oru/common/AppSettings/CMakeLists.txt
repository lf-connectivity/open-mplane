# Cmake file for AppSettings

add_sources (SOURCES
	src/AppSettings.cpp
	src/AppSettingsSingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(AppSettings)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# uses vhi test
	include_directories(${VHI_TEST_PATH}/inc)
	
	# Load google test
	include (gtest)
	
	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/AppSettings_unittest.cpp
	)
	addGtest(AppSettings_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(AppSettings_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(AppSettings_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

