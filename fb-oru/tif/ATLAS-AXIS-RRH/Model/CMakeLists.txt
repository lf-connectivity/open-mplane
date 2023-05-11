# Cmake file for ATLAS-AXIS-RRH/Model

add_sources (SOURCES
    src/AtlasAxisRrhTestInterfaceFactory.cpp
    src/AtlasAxisRrhTestInterface.cpp
    src/AtlasAxisRrhSettings.cpp

    src/AtlasAxisRrhFibreTestHandler.cpp
    src/AtlasAxisRrhCarrierHwTestHandler.cpp
    src/AtlasAxisRrhEmbeddedTestHandler.cpp
    src/AtlasAxisRrhFpgaTestHandler.cpp
    src/AtlasAxisRrhOranFpgaTestHandler.cpp
    src/AtlasAxisRrhI2cTestHandler.cpp
    src/AtlasAxisRrhRegDevicesTestHandler.cpp
    src/AtlasAxisRrhRxPortTestHandler.cpp
    src/AtlasAxisRrhTxPortTestHandler.cpp
    src/AtlasAxisRrhAgcTestHandler.cpp
    src/AtlasAxisRrhSystemTestHandler.cpp
    src/AtlasAxisRrhGpioTestHandler.cpp
    src/AtlasAxisRrhCarrierTestHandler.cpp
    src/AtlasAxisRrhSrxPortTestHandler.cpp
    src/AtlasAxisRrhHeartbeatTestHandler.cpp
    src/AtlasAxisRrhRadioStateTestHandler.cpp
    src/AtlasAxisRrhWaveformTestHandler.cpp
    src/AtlasAxisRrhWaveformFileTestHandler.cpp
    src/AtlasAxisRrhFtpTestHandler.cpp
    src/AtlasAxisRrhEqualiserTestHandler.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Atlas_AXIS_RRHModel)

