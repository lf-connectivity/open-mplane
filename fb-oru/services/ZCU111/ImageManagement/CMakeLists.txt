add_sources (SOURCES
	src/Zcu111ImageManagement.cpp
	src/Zcu111OsImage.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Zcu111ImageManagement)

