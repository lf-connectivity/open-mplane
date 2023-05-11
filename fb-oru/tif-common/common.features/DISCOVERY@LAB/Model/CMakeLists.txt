# Cmake file for DISCOVERY@ENABLE/Model

add_sources (SOURCES

    src/DiscoveryLabDiscoveryTestHandler.cpp

)


## Cppcheck
include (cppcheck)
addCppcheck(Model)

