add_sources (SOURCES
    src/Zcu111MplaneOranrrhTestInterfaceFactory.cpp
    src/Zcu111MplaneOranrrhTestInterface.cpp
    src/Zcu111MplaneOranrrhSettings.cpp

    src/Zcu111MplaneOranrrhFibreTestHandler.cpp
    src/Zcu111MplaneOranrrhCarrierHwTestHandler.cpp
    src/Zcu111MplaneOranrrhEmbeddedTestHandler.cpp
    src/Zcu111MplaneOranrrhFpgaTestHandler.cpp
    src/Zcu111MplaneOranrrhOranFpgaTestHandler.cpp
    src/Zcu111MplaneOranrrhI2cTestHandler.cpp
    src/Zcu111MplaneOranrrhRegDevicesTestHandler.cpp
    src/Zcu111MplaneOranrrhRxPortTestHandler.cpp
    src/Zcu111MplaneOranrrhTxPortTestHandler.cpp
    src/Zcu111MplaneOranrrhAgcTestHandler.cpp
    src/Zcu111MplaneOranrrhSystemTestHandler.cpp
    src/Zcu111MplaneOranrrhSystemConfigTestHandler.cpp
    src/Zcu111MplaneOranrrhYangConfigTestHandler.cpp
    src/Zcu111MplaneOranrrhDot1agdMonTestHandler.cpp
    src/Zcu111MplaneOranrrhNetopeerMonTestHandler.cpp
    src/Zcu111MplaneOranrrhYangTestTestHandler.cpp
    src/Zcu111MplaneOranrrhCarrierTestHandler.cpp
    src/Zcu111MplaneOranrrhGpioTestHandler.cpp
    src/Zcu111MplaneOranrrhSrxPortTestHandler.cpp
    src/Zcu111MplaneOranrrhHeartbeatTestHandler.cpp
    src/Zcu111MplaneOranrrhRadioStateTestHandler.cpp
    src/Zcu111MplaneOranrrhYangManagerTestHandler.cpp
    src/Zcu111MplaneOranrrhIpTestHandler.cpp
    src/Zcu111MplaneOranrrhIpListTestHandler.cpp
    src/Zcu111MplaneOranrrhEqualiserTestHandler.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Zcu11_Mplane_ORANRRHModel)
