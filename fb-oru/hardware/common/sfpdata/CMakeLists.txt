# Cmake file for common/sfpdata

add_sources (SOURCES
	src/SfpData.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(sfpdata)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    addRepoLib(libs xcommon)
    addRepoLib(libs common)
    
    ## Uses tinyxml2
#    addRosLib( libs  tinyxml2 )

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
	    gtest/SfpData_unittest.cpp
	    gtest/tests.cpp
	    
        # Mocks
        ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
        ${TEST_HW_COMMON}/TestBus.cpp
	)
	addGtest(sfpdata_GTEST "${libs}" ${gtest_src})

    # Add code coverage
	include (coverage)
	addCoverage(sfpdata_GTEST)

    # Add memory leak check
	include (valgrind)
	addMemcheck(sfpdata_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

