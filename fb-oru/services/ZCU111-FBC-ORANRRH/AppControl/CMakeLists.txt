# Cmake file for ZCU111-AXIS-ART/AppControl

add_sources (SOURCES
	src/Zcu111AppControl.cpp
	src/Zcu111AppControlFactory.cpp
	src/CdiNetworkingService.cpp
	src/OranNetworkingService.cpp
	src/OranrrhNetworkingSingleton.cpp
	src/Zcu111FbcOranrrhServices.cpp
    src/Zcu111ServicesFactory.cpp
    src/Zcu111ImageManagementSingleton.cpp
    src/PacketSnifferSingleton.cpp
)



## Cppcheck
include (cppcheck)
addCppcheck(Zcu111AppControl)

