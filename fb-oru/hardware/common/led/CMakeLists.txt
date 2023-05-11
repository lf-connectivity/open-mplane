# Cmake file for common/led

add_sources (SOURCES
	src/CLed.cpp
	src/CLedControl.cpp
	src/LedSystem.cpp
)





## Cppcheck
include (cppcheck)
addCppcheck(led)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/CLedTestCase.cpp
		gtest/LedSystemTestCase.cpp
		gtest/Tests.cpp

        # Test Mocks		
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
	)
	addGtest(led_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(led_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(led_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

