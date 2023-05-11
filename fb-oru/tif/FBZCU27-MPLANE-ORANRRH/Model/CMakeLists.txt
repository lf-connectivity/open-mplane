add_sources (SOURCES
    src/Fbzcu27MplaneOranrrhTestInterfaceFactory.cpp
    src/Fbzcu27MplaneOranrrhTestInterface.cpp
    src/Fbzcu27MplaneOranrrhSettings.cpp

    src/Fbzcu27MplaneOranrrhFibreTestHandler.cpp
    src/Fbzcu27MplaneOranrrhCarrierHwTestHandler.cpp
    src/Fbzcu27MplaneOranrrhEmbeddedTestHandler.cpp
    src/Fbzcu27MplaneOranrrhFpgaTestHandler.cpp
    src/Fbzcu27MplaneOranrrhOranFpgaTestHandler.cpp
    src/Fbzcu27MplaneOranrrhI2cTestHandler.cpp
    src/Fbzcu27MplaneOranrrhRegDevicesTestHandler.cpp
    src/Fbzcu27MplaneOranrrhRxPortTestHandler.cpp
    src/Fbzcu27MplaneOranrrhTxPortTestHandler.cpp
    src/Fbzcu27MplaneOranrrhAgcTestHandler.cpp
    src/Fbzcu27MplaneOranrrhSystemTestHandler.cpp
    src/Fbzcu27MplaneOranrrhSystemConfigTestHandler.cpp
    src/Fbzcu27MplaneOranrrhYangConfigTestHandler.cpp
    src/Fbzcu27MplaneOranrrhDot1agdMonTestHandler.cpp
    src/Fbzcu27MplaneOranrrhNetopeerMonTestHandler.cpp
    src/Fbzcu27MplaneOranrrhYangTestTestHandler.cpp
    src/Fbzcu27MplaneOranrrhCarrierTestHandler.cpp
    src/Fbzcu27MplaneOranrrhGpioTestHandler.cpp
    src/Fbzcu27MplaneOranrrhSrxPortTestHandler.cpp
    src/Fbzcu27MplaneOranrrhHeartbeatTestHandler.cpp
    src/Fbzcu27MplaneOranrrhRadioStateTestHandler.cpp
    src/Fbzcu27MplaneOranrrhYangManagerTestHandler.cpp
    src/Fbzcu27MplaneOranrrhIpTestHandler.cpp
    src/Fbzcu27MplaneOranrrhIpListTestHandler.cpp
    src/Fbzcu27MplaneOranrrhEqualiserTestHandler.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Fbzcu27_Mplane_ORANRRHModel)
