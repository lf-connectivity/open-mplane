# Cmake file for hardware/common/caldata

add_sources (SOURCES
    src/CommonCalBase.cpp

    src/RxCalDownload.cpp
    src/RxIfCalDownload.cpp
    src/TxCalDownload.cpp
    src/SRxCalDownload.cpp
    src/SwrCalDownload.cpp
    src/CalData.cpp
    src/RxIfCalData.cpp
    src/RxCalData.cpp
    src/RxAgcCalData.cpp
    src/TxCalData.cpp
    src/SRxCalData.cpp
    src/SwrCalData.cpp
    src/TxCal.cpp
    src/RxCal.cpp
    src/RxIfCal.cpp
    src/RxAgcCal.cpp
    src/SRxCal.cpp
    src/SwrCal.cpp
    src/CalDataSingleton.cpp
    src/TxDCOffsetCal.cpp
    src/TxDCOffsetCalDownload.cpp
    src/TxQuadCal.cpp
    src/TxQuadCalDownload.cpp
    src/TxVVACal.cpp
    src/TxVVACalDownload.cpp
    src/PaDetCal.cpp
    src/PaDetCalDownload.cpp
    src/RxIfCalHelper.cpp
    src/PamCal.cpp
    src/PamCalData.cpp
    src/PamCalDownload.cpp
    src/TxIfCal.cpp
    src/TxIfCalData.cpp
    src/TxIfCalDownload.cpp
    src/TxIfCalHelper.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(caldata)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")

    ## Uses tinyxml2
    addRosLib( libs  tinyxml2 )

    ## Libraries used
    addRepoLib( libs  xcommon )
    addRepoLib( libs  common )

    # Load google test
    include (gtest)

    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)


    include_directories(gtest)
    set(gtest_src
        gtest/cm_fixture.cpp
        gtest/CommonCalBaseTestCase.cpp
        gtest/tests.cpp
        gtest/RxCalDownload_unittest.cpp
        gtest/RxIfCalDownload_unittest.cpp
        gtest/TxCalDownload_unittest.cpp
        gtest/SRxCalDownload_unittest.cpp
        gtest/SwrCalDownload_unittest.cpp
        gtest/RxCalDataTestCase.cpp
        gtest/RxIfCalDataTestCase.cpp
        gtest/TxCalDataTestCase.cpp
        gtest/TxIfCalDataTestCase.cpp
        gtest/RxAgcCalDataTestCase.cpp
        gtest/SRxCalDataTestCase.cpp
        gtest/SwrCalDataTestCase.cpp
        gtest/TxDCOffsetCalDataTestCase.cpp
        gtest/TxQuadCalDataTestCase.cpp
        gtest/TxVVACalDataTestCase.cpp
        gtest/PaDetCalDataTestCase.cpp
        gtest/PamCalDataTestCase.cpp

        # Test Mocks
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonDevices.cpp
        ${TEST_HW_COMMON}/TestCommonAttenuator.cpp
        ${TEST_HW_COMMON}/TestCommonSynth.cpp
        ${TEST_HW_COMMON}/TestCommonRefClock.cpp
        ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
        ${TEST_HW_COMMON}/TestCam.cpp
        ${TEST_HW_COMMON}/TestCamFactory.cpp
        ${TEST_HW_COMMON}/TestCommonRadio.cpp
        ${TEST_HW_COMMON}/TestCommonRadioInfoSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonRadioFactories.cpp
        ${TEST_HW_COMMON}/TestCommonRxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonSRxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonTxPortSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonCpriSingleton.cpp
        ${TEST_HW_COMMON}/TestBus.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierSingleton.cpp
        ${TEST_HW_COMMON}/TestCommonModules.cpp
        ${TEST_HW_COMMON}/TestRadioPostInit.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServer.cpp
        ${TEST_HW_COMMON}/TestCommonCarrierServerSingleton.cpp
        ${TEST_HW_COMMON}/TestIRfConstFactory.cpp
        ${TEST_HW_COMMON}/TestRxFreqConstFactory.cpp
        ${TEST_HW_COMMON}/TestTxFreqConstFactory.cpp
    )
    addGtest(caldata_GTEST "${libs}" ${gtest_src})

    # Add code coverage
    include (coverage)
    addCoverage(caldata_GTEST)

    # Add memory leak check
    include (valgrind)
    addMemcheck(caldata_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

