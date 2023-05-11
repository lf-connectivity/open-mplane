# Cmake file for common/cpri

add_sources (SOURCES
             src/CommonCpri.cpp
             src/CommonCpriCore.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(cpri)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) AND (${BUILD_FIBRE_INTERFACE} STREQUAL "CPRI") )

	addRepoLib( libs  xcommon )
	addRepoLib( libs  common )

	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
	    gtest/CommonCpriTestCase.cpp
	    gtest/CommonCpriTests.cpp

	    # Test Mocks
	    ${TEST_COMMON}/TestIloggerFactory.cpp
	    ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
	    ${TEST_HW_COMMON}/TestFpgaMock.cpp
	    ${TEST_HW_COMMON}/TestCommonCpriSingleton.cpp
		${TEST_HW_COMMON}/TestBus.cpp
	)
	addGTest(cpri_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(cpri_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(cpri_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) AND (${BUILD_FIBRE_INTERFACE} STREQUAL "CPRI") )

