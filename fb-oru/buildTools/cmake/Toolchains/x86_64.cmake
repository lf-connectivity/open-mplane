##======================================================================================================================
## Settings for local builds
##
## Useage: cmake -DCMAKE_TOOLCHAIN_FILE=~/git/buildTools/cmake/Toolchains/x86_64.cmake <src>
##======================================================================================================================

message ("x86_64.cmake: GITDIR=${GITDIR} PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")

##----------------------------------------------------------------------------------------------------------------------
if (NOT GITDIR)

	get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)

	# Given a source path, keep stripping off directories until the path is the top-level git path
	# in which we expect at least buildTools directory to be present
	while (NOT IS_DIRECTORY ${GITDIR}/buildTools)

		get_filename_component (GITDIR ${GITDIR} DIRECTORY)

	endwhile ()

message("x86_64.cmake: set GITDIR=${GITDIR}")
	set (GITDIR "${GITDIR}" CACHE PATH "Path to the top-level git directory")

endif ()

message ("x86_64.cmake: now GITDIR=${GITDIR}")
list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)

##----------------------------------------------------------------------------------------------------------------------
## Set target
set (TARGET x86_64)

##----------------------------------------------------------------------------------------------------------------------
## Include the common settings/macros
include (settings)


##----------------------------------------------------------------------------------------------------------------------
## Environment
set (LOCAL_INSTALL_DIR ${GITDIR}/buildTools/sysroot)



# Strip off the final dir to find ROS top-level
#
get_filename_component(ROS_TOP ${ROS_BUILDDIR} DIRECTORY)

message(STATUS "x86_64.cmake: ROS_PATH=${ROS_PATH}")
message(STATUS "x86_64.cmake: ROS_BUILDDIR=${ROS_BUILDDIR}")
message(STATUS "x86_64.cmake: ROS_TOP=${ROS_TOP}")
message(STATUS "x86_64.cmake: calling readMakeSettings (${TARGET} ${ROS_BUILDDIR}/HOST/make)")


# Load in ros makefile settings
readMakeSettings (${TARGET} ${ROS_BUILDDIR}/HOST/make)
set (TOOLCHAIN_SYSROOT ${TOOLCHAIN_DIR}/${TOOLCHAIN_TARGET}/sysroot)

# Settings
getCachedEnvVar (BUILD_COVERAGE 1 "Build with coverage enabled")
set (OFF_TARGET 1 CACHE STRING "Off target build" FORCE)

##----------------------------------------------------------------------------------------------------------------------
## Set up cross-compiler for local GCC build
set (CMAKE_SYSTEM_NAME Linux)
set (CMAKE_C_COMPILER  ${TOOLCHAIN_DIR}/bin/${TOOLCHAIN_TARGET}-gcc)
set (CMAKE_CXX_COMPILER  ${TOOLCHAIN_DIR}/bin/${TOOLCHAIN_TARGET}-g++)

if (${SPECIAL_BUILD})

set (CMAKE_FIND_ROOT_PATH
	${TOOLCHAIN_SYSROOT}
	${DEVTOOLS_INSTALLDIR}
	${EXTRA_FIND_ROOT_PATH}
)

else()
set (CMAKE_FIND_ROOT_PATH
	${TOOLCHAIN_SYSROOT}
	${DEVTOOLS_INSTALLDIR}
	${LOCAL_INSTALL_DIR}
	${EXTRA_FIND_ROOT_PATH}
)
endif()

set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#message(STATUS "x86_64.cmake: EXTRA_FIND_ROOT_PATH=${EXTRA_FIND_ROOT_PATH}")
#message(STATUS "x86_64.cmake: CMAKE_FIND_ROOT_PATH=${CMAKE_FIND_ROOT_PATH}")
#message(STATUS "x86_64.cmake: CMAKE_INCLUDE_PATH=${CMAKE_INCLUDE_PATH}")

#message(STATUS "x86_64.cmake: SPECIAL_BUILD=${SPECIAL_BUILD}")

##----------------------------------------------------------------------------------------------------------------------
## Set up link flags
if (${SPECIAL_BUILD})
set (LINK_FLAGS "-static-libstdc++")
else()
set (LINK_FLAGS "-static-libstdc++")
set (LINK_FLAGS "${LINK_FLAGS} -Wl,-rpath=${LOCAL_INSTALL_DIR}/lib")
set (LINK_FLAGS "${LINK_FLAGS} -L${LOCAL_INSTALL_DIR}/lib")
set (LINK_FLAGS "${LINK_FLAGS} -Wl,-rpath=${DEVTOOLS_INSTALLDIR}/lib")
set (LINK_FLAGS "${LINK_FLAGS} -L${DEVTOOLS_INSTALLDIR}/lib")
set (LINK_FLAGS "${LINK_FLAGS} -Wl,-rpath=${TOOLCHAIN_DIR}/${TOOLCHAIN_TARGET}/lib64")
set (LINK_FLAGS "${LINK_FLAGS} -L${TOOLCHAIN_DIR}/${TOOLCHAIN_TARGET}/lib64")
set (LINK_FLAGS "${LINK_FLAGS} -Wl,-rpath=${TOOLCHAIN_SYSROOT}/lib64")
set (LINK_FLAGS "${LINK_FLAGS} -L${TOOLCHAIN_SYSROOT}/lib64")
set (LINK_FLAGS "${LINK_FLAGS} -Wl,-dynamic-linker=${TOOLCHAIN_SYSROOT}/lib/ld-linux-x86-64.so.2")
set (LINK_FLAGS "${LINK_FLAGS} -pthread")
endif()

#message(STATUS "x86_64.cmake: LINK_FLAGS=${LINK_FLAGS}")

##----------------------------------------------------------------------------------------------------------------------
## Set up compiler flags
if (${SPECIAL_BUILD})
set (COMPILE_FLAGS "")
set (COMPILE_FLAGS "${COMPILE_FLAGS} -pthread")
else()
set (COMPILE_FLAGS "-O0 -g3")
set (COMPILE_FLAGS "${COMPILE_FLAGS} -I${LOCAL_INSTALL_DIR}/include")
set (COMPILE_FLAGS "${COMPILE_FLAGS} -DROS_TOP='\"${ROS_TOP}\"'")
set (COMPILE_FLAGS "${COMPILE_FLAGS} -DOFF_TARGET")
set (COMPILE_FLAGS "${COMPILE_FLAGS} -DOFFTARGET_CFG_DIR='\"${GITDIR}/hardware/common/fpga/cfg\"'") # used by fpga emulator
set (COMPILE_FLAGS "${COMPILE_FLAGS} -pthread")
endif()

set (COMPILE_FLAGS "${COMPILE_FLAGS} -Wno-error=misleading-indentation")

#message(STATUS "x86_64.cmake: COMPILE_FLAGS=${COMPILE_FLAGS}")

# coverage
if (${BUILD_COVERAGE})
	set (COMPILE_FLAGS "-pg --coverage ${COMPILE_FLAGS}")
	set (LINK_FLAGS "-pg --coverage ${LINK_FLAGS}")
endif (${BUILD_COVERAGE})

##----------------------------------------------------------------------------------------------------------------------
## Testing

# Allow testing for host builds
enable_testing()

##----------------------------------------------------------------------------------------------------------------------
## Compiler/Linker flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILE_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  ${LINK_FLAGS} ")


