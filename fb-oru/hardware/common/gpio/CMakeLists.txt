# Cmake file for common/gpio

add_sources (SOURCES
	src/CommonGpio.cpp
	src/CommonGpioKernel.cpp
	src/OffTargetGpio.cpp
	src/Mcp23S17Spi.cpp
	src/Tca6416aGpio.cpp
	src/GpioLinuxMgr.cpp
)

if (${TARGET} STREQUAL "x86_64")

	# PC sim
	add_sources (SOURCES
	    src/GpioControlLinuxSim.cpp
	)
else()

	# Target
	add_sources (SOURCES
	    src/GpioControlLinux.cpp
	)
endif()

## Cppcheck
include (cppcheck)
addCppcheck(gpio)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)
	
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/Tests.cpp
		gtest/Mcp23S17SpiTestCase.cpp
		
		${TEST_HW_COMMON}/TestBus.cpp
	)
	addGtest(GPIO_GTEST "common" ${gtest_src})

	# Add code coverage
	include (coverage)

	# Add memory leak check
	include (valgrind)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

