# Cmake file for common/FpgaRegsEmu

if (${TARGET} STREQUAL "x86_64")

    add_sources (SOURCES
    	src/W1Clear.cpp
    	src/LatchedAlarmEmu.cpp
    	src/LatchedAntennaAlarmEmu.cpp
    )

    ## Cppcheck
    include (cppcheck)
    addCppcheck(FpgaRegsEmu)

endif ()


