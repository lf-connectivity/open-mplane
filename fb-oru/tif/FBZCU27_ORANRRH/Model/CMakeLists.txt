# Cmake file for Zcu11_ORANRRH/Model

add_sources (SOURCES
	src/Fbzcu27OranrrhTestInterface.cpp
)



## Cppcheck
include (cppcheck)
addCppcheck(Fbzcu27_ORANRRHModel)

