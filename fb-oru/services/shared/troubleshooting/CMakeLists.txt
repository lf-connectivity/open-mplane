# Cmake file for shared/troubleshooting

add_sources (SOURCES
	src/TroubleshootCarrierFile.cpp
	src/TroubleshootCarrierhwFile.cpp
	src/TroubleshootTxFile.cpp
	src/TroubleshootRxFile.cpp
	src/TroubleshootHelper.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(troubleshooting)

