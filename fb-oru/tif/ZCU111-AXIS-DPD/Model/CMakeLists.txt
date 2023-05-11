# Cmake file for Zcu11-AXIS-FTU/Model

add_sources (SOURCES
    src/Zcu111AxisDpdTestInterfaceFactory.cpp
    src/Zcu111AxisDpdTestInterface.cpp
    src/Zcu111AxisDpdSettings.cpp

    src/Zcu111AxisDpdFibreTestHandler.cpp
    src/Zcu111AxisDpdCarrierHwTestHandler.cpp
    src/Zcu111AxisDpdEmbeddedTestHandler.cpp
    src/Zcu111AxisDpdFpgaTestHandler.cpp
    src/Zcu111AxisDpdOranFpgaTestHandler.cpp
    src/Zcu111AxisDpdI2cTestHandler.cpp
    src/Zcu111AxisDpdRegDevicesTestHandler.cpp
    src/Zcu111AxisDpdRxPortTestHandler.cpp
    src/Zcu111AxisDpdTxPortTestHandler.cpp
    src/Zcu111AxisDpdAgcTestHandler.cpp
    src/Zcu111AxisDpdSystemTestHandler.cpp
    src/Zcu111AxisDpdGpioTestHandler.cpp
    src/Zcu111AxisDpdCarrierTestHandler.cpp
    src/Zcu111AxisDpdSrxPortTestHandler.cpp
    src/Zcu111AxisDpdHeartbeatTestHandler.cpp
    src/Zcu111AxisDpdRadioStateTestHandler.cpp
    src/Zcu111AxisDpdDpdCtrlTestHandler.cpp
    src/Zcu111AxisDpdCfrTestHandler.cpp

    src/Zcu111AxisDpdWaveformTestHandler.cpp
    src/Zcu111AxisDpdWaveformFileTestHandler.cpp
    src/Zcu111AxisDpdEqualiserTestHandler.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Zcu11_AXIS_DpdModel)

