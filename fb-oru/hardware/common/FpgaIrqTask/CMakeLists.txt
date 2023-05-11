# Cmake file for common/FpgaIrqTask

add_sources (SOURCES
	src/FpgaIrqTask.cpp
	src/FpgaIrqWait.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FpgaIrqTask)

if ( ${BUILD_TEST_SHARED} )

    set (libs "")
    addRepoLib(libs xcommon)
    addRepoLib(libs common)

    # Load google test
    include (gtest)
    
    addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

    include_directories(gtest)
    set(gtest_src
        gtest/FpgaIrqTask_unittest.cpp
        gtest/FpgaIrqWait_unittest.cpp
        gtest/tests.cpp

		# Test mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
    )
    addGtest(FpgaIrqTask_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FpgaIrqTask_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(FpgaIrqTask_GTEST)


endif ()

