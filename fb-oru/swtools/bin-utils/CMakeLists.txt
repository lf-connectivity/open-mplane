##======================================================================================================================
## Cmake file for swtools/bin-utils
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (swtoolsBinUtils CXX)
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
useRepoLib (common)
useRepoLib (xcommon)
useRepoLib (swtools shared)


##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_subdirectory (lib-binutils)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)

##----------------------------------------------------------------------------------------------------------------------
## Executables
add_subdirectory (gentool)
add_subdirectory (regtool)



