# Cmake file for common/sensors

add_sources (SOURCES
    src/NXPLM75B.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(sensors)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/Tests.cpp
		gtest/SensorsTestCase.cpp
		
		${TEST_HW_COMMON}/TestBus.cpp
	)
	addGtest(Sensors_GTEST "common" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Sensors_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(Sensors_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
