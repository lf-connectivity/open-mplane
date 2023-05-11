# Cmake file for common/RegModel

add_sources (SOURCES
	src/RegModel.cpp
	src/PagedRegModel.cpp
	src/RegModelMgr.cpp
	src/Mcp23S17RegModel.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RegModel)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load gtest
	include (gtest)

	addRepoLib(libs xcommon )
    addRepoLib(libs common )

	include_directories(gtest)
	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)
	
	set(gtest_src
		gtest/RegModel_fixture.cpp
		gtest/RegModel_unittest.cpp
		gtest/tests.cpp

		# Mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(RegModel_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(RegModel_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(RegModel_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

