# Cmake file for common:DISCOVERY=LAB/Feature

add_sources (SOURCES
	src/FeatureDiscoveryLab.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FeatureDiscovery)

