# Cmake file for TxService

add_sources (SOURCES
	src/RrhTxPowerControl.cpp
	src/RrhTxPowerControlFactory.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(TxService)

