# Cmake file for Zcu11-AXIS-FTU/Model

add_sources (SOURCES
    src/Zcu111AxisRrhTestInterfaceFactory.cpp
    src/Zcu111AxisRrhTestInterface.cpp
    src/Zcu111AxisRrhSettings.cpp

    src/Zcu111AxisRrhFibreTestHandler.cpp
    src/Zcu111AxisRrhCarrierHwTestHandler.cpp
    src/Zcu111AxisRrhEmbeddedTestHandler.cpp
    src/Zcu111AxisRrhFpgaTestHandler.cpp
    src/Zcu111AxisRrhOranFpgaTestHandler.cpp
    src/Zcu111AxisRrhI2cTestHandler.cpp
    src/Zcu111AxisRrhRegDevicesTestHandler.cpp
    src/Zcu111AxisRrhRxPortTestHandler.cpp
    src/Zcu111AxisRrhTxPortTestHandler.cpp
    src/Zcu111AxisRrhAgcTestHandler.cpp
    src/Zcu111AxisRrhSystemTestHandler.cpp
    src/Zcu111AxisRrhGpioTestHandler.cpp
    src/Zcu111AxisRrhCarrierTestHandler.cpp
    src/Zcu111AxisRrhSrxPortTestHandler.cpp
    src/Zcu111AxisRrhHeartbeatTestHandler.cpp
    src/Zcu111AxisRrhRadioStateTestHandler.cpp
    src/Zcu111AxisRrhWaveformTestHandler.cpp
    src/Zcu111AxisRrhWaveformFileTestHandler.cpp
    src/Zcu111AxisRrhFtpTestHandler.cpp
    src/Zcu111AxisRrhEqualiserTestHandler.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Zcu11_AXIS_RRHModel)

