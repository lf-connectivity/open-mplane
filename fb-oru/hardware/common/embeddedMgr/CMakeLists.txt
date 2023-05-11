# Cmake file for common/embeddedMgr

add_sources (SOURCES
	src/EmbeddedMgr.cpp
)

## When feature DPD2=NONE we need to add a dummy msg handler
if ($ENV{FEAT_DPD2} STREQUAL "NONE" )

	message(STATUS "Feature DPD2=NONE: Adding dummy msg handler")
	add_sources (SOURCES
		src/DummyRemoteMsgHandler.cpp
	)
	
endif()

## Cppcheck
include (cppcheck)
addCppcheck(embeddedMgr)

#if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
if ( (${TARGET} STREQUAL "x86_64") )

    addRepoLib(libs xcommon)
    addRepoLib(libs common)
    
	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/EmbeddedMgr_fixture.cpp
		gtest/EmbeddedMgr_unittest.cpp
		gtest/TestEmbeddedMgr.cpp
		gtest/tests.cpp
	)
	addGtest(embeddedMgr_GTEST "${libs}" ${gtest_src})
	
	# Add code coverage
	include (coverage)
	addCoverage(embeddedMgr_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(embeddedMgr_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") )

