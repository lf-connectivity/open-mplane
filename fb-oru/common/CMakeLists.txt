##======================================================================================================================
## Cmake file for common lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (common CXX)
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

##----------------------------------------------------------------------------------------------------------------------
## Library Source

add_subdirectory (Alarm)
add_subdirectory (AnsiEsc)
add_subdirectory (AppOptions)
add_subdirectory (AppSettings)
add_subdirectory (Benchmark)
add_subdirectory (BootEnv)
add_subdirectory (BootTimer)
add_subdirectory (calDownloadManagement)
add_subdirectory (configDownloadManagement)
add_subdirectory (configData)
add_subdirectory (datatype)
add_subdirectory (DataVariant)
add_subdirectory (Delay)
add_subdirectory (device)
add_subdirectory (FailString)
add_subdirectory (fault)
add_subdirectory (FileConfig)
add_subdirectory (FileLock)
add_subdirectory (FileMap)
add_subdirectory (FileMgr)
add_subdirectory (FileORanLog)
add_subdirectory (FileStatus)
add_subdirectory (imageManagement)
add_subdirectory (initialise)
add_subdirectory (logging)
add_subdirectory (Maths)
add_subdirectory (MemMap)
add_subdirectory (MovingAvg)
add_subdirectory (module)
add_subdirectory (MsgQ)
add_subdirectory (NetDevice)
add_subdirectory (Networking)
add_subdirectory (NetStatus)
add_subdirectory (observer)
add_subdirectory (Path)
add_subdirectory (Process)
add_subdirectory (RemoteMsg)
add_subdirectory (ros-tests)
add_subdirectory (service)
add_subdirectory (ServicesMonitor)
add_subdirectory (Sftp)
add_subdirectory (socket)
add_subdirectory (SoftwareSlots)
add_subdirectory (spline)
add_subdirectory (SSDP)
add_subdirectory (stringfunc)
add_subdirectory (task)
add_subdirectory (Tcp)
add_subdirectory (TifIoctl)
add_subdirectory (timer)
add_subdirectory (trace)
add_subdirectory (troubleshooting)
add_subdirectory (Val)
add_subdirectory (WatchdogCount)
add_subdirectory (WebSocket)


##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)

## Define the search path to use for configuration files.
if (${TARGET} STREQUAL "x86_64")
	set(CFG_DATA_PATH ${GITDIR}/yang-manager-server/yang-config)
else()
	set(CFG_DATA_PATH /nandflash/configdata)
endif()

message( STATUS "Set CFG_DATA_PATH=${CFG_DATA_PATH}")
add_compile_definitions(CFG_DATA_PATH="${CFG_DATA_PATH}")
