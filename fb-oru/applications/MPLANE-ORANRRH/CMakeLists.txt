##======================================================================================================================
## Cmake file for applications/MPLANE-ORANRRH
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (applicationsMplaneOranrrh CXX)
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
add_subdirectory (MplaneOranrrhProcess)
addExternalDirectory (../FBC-ORANRRH/802_1agUtils)


##======================================================================================================================
## INSTALL
include (installCommonTasks)
