# Cmake file for yang-manager-server/RadioSysrepo

add_sources (SOURCES
	src/LeafContainer.cpp
	src/SysrepoGetitemsCallback.cpp
	src/RadioDatastoreSysrepo.cpp
	src/SysrepoUtils.cpp
	src/YangHandlerSysrepoUnlogged.cpp
	src/YangHandlerSysrepo.cpp
	src/YangHandlerSysrepo/HandlerCallback.cpp
	src/YangHandlerSysrepo/RpcCallback.cpp
	src/YangUserAuth.cpp
	src/YangParamSysrepo.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(yangsysrepo)

