# Cmake file for helper/common/core

add_sources (SOURCES
#    src/FpgaCommsHelper.cpp
#    src/SharedArbTestHelper.cpp
    src/TcpPortHelper.cpp
    src/SettingsHelper.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(helpercore)

