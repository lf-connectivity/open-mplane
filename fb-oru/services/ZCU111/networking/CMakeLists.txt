# Cmake file for ZCU111/networking

add_sources (SOURCES
	src/LoRestart.cpp
	src/Zcu111BaseNetworkingService.cpp
	src/Zcu111NetworkingService.cpp
)



## Cppcheck
include (cppcheck)
addCppcheck(Zcu111Networking)

