# Cmake file for ETNA/waveform

add_sources (SOURCES
	src/WaveformControl.cpp
	src/WaveformHardware.cpp
	src/WaveformHardwareDpdAdc.cpp
	src/WaveformHardwareRxAdc.cpp
	src/WaveformHardwareFullrate.cpp
	src/WaveformHardwareRxFixedRate.cpp
	src/WaveformHardwareFastVss.cpp
	src/WaveformHardware153M6.cpp
    src/WaveformHardware122M88.cpp
	src/WaveformManager.cpp
	src/WaveMemMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(waveform)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

    set (libs "")

    ## Uses tinyxml2
    addRosLib( libs  tinyxml2 )

	addRepoLib(libs common)
	addRepoLib(libs xcommon)
	addRepoLib(libs hardware common)

	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/model_fixture.cpp
		gtest/tests.cpp
		gtest/TestWaveformFpga.cpp
		gtest/TestWaveFpgaSingleton.cpp
		gtest/Waveform_unittest.cpp
		gtest/WaveformControl_unittest.cpp
		gtest/WaveformHardware_unittest.cpp
		gtest/WaveformHardwareDpdAdc_unittest.cpp
		gtest/WaveformHardwareFullrate_unittest.cpp
		gtest/WaveformManager_unittest.cpp
		gtest/WaveMemMgr_unittest.cpp

		# Test Mock
		${TEST_HW_COMMON}/TestCommonCpriSingleton.cpp
		${TEST_HW_COMMON}/TestBus.cpp
		${TEST_HW_COMMON}/TestSystemSynth.cpp
		${TEST_HW_COMMON}/TestSystemSynthSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonDevices.cpp
	    ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
	    ${TEST_HW_COMMON}/TestCommonSynth.cpp
	    ${TEST_HW_COMMON}/TestCommonRefClock.cpp
	    ${TEST_HW_COMMON}/TestCommonRadio.cpp
	    ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
	    ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonSRxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
	    ${TEST_HW_COMMON}/TestCommonRxAgc.cpp
	    ${TEST_HW_COMMON}/TestCommonRxAgcSingleton.cpp
    	${TEST_HW_COMMON}/TestEtnaCarrierModelSingleton.cpp
    	${TEST_HW_COMMON}/TestEtnaCarrierHardwareDataSingleton.cpp
    	${TEST_HW_COMMON}/TestEtnaHardwareSettingsSingleton.cpp
		${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
	)
#	addGtest(waveform_GTEST "${libs}" ${gtest_src})
#
#	# Add code coverage
#	include (coverage)
#	addCoverage(waveform_GTEST)
#
#	# Add memory leak check
#	include (valgrind)
#	addMemcheck(waveform_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

