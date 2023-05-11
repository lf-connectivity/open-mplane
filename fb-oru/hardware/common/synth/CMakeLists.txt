# Cmake file for common/synth

add_sources (SOURCES
	src/SI5382aI2C.cpp
	src/SI5382aI2CWithIntr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(synth)

