# Cmake file for common/driver

add_sources (SOURCES
    src/Driver.cpp
    src/RegDriver.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(driver)

