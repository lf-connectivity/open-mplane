# Cmake file for Rrh/FibreControlService

add_sources (SOURCES
	src/RrhCpriFactory.cpp
	src/RrhCpriPortHandling.cpp
)

# Cppcheck
include (cppcheck)
addCppcheck(FibreControlService)

