add_sources (SOURCES
	../services-ZCU111-FBC-ORANRRH/src/YangZcu111FbcOranrrhServices.cpp
	../services-ZCU111-FBC-ORANRRH/src/YangZcu111ServicesFactory.cpp
	../services-ZCU111-FBC-ORANRRH/src/Zcu111FbcLinuxPtpServiceSingleton.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(services-FBZCU27-MPLANE-ORANRRH)
