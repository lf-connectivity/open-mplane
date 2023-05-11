##======================================================================================================================
## Cmake file for Feature WEBSOCK-LAB
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (applications-commonCommon.featuresWEBSOCK_LAB CXX)
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
# Use of the repository libs
useRepoLib (xcommon)
useRepoLib (common)
useRepoLib (swtools shared)
useRepoLib (tif-common)

useRepoLib (applications common)

##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_subdirectory (BuildFeature)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)



