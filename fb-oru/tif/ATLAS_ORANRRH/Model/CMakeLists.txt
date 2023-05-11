# Cmake file for Zcu11_ORANRRH/Model

add_sources (SOURCES
	src/AtlasOranrrhTestInterface.cpp
)



## Cppcheck
include (cppcheck)
addCppcheck(Atlas_ORANRRHModel)

