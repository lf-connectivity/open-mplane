# Cmake file for common/FpgaCommsEmu

if (${TARGET} STREQUAL "x86_64")

    add_sources (SOURCES
    	src/CommsEmuHandler.cpp
    	src/FpgaCommsEmulator.cpp
    	src/ToUblazeEmu.cpp
    	src/FromUblazeEmu.cpp
    	src/CommsEmuMsg.cpp
    )
    
endif()
    
if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Cppcheck
    include (cppcheck)
    addCppcheck(FpgaCommsEmu)

    set (libs "")
    addRepoLib(libs xcommon)
    addRepoLib(libs xcommon)
    addRepoLib(libs common)

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/comms_fixture.cpp
		gtest/tests.cpp
		gtest/CommsEmuHandler_unittest.cpp
		gtest/ToUblazeEmu_unittest.cpp
		gtest/FromUblazeEmu_unittest.cpp
		gtest/FpgaCommsEmulator_unittest.cpp
		
		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
#SDP#	addGtest(FpgaCommsEmu_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
#SDP#	addCoverage(FpgaCommsEmu_GTEST)

	# Add memory leak check
#	include (valgrind)
#	addMemcheck(FpgaCommsEmu_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

