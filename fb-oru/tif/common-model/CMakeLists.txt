##======================================================================================================================
## Cmake file for tif/common-model lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (tifCommon-model CXX)
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
useRepoLib (xcommon)
useRepoLib (common)
useRepoLib (hardware common)
useRepoLib (swtools shared)
useRepoLib (tif-common)
useRepoLib (tif-common helper/common)
useRepoLib (tif helper/common)

##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_subdirectory (Model)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)


