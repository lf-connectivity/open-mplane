# Cmake file for # Cmake file for yang-manager-server/OranFaults

add_sources (SOURCES
	src/OranFaults.cpp
	src/OranFaultsSingleton.cpp

	src/CUPlaneConnectivityMinorFault.cpp
	src/CUPlaneConnectivityMajorFault.cpp

	src/CUPlaneMsgContentMinorFault.cpp
	src/CUPlaneMsgContentMajorFault.cpp

)

## Cppcheck
include (cppcheck)
addCppcheck(OranFaults)
