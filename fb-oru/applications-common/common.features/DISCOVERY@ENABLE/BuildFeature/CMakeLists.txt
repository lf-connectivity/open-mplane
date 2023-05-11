# Cmake file for common:DISCOVERY=ENABLE/Feature

add_sources (SOURCES
	src/FeatureDiscoveryEnable.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FeatureDiscovery)

