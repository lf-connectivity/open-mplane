##======================================================================================================================
## Cmake file for services/ZCU111 lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (servicesZCU111 CXX)
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
add_subdirectory (ImageManagement)
add_subdirectory (networking)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)



