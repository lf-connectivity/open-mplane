# Cmake file for Zcu11/Model
add_sources (SOURCES
	src/AtlasUsedTestInterface.cpp
)

if (${BUILD_FIBRE_INTERFACE} STREQUAL "CPRI")

	add_sources (SOURCES
		src/AtlasCpriTestHandler.cpp
	)

endif()

## Cppcheck
include (cppcheck)
addCppcheck(AtlasModel)

