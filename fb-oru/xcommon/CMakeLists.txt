##======================================================================================================================
## Cmake file for xcommon lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (xcommon CXX)
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
## Library Source

add_subdirectory (md5)
add_subdirectory (Base64)
add_subdirectory (ByteTransfer)
add_subdirectory (Crc)
add_subdirectory (Feature)
add_subdirectory (WaveFile)
add_subdirectory (sha1)
add_subdirectory (crypt)
add_subdirectory (key)
add_subdirectory (lzo)
add_subdirectory (PathUtils)
#add_subdirectory (fft)
add_subdirectory (cubicSpline)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)


