# Cmake file for common/bus

add_sources (SOURCES
    src/i2c/smbus.cpp
    src/Bus.cpp
    src/I2cBus.cpp
    src/I2cToSpiBus.cpp
    src/SpiBus.cpp
    src/SpiBusSettings.cpp
    src/I2cBusMgr.cpp
    src/I2cBusLinuxMgr.cpp
    src/FpgaSpiBus.cpp
    src/FpgaSpiBus0.cpp
    src/FpgaSpiBus1.cpp
    src/FpgaRxIfAttenuatorBus.cpp
    src/FpgaRxRfAttenuatorBus.cpp
    src/FpgaSRxAttenuatorBus.cpp
    src/FpgaTxVVABus.cpp
    src/I2cToSpiBusWithReadback.cpp
    src/SerialBus.cpp
    src/SerialBusLinux.cpp
    src/Rs485BusLinux.cpp
    src/TestDataBus.cpp
    src/SerialBusFpga.cpp
    src/Rs485BusFpga.cpp
)

if (${TARGET} STREQUAL "x86_64")

	# PC sim
	add_sources (SOURCES
	    src/I2cBusLinuxSim.cpp
	)
else()

	# Target
	add_sources (SOURCES
	    src/I2cBusLinux.cpp
	)
endif()

## Cppcheck
include (cppcheck)
addCppcheck(bus)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")

    ## Libraries used
    addRepoLib( libs  xcommon )
    addRepoLib( libs  common )

	# Load google test
	include (gtest)

    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)


	include_directories(gtest)
	set(gtest_src
        gtest/tests.cpp
        gtest/bus_fixture.cpp
        gtest/I2cBusMgr_unittest.cpp
        gtest/SpiBus_unittest.cpp
        gtest/FpgaSpiBus_unittest.cpp
        gtest/FpgaRxIfAttenuatorBus_unittest.cpp
        gtest/FpgaTxVVABus_unittest.cpp
        gtest/Rs485FpgaBus_fixture.cpp
        gtest/Rs485FpgaBus_unittest.cpp
        
        
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
        ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonDevices.cpp
        ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
	    ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
	    ${TEST_HW_COMMON}/FpgaRegCapture_fixture.cpp
	)
	addGtest(bus_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(bus_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(bus_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

