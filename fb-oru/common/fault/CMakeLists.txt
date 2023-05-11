# Cmake file for fault

add_sources (SOURCES
	src/Fault.cpp
	src/FaultUtils.cpp
	src/FaultOwner.cpp
	src/FaultsList.cpp
	src/FaultBuilder.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(fault)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Fault_unittest.cpp
		gtest/FaultOwner_unittest.cpp
		gtest/FaultPackage_unittest.cpp
		gtest/FaultBuilder_unittest.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(fault_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(fault_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(fault_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

