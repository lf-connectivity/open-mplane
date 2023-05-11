# Cmake file for Zcu11_ORANRRH/Model

add_sources (SOURCES
	src/Zcu111OranrrhTestInterface.cpp
)



## Cppcheck
include (cppcheck)
addCppcheck(Zcu111_ORANRRHModel)

