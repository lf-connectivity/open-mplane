# Cmake file for applications/common-specific/RadioApp

add_sources (SOURCES
	src/RadioApp.cpp
	src/CommonPostInit.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Application)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "common")

	# Load google test
	include (gtest)

	addRepoLib(libs xcommon)
	addRepoLib(libs hardware common)
	addRepoLib(libs swtools shared)
	addRepoLib(libs tif-common)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	addTestCommon(TEST_TIF_COMMON tif)

	include_directories(gtest)
	set(gtest_src
		gtest/RadioApp_unittest.cpp
		gtest/tests.cpp
		
		# Mocks
		gtest/FpgaCommsShimSingleton.cpp
		gtest/TestInterfaceFactory.cpp
		${TEST_TIF_COMMON}/TestLimitsSettings.cpp
	)
#SDP#	addGtest(RadioApp_GTEST "${libs}" ${gtest_src})
	
	# Add code coverage
	include (coverage)
#SDP#	addCoverage(RadioApp_GTEST)

	# Add memory leak check
	include (valgrind)
#SDP#	addMemcheck(RadioApp_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

