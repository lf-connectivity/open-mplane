##======================================================================================================================
## Settings for ARM builds
##
## Useage: cmake -DCMAKE_TOOLCHAIN_FILE=~/git/buildTools/cmake/Toolchains/petalinux.cmake <src>
##======================================================================================================================

#message ("petalinux.cmake: GITDIR=${GITDIR} PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}") 

##----------------------------------------------------------------------------------------------------------------------
if (NOT GITDIR)

	get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
	
	# Given a source path, keep stripping off directories until the path is the top-level git path
	# in which we expect at least buildTools directory to be present
	while (NOT IS_DIRECTORY ${GITDIR}/buildTools)
		
		get_filename_component (GITDIR ${GITDIR} DIRECTORY)

	endwhile ()
	
	set (GITDIR "${GITDIR}" CACHE PATH "Path to the top-level git directory")
	
	
endif ()

#message ("petalinux.cmake: now GITDIR=${GITDIR}") 
list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)


##----------------------------------------------------------------------------------------------------------------------
## Set target
set (TARGET petalinux)

##----------------------------------------------------------------------------------------------------------------------
## Include the common settings/macros
include (settings)


##----------------------------------------------------------------------------------------------------------------------
## Environment
set (LOCAL_INSTALL_DIR ${GITDIR}/buildTools/sysroot)

# Load in ros makefile settings
readMakeSettings (${TARGET} ${ROS_MAKE_PATHS})
# Sets:
#TOOLCHAIN_LINUX_DIR=petalinux-2019.2
#TOOLCHAIN_TARGET=aarch64-xilinx-linux
#TOOLCHAIN_DIR=/disks/disk1/data/ros/build/ZCU111/Linux-petalinux/dev-install/sysroot
#TOOLCHAIN_LIBS=/disks/disk1/data/ros/build/ZCU111/Linux-petalinux/dev-install/sysroot/usr/lib
#TOOLCHAIN_BIN=/disks/disk1/data/ros/build/ZCU111/Linux-petalinux/dev-install/usr/bin/aarch64-xilinx-linux
#TOOLCHAIN_PREFIX=/disks/disk1/data/ros/build/ZCU111/Linux-petalinux/dev-install/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-
#TOOLS_INSTALLDIR=/disks/disk1/data/ros/build/ZCU111/Linux-petalinux/install
#DEVTOOLS_INSTALLDIR=/disks/disk1/data/ros/build/ZCU111/Linux-petalinux/dev-install
#TOOLCHAIN_SYSROOT=/disks/disk1/data/ros/build/ZCU111/Linux-petalinux/dev-install/sysroot

message(STATUS "TOOLCHAIN_PREFIX=${TOOLCHAIN_PREFIX}")
message(STATUS "DEVTOOLS_INSTALLDIR=${DEVTOOLS_INSTALLDIR}")


string(TOUPPER ${TOOLCHAIN_LINUX_DIR} TOOLCHAIN_VER)
string(REPLACE "-" "" TOOLCHAIN_VER ${TOOLCHAIN_VER})
string(REPLACE "." "_" TOOLCHAIN_VER ${TOOLCHAIN_VER})
message(STATUS "TOOLCHAIN_VER=${TOOLCHAIN_VER}")

# Load in ros latest build settings
readMakePkgSettings (${TARGET}-build  ${ROS_MAKE_PATHS})


## Settings
set (BUILD_COVERAGE 0 CACHE STRING "Build with coverage disabled" FORCE)
set (OFF_TARGET 0 CACHE STRING "Off target build - this build is on target" FORCE)

##----------------------------------------------------------------------------------------------------------------------
## Set up cross-compiler for PPC GCC build
set (CMAKE_SYSTEM_NAME Linux)
set (CMAKE_C_COMPILER  "${TOOLCHAIN_PREFIX}gcc")
set (CMAKE_CXX_COMPILER  "${TOOLCHAIN_PREFIX}g++")
set (CMAKE_FIND_ROOT_PATH
	${TOOLCHAIN_SYSROOT}
	${DEVTOOLS_INSTALLDIR}
	${EXTRA_FIND_ROOT_PATH}
)
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

##----------------------------------------------------------------------------------------------------------------------
## Set up link flags
set (LINK_FLAGS "  --sysroot=${DEVTOOLS_INSTALLDIR}/sysroot -lmetal -lrfdc")

##----------------------------------------------------------------------------------------------------------------------
## Set up compiler flags
#set (COMPILE_FLAGS "-O2 -g -Wno-error=misleading-indentation -Wno-error=stringop-truncation --sysroot=${DEVTOOLS_INSTALLDIR}/sysroot")
set (COMPILE_FLAGS "-O2 -g -Wno-error=misleading-indentation --sysroot=${DEVTOOLS_INSTALLDIR}/sysroot")
add_compile_definitions(${TOOLCHAIN_VER}=1)

##----------------------------------------------------------------------------------------------------------------------
#get_property(IS_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE)
#if (IS_IN_TRY_COMPILE)
#	message(STATUS "IN trying to compile...")
#	add_compile_options(--sysroot=${DEVTOOLS_INSTALLDIR}/sysroot)
#	add_link_options(--sysroot=${DEVTOOLS_INSTALLDIR}/sysroot)
#endif()

##----------------------------------------------------------------------------------------------------------------------
## Compiler/Linker flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILE_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  ${LINK_FLAGS} ")


