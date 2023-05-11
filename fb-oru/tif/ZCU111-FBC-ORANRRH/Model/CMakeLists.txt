# Cmake file for Zcu11-FBC-ORANRRH/Model

add_sources (SOURCES
    src/Zcu111FbcOranrrhTestInterfaceFactory.cpp
    src/Zcu111FbcOranrrhTestInterface.cpp
    src/Zcu111FbcOranrrhSettings.cpp

    src/Zcu111FbcOranrrhFibreTestHandler.cpp
    src/Zcu111FbcOranrrhCarrierHwTestHandler.cpp
    src/Zcu111FbcOranrrhEmbeddedTestHandler.cpp
    src/Zcu111FbcOranrrhFpgaTestHandler.cpp
    src/Zcu111FbcOranrrhOranFpgaTestHandler.cpp
    src/Zcu111FbcOranrrhI2cTestHandler.cpp
    src/Zcu111FbcOranrrhRegDevicesTestHandler.cpp
    src/Zcu111FbcOranrrhRxPortTestHandler.cpp
    src/Zcu111FbcOranrrhTxPortTestHandler.cpp
    src/Zcu111FbcOranrrhAgcTestHandler.cpp
    src/Zcu111FbcOranrrhSystemTestHandler.cpp
    src/Zcu111FbcOranrrhSystemConfigTestHandler.cpp
    src/Zcu111FbcOranrrhYangConfigTestHandler.cpp
    src/Zcu111FbcOranrrhDot1agdMonTestHandler.cpp
    src/Zcu111FbcOranrrhNetopeerMonTestHandler.cpp
    src/Zcu111FbcOranrrhYangTestTestHandler.cpp
    src/Zcu111FbcOranrrhCarrierTestHandler.cpp
    src/Zcu111FbcOranrrhGpioTestHandler.cpp
    src/Zcu111FbcOranrrhSrxPortTestHandler.cpp
    src/Zcu111FbcOranrrhHeartbeatTestHandler.cpp
    src/Zcu111FbcOranrrhRadioStateTestHandler.cpp
    src/Zcu111FbcOranrrhYangManagerTestHandler.cpp
    src/Zcu111FbcOranrrhIpTestHandler.cpp
    src/Zcu111FbcOranrrhIpListTestHandler.cpp
    src/Zcu111FbcOranrrhFtpTestHandler.cpp
    src/Zcu111FbcOranrrhEqualiserTestHandler.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(Zcu11_AFBC_ORANRRHModel)

