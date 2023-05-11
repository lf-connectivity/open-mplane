# Cmake file for helper/core/core

add_sources (SOURCES
   src/PowerSaver.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(commoncore)

