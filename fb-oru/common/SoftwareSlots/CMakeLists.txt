# Cmake file for socket

add_sources (SOURCES
	src/SoftwareSlotConstants.cpp
	src/SoftwarePackage.cpp
	src/SoftwareSlot.cpp
	src/SoftwareSlotMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(softwareSlot)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	include (coverage)
	include (valgrind)

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/ImageFactory.cpp
		gtest/TestConstants.cpp
		gtest/SoftwarePackage_unittest.cpp
		gtest/SoftwareSlot_unittest.cpp
		gtest/SoftwareSlotMgr_unittest.cpp
		gtest/tests.cpp
		
		# Test mocks
	    ${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		
	)
	addGtest(softwareSlot_GTEST "${libs}" ${gtest_src})

	addCoverage(softwareSlot_GTEST)
	addMemcheck(softwareSlot_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

