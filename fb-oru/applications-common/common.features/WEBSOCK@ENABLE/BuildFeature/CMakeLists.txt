# Cmake file for common:WEBSOCK-TRUE/Feature

add_sources (SOURCES
	src/FeatureWebsockEnable.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FeatureWebsock)

