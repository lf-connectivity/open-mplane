add_sources (SOURCES
    src/AtlasMplaneOranrrhTestInterfaceFactory.cpp
    src/AtlasMplaneOranrrhTestInterface.cpp
    src/AtlasMplaneOranrrhSettings.cpp

    src/AtlasMplaneOranrrhFibreTestHandler.cpp
    src/AtlasMplaneOranrrhCarrierHwTestHandler.cpp
    src/AtlasMplaneOranrrhEmbeddedTestHandler.cpp
    src/AtlasMplaneOranrrhFpgaTestHandler.cpp
    src/AtlasMplaneOranrrhOranFpgaTestHandler.cpp
    src/AtlasMplaneOranrrhI2cTestHandler.cpp
    src/AtlasMplaneOranrrhRegDevicesTestHandler.cpp
    src/AtlasMplaneOranrrhRxPortTestHandler.cpp
    src/AtlasMplaneOranrrhTxPortTestHandler.cpp
    src/AtlasMplaneOranrrhAgcTestHandler.cpp
    src/AtlasMplaneOranrrhSystemTestHandler.cpp
    src/AtlasMplaneOranrrhSystemConfigTestHandler.cpp
    src/AtlasMplaneOranrrhYangConfigTestHandler.cpp
    src/AtlasMplaneOranrrhDot1agdMonTestHandler.cpp
    src/AtlasMplaneOranrrhNetopeerMonTestHandler.cpp
    src/AtlasMplaneOranrrhYangTestTestHandler.cpp
    src/AtlasMplaneOranrrhCarrierTestHandler.cpp
    src/AtlasMplaneOranrrhGpioTestHandler.cpp
    src/AtlasMplaneOranrrhSrxPortTestHandler.cpp
    src/AtlasMplaneOranrrhHeartbeatTestHandler.cpp
    src/AtlasMplaneOranrrhRadioStateTestHandler.cpp
    src/AtlasMplaneOranrrhYangManagerTestHandler.cpp
    src/AtlasMplaneOranrrhIpTestHandler.cpp
    src/AtlasMplaneOranrrhIpListTestHandler.cpp
    src/AtlasMplaneOranrrhEqualiserTestHandler.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Atlas_Mplane_ORANRRHModel)
