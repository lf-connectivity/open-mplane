##======================================================================================================================
## Cmake file for tif/ZCU111-FBC-ORANRRH lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (tifZCU111-FBC-ORANRRH CXX)
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
useRepoLib (swtools shared)
useRepoLib (tif-common)
useRepoLib (tif-common helper/common)
useRepoLib (tif common-model)
useRepoLib (tif ZCU111)
useRepoLib (tif ZCU111_ORANRRH)
useRepoLib (tif helper/common)
useRepoLib (tif helper/ZCU111)
useRepoLib (tif helper/ORANRRH)

useRepoLib (hardware common)
useRepoLib (hardware ZCU111)
useRepoLib (hardware ZCU111_ORANRRH)
useRepoLib (yang-manager-server)
useRepoLib( oran-libs sysrepo-cpp )

##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_subdirectory (Model)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)


