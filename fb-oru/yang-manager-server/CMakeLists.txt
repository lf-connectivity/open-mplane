##======================================================================================================================
## Cmake file for yang-manager-server
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (yang-manager-server CXX)
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
useRepoLib (halmplane)
useRepoLib (hardware common)
useRepoLib (hardware ${BUILD_BOARD})
useRepoLib (hardware ${BUILD_BOARD}_${BUILD_APPLICATION})
useRepoLib( oran-libs zlib )
useRepoLib( oran-libs ssl )
useRepoLib( oran-libs crypto )
useRepoLib( oran-libs libssh )
useRepoLib( oran-libs sysrepo )
useRepoLib( oran-libs sysrepo-cpp )
useRepoLib( oran-libs yang )
useRepoLib( oran-libs yangcpp )
useRepoLib (services common)
useRepoLib (services ${BUILD_APPLICATION})
useRepoLib (services ${BUILD_BOARD})
useRepoLib (services ${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION})

#list(APPEND libs "-ldl -lrt")

##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_subdirectory (logging)
add_subdirectory (ssh)
add_subdirectory (ConfigParser)
add_subdirectory (Dot1agdMonitoringService)
add_subdirectory (LinuxPtpService)
add_subdirectory (NetopeerMonitoringService)
add_subdirectory (OranAlarms)
add_subdirectory (OranDelays)
add_subdirectory (OranFaults)
add_subdirectory (OranFm)
add_subdirectory (OranNetworking)
add_subdirectory (OranPerformanceMgmt)
add_subdirectory (OranSupervision)
add_subdirectory (RadioDatastore)
add_subdirectory (services-${BUILD_APPLICATION})
add_subdirectory (services-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION})
add_subdirectory (yang-handlers)
add_subdirectory (yang-manager)
add_subdirectory (yang-manager-service)
add_subdirectory (yang-models)
add_subdirectory (yang-sysrepo)
add_subdirectory (yang-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION})

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)

## Define the search path to use for YANG module and configuration files.
if (${TARGET} STREQUAL "x86_64")
	set(YANG_MODS_PATH ${GITDIR}/oran-libs/build/${TARGET}-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION}/sysroot/yangfiles)
	set(FAULT_CFG_PATH ${GITDIR}/yang-manager-server/fault-config)
	set(SYSREPO_REPO_PATH ${GITDIR}/oran-libs/build/${TARGET}-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION}/sysroot/sysrepo/repository)
	set(NETOPEER_PATH ${GITDIR}/oran-libs/build/${TARGET}-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION}/netopeer2-1.1.27-build)
	set(DOT1AGD_PATH ${GITDIR}/applications/${BUILD_CUSTOMER}-${BUILD_APPLICATION}/build/${TARGET}-${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION}/802_1agUtils)
else()
	set(YANG_MODS_PATH /nandflash/yangfiles)
	set(FAULT_CFG_PATH /nandflash/configdata)
	set(SYSREPO_REPO_PATH nandflash/sysrepo/repository)
	set(NETOPEER_PATH /usr/local/bin)
	set(DOT1AGD_PATH /usr/local/bin)
endif()

message( STATUS "Set YANG_MODS_PATH=${YANG_MODS_PATH}")
add_compile_definitions(YANG_MODS_PATH="${YANG_MODS_PATH}")
message( STATUS "Set FAULT_CFG_PATH=${FAULT_CFG_PATH}")
add_compile_definitions(FAULT_CFG_PATH="${FAULT_CFG_PATH}")
message( STATUS "Set SYSREPO_REPO_PATH=${SYSREPO_REPO_PATH}")
add_compile_definitions(SYSREPO_REPO_PATH="${SYSREPO_REPO_PATH}")
message( STATUS "Set NETOPEER_PATH=${NETOPEER_PATH}")
add_compile_definitions(NETOPEER_PATH="${NETOPEER_PATH}")
message( STATUS "Set DOT1AGD_PATH=${DOT1AGD_PATH}")
add_compile_definitions(DOT1AGD_PATH="${DOT1AGD_PATH}")

if (${TARGET} STREQUAL "x86_64")
set(SCRIPTS_PATH ${GITDIR}/yang-manager-server/scripts)
message( STATUS "Set SCRIPTS_PATH=${SCRIPTS_PATH}")
add_compile_definitions(SCRIPTS_PATH="${SCRIPTS_PATH}")
endif()
