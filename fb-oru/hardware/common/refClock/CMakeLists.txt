# Cmake file for common/refClock

add_sources (SOURCES
    src/LMX2594.cpp
    src/LMK04208.cpp
    src/SI5341bI2C.cpp
    src/SI570.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(refClock)

