# Cmake file for common/EgAppControl

add_sources (SOURCES
        src/CommonServices.cpp
        src/EgAppControl.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(EgAppControl)

