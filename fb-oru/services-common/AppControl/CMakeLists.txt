# Cmake file for common/AppControl

add_sources (SOURCES
    src/AppControl.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(AppControl)

