# Cmake file for Zcu11/Model
add_sources (SOURCES
	src/Zcu111UsedTestInterface.cpp
)

if (${BUILD_FIBRE_INTERFACE} STREQUAL "CPRI")

	add_sources (SOURCES
		src/Zcu111CpriTestHandler.cpp
	)

endif()

## Cppcheck
include (cppcheck)
addCppcheck(Zcu111Model)

