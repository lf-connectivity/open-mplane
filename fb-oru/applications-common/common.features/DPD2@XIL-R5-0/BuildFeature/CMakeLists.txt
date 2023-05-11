# Cmake file for common:DPD=XILINX/Feature

add_sources (SOURCES
	src/FeatureDpd2XilR50.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FeatureDpd)

