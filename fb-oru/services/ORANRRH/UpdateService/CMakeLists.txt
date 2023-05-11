# Cmake file for ORANRRH/UpdateService

add_sources (SOURCES
	src/OranRrhUpdateService.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RrhUpdateService)

if (${TARGET} STREQUAL "x86_64")


	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/FtuUpdateServiceTestCase.cpp
		
		## Test Mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_HW_COMMON}/TestFpgaKernel.cpp
		${TEST_HW_COMMON}/TestCommonRadio.cpp
		${TEST_HW_COMMON}/TestCalData.cpp
	)
	#addGtest(FtuUpdateService_GTEST "common;hardwareCommon;hardwareVhiTest" ${gtest_src})

	# Add code coverage
	include (coverage)
	#addCoverage(FtuUpdateService_GTEST)

	# Add memory leak check
	include (valgrind)
	#addMemcheck(FtuUpdateService_GTEST)


endif (${TARGET} STREQUAL "x86_64")

