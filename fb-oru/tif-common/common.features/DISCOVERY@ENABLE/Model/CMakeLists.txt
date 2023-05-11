# Cmake file for DISCOVERY@ENABLE/Model

add_sources (SOURCES

    src/DiscoveryEnableDiscoveryTestHandler.cpp

)


## Cppcheck
include (cppcheck)
addCppcheck(Model)

