add_sources (SOURCES
	src/Zcu111OranImageManagement.cpp
	src/Zcu111OranOsImage.cpp
	src/Zcu111OranAppImage.cpp
	src/Zcu111FbcSoftwareFactory.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Zcu111ImageManagement)

