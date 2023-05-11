# Cmake file for DPD@APP/Model

add_sources (SOURCES

    src/DpdAppDpdTestHandler.cpp

)


## Cppcheck
include (cppcheck)
addCppcheck(Model)

