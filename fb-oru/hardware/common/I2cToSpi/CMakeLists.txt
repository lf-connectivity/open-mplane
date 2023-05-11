# Cmake file for common/I2cToSpi

add_sources (SOURCES
    src/Sc18is602bBus.cpp
    src/Sc18is602bBusSettings.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(I2cToSpi)

