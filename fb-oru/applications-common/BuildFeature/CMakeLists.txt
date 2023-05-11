# Cmake file for applications/applications-common/BuildFeature

add_sources (SOURCES
	src/BuildFeature.cpp
	src/BuildFeatureList.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(BuildFeature)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "common")

	# Load google test
	include (gtest)

	# use VHI/VSI test mocks
#	addRepoLib(libs hardware vhi test)
#	addRepoLib(libs services vsi test)

	addRepoLib(libs xcommon)
#	addRepoLib(libs hardware common)
	addRepoLib(libs tif-common)

#	addTestCommon(TEST_COMMON common)
#	addTestCommon(HARDWARE_TEST_COMMON hardware)
#	addTestCommon(TIF_TEST_COMMON tif)

	include_directories(gtest)
	set(gtest_src
		gtest/BuildFeature_unittest.cpp
#		gtest/tests.cpp

		# Mocks
#		gtest/FpgaCommsShimSingleton.cpp
#		gtest/TestInterfaceFactory.cpp
#		${TIF_TEST_COMMON}/TestLimitsSettings.cpp
	)
	addGtest(BuildFeature_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(BuildFeature_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(BuildFeature_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

