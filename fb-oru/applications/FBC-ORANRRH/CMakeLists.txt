##======================================================================================================================
## Cmake file for applications/FBC-ORANRRH
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (applicationsFbcOranRrh CXX)
set (version "0.1")

##----------------------------------------------------------------------------------------------------------------------
if (NOT GITDIR)

	get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
	list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)
	
endif ()

##----------------------------------------------------------------------------------------------------------------------
## Get shared include
include(rse)
include(installSettings)

##----------------------------------------------------------------------------------------------------------------------
## Add all the includes directories under this directory
addIncludes ()

##----------------------------------------------------------------------------------------------------------------------
# Uses VHI & VSI interfaces
addInterfaceIncludes(hardware)
addInterfaceIncludes(services)

##----------------------------------------------------------------------------------------------------------------------
## Dummy target to allow 'make lib' to run
add_custom_target(lib)

##======================================================================================================================
## Executables

# one of these should set the variable $STARTUP_APP to the start application
set (STARTUP_APP "NOT SET")
add_subdirectory (FbcOranrrhProcess)
add_subdirectory (802_1agUtils)

addExternalDirectory (../shared/Ina226Rd)

addExternalDirectory (../shared/FpgaRd)
addExternalDirectory (../shared/FpgaWr)

addExternalDirectory (../shared/YangCarrier)
addExternalDirectory (../shared/SysrepoGet)
addExternalDirectory (../shared/SysrepoSet)

# addExternalDirectory (../shared/TifCmd)

# addExternalDirectory (../shared/YangFiles)
addExternalDirectory (../shared/YangSync)
addExternalDirectory (../shared/YangSupervision)

# addExternalDirectory (../shared/YangAcm)
# addExternalDirectory (../shared/YangSw)


# addExternalDirectory (../shared/YangFiles)
# addExternalDirectory (../shared/YangSyntax)
# addExternalDirectory (../shared/NetDev)
# addExternalDirectory (../shared/xrfdcTest)
# addExternalDirectory (../shared/Enet10G)
# addExternalDirectory (../shared/Sftp)
# addExternalDirectory (../shared/YangSyntax)
# addExternalDirectory (../shared/LabDiscovery)
# addExternalDirectory (../shared/R5ProxyTest)

##======================================================================================================================
## INSTALL
include (installCommonTasks)

