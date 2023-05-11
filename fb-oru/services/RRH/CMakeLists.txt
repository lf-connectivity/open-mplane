##======================================================================================================================
## Cmake file for services/RRH lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (servicesRRH CXX)
set (version "0.1")

##----------------------------------------------------------------------------------------------------------------------
if (NOT GITDIR)

	get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
	list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)
	
endif ()

##----------------------------------------------------------------------------------------------------------------------
## Get shared include
include(rse)

##----------------------------------------------------------------------------------------------------------------------
## Add all the includes directories under this directory
addIncludes ()

##----------------------------------------------------------------------------------------------------------------------
# Uses VHI & VSI interfaces
addInterfaceIncludes(hardware)
addInterfaceIncludes(services)

##----------------------------------------------------------------------------------------------------------------------
# Use of the repository libs
useRepoLib (common)
useRepoLib (xcommon)
useRepoLib (hardware common)
useRepoLib (hardware ${BUILD_BOARD}_${BUILD_APPLICATION})
useRepoLib (services common)

##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_subdirectory (AppControl)
add_subdirectory (UpdateService)

addExternalDirectory (../shared/Alarms)
addExternalDirectory (../shared/RadioStateService)
addExternalDirectory (../shared/FibreControlService)
addExternalDirectory (../shared/TxService)

if (FEAT_DPD2 STREQUAL "APP")
addExternalDirectory (../shared/RadioDpd2Service)
endif()

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)



