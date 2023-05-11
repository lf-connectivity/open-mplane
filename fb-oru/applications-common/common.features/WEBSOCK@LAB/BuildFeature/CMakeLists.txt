# Cmake file for common:WEBSOCK-LAB/Feature

add_sources (SOURCES
	src/FeatureWebsockLab.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FeatureWebsock)

