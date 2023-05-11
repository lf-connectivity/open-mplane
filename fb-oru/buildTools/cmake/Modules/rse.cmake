##======================================================================================================================
## RSE Shared CMake functions, Macros, and settings
##
##======================================================================================================================

# Include guard
if (_INCLUDED_RSE)
	return ()
endif (_INCLUDED_RSE)
set (_INCLUDED_RSE 1)

##======================================================================================================================
## MACROS/FUNCTIONS
include (settings)
include (rse_functions)

## Features
foreach (feat ${FEATURES})
    include (${feat})
endforeach()

##======================================================================================================================
## SETTINGS

##----------------------------------------------------------------------------------------------------------------------
## Config file

## create a config file in each directory anyway
#configure_file (
#	"${GITDIR}/buildTools/cmake/inc/config.h.in"
#	"${PROJECT_BINARY_DIR}/config.h"
#)

#message(STATUS "FPGA=${BUILD_FPGA_BUILD}")

addVersionConfig()

includeDirectories(${PROJECT_BINARY_DIR})
#include_directories(${PROJECT_BINARY_DIR})

##----------------------------------------------------------------------------------------------------------------------
## ROS built libraries include location
if (NOT ${DEVTOOLS_INSTALLDIR} STREQUAL "")
includeDirectories( ${DEVTOOLS_INSTALLDIR}/include )
endif()

##----------------------------------------------------------------------------------------------------------------------
# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

##----------------------------------------------------------------------------------------------------------------------
## Common compile settings

# Compiler - COMPILE_FLAGS is set up by the appropriate host/ppc cmake file

execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE CXX_VERSION)
if ( ${CXX_VERSION} GREATER_EQUAL "7.0.0" )

	# latest compiler
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fmessage-length=0 -std=gnu++17 -pthread")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=misleading-indentation")

else ()

	# old compiler
	message(WARNING "Old compiler detected, switching to C++14")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fmessage-length=0 -std=gnu++14 -pthread")

endif ()

# Turns out lots of our gtests incorrectly compare signed with unsigned ints
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=sign-compare")

## C compile
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -fmessage-length=0")

## Add definitions for the build parameters
## NOTE: Some of these are already created in the generated config.h file
#add_compile_definitions(BUILD_BOARD_${BUILD_BOARD})
#add_compile_definitions(BUILD_APPLICATION_${BUILD_APPLICATION})
#add_compile_definitions(BUILD_CUSTOMER_${BUILD_CUSTOMER})
add_compile_definitions(BUILD_DUPLEX_${BUILD_DUPLEX})
add_compile_definitions(BUILD_IF_${BUILD_FIBRE_INTERFACE})


##----------------------------------------------------------------------------------------------------------------------
## Show the settings
logMessage (
"==========================================================="
"BUILD SETTINGS"
"   "
"Target.............: ${TARGET}"
"Application........: ${BUILD_APPLICATION}"
"Customer...........: ${BUILD_CUSTOMER}"
"Board..............: ${BUILD_BOARD}"
"Duplex.............: ${BUILD_DUPLEX}"
"Fibre I/F..........: ${BUILD_FIBRE_INTERFACE}"
"Build..............: ${BUILD_NUMBER}"
"Version............: ${BUILD_VERSION}"
"FPGA Part..........: ${BUILD_FPGA_PART}"
"FPGA Build.........: ${BUILD_FPGA_BUILD}"
"FPGA Vendor........: ${BUILD_FPGA_VENDOR}"
"   "
"-----------------------------------------------------------"
"PROJECT ${PROJECT_NAME} v${version}"
"   "
"Source Dir.........: ${CMAKE_SOURCE_DIR}"
"Build Dir..........: ${CMAKE_BINARY_DIR}"
"C++ Compiler.......: ${CMAKE_CXX_COMPILER}"
"Compile flags......: ${CMAKE_CXX_FLAGS}"
"Link flags.........: ${CMAKE_EXE_LINKER_FLAGS}"
"GITDIR.............: ${GITDIR}"
"Local Sysroot......: ${LOCAL_INSTALL_DIR}"
"ROS path...........: ${ROS_BUILDDIR}"
"TOOLCHAIN_SYSROOT..: ${TOOLCHAIN_SYSROOT}"
"==========================================================="
)

