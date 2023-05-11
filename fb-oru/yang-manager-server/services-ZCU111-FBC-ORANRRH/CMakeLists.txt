# Cmake file for yang-manager-server/services-ZCU111-FBC-ORANRRH

add_sources (SOURCES
	src/YangZcu111FbcOranrrhServices.cpp
	src/YangZcu111ServicesFactory.cpp
	src/Zcu111FbcLinuxPtpServiceSingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(services-ZCU111-FBC-ORANRRH)

