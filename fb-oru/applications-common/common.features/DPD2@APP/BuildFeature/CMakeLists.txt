# Cmake file for common:DPD2=APP/Feature

add_sources (SOURCES
	src/FeatureDpd2App.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FeatureDpd)

