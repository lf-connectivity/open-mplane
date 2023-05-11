# Cmake file for common/hdlc

add_sources (SOURCES
	src/Hdlc.cpp
	src/fcs.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(hdlc)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")

    ## Libraries used
    addRepoLib( libs  common )
    addRepoLib( libs  xcommon )
    
	# Load google test
	include (gtest)
	
	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/Tests.cpp
		gtest/TestHdlc.cpp
		gtest/Hdlc_unittest.cpp
		
		${TEST_HW_COMMON}/TestBus.cpp
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(HDLC_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(HDLC_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(HDLC_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )