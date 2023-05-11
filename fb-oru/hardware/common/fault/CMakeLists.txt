# Cmake file for common/fault

add_sources (SOURCES
	src/SynthClockFault.cpp
	src/CommonRadioFaults.cpp
	src/Cpri0LossOfFrameFaultMajor.cpp
    src/Cpri0LossOfSignalFaultMajor.cpp
    src/Cpri0RemoteAlarmIndFaultMajor.cpp
    src/Cpri0SapDefectIndFaultMajor.cpp
    
    src/Cpri1LossOfFrameFaultMajor.cpp
    src/Cpri1LossOfSignalFaultMajor.cpp
    src/Cpri1RemoteAlarmIndFaultMajor.cpp
    src/Cpri1SapDefectIndFaultMajor.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(fault)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    addRepoLib(libs xcommon)
    addRepoLib(libs common)
    
    ## Uses tinyxml2
    addRosLib( libs  tinyxml2 )

	include_directories(test)
	
	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp

		# Test mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
	)
	addGtest(fault_GTEST "${libs}" ${gtest_src})
	

	# Add code coverage
	include (coverage)
	addCoverage(fault_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(fault_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

