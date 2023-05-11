# Cmake file for DPD@XILINX/Model

add_sources (SOURCES

    src/DpdXilinxDpdTestHandler.cpp

)


## Cppcheck
include (cppcheck)
addCppcheck(Model)

