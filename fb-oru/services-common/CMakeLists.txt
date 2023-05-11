##======================================================================================================================
## Cmake file for services/common lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (servicesCommon CXX)
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
useRepoLib (hardware common)

##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_subdirectory (NetworkingService)
add_subdirectory (AppServices)
add_subdirectory (AppMonService)
add_subdirectory (MemMon)
add_subdirectory (Discovery)
add_subdirectory (DigitalPowerService)
add_subdirectory (faultChange)
add_subdirectory (faultService)
#add_subdirectory (FibreControlService)
add_subdirectory (ImageManagement)
add_subdirectory (AppControl)
add_subdirectory (rxService)
add_subdirectory (TxService)
add_subdirectory (DpdService)
add_subdirectory (Dpd2Service)


##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)



