##======================================================================================================================
## Cmake file for services/ATLAS-MPLANE-ORANRRH lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (servicesATLAS-MPLANE-ORANRRH CXX)
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
useRepoLib (services ${BUILD_BOARD})
useRepoLib (services ${BUILD_APPLICATION})

##----------------------------------------------------------------------------------------------------------------------
## Library Source
addExternalDirectory (../ZCU111-FBC-ORANRRH/ImageManagement)
addExternalDirectory (../ZCU111-FBC-ORANRRH/AppControl)
addExternalDirectory (../ZCU111-FBC-ORANRRH/UpdateService)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)
