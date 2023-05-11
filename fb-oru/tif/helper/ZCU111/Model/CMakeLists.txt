# Cmake file for helper/ZCU111/Model

add_sources (SOURCES
	src/CarrierHwTestHelper.cpp
	src/WaveformTestHelper.cpp
	src/WaveformWrxcalTestHelper.cpp
	src/WaveformFileTestHelper.cpp
	src/RadioStateTestHelper.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(ZCU111Model)

