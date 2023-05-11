# Cmake file for Zcu11/Model
add_sources (SOURCES
	src/Fbzcu27UsedTestInterface.cpp
)

if (${BUILD_FIBRE_INTERFACE} STREQUAL "CPRI")

	add_sources (SOURCES
		src/Fbzcu27CpriTestHandler.cpp
	)

endif()

## Cppcheck
include (cppcheck)
addCppcheck(Fbzcu27Model)

