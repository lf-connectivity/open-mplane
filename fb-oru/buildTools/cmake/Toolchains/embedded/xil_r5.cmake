##======================================================================================================================
## Settings for ARM R5 builds
##
## Needs the following variables defined:
##
## R5	- R5 instance number (0|1)
##
## Needs the following environment variables defined:
##
## PETALINUX	- path to petalinux installation
##
##======================================================================================================================

message ("xil_r5.cmake: GITDIR=${GITDIR} PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}") 
message ("xil_r5.cmake: R5=${R5} PETALINUX=$ENV{PETALINUX}") 
message ("xil_r5.cmake: CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}") 


set (GITDIR "${GITDIR}" CACHE PATH "Path to the top-level git directory")

message ("xil_r5.cmake: now GITDIR=${GITDIR}") 
list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)


##----------------------------------------------------------------------------------------------------------------------
## Set target
set (TARGET xil_r5_${R5})

##----------------------------------------------------------------------------------------------------------------------
## Include the common settings/macros
include (settings)


##----------------------------------------------------------------------------------------------------------------------
## Environment


##----------------------------------------------------------------------------------------------------------------------
## Set up cross-compiler for PPC GCC build
set (CMAKE_SYSTEM_NAME "Generic" CACHE STRING "")

set (CMAKE_SYSTEM_PROCESSOR "arm" CACHE STRING "")
set (MACHINE "zynqmp_r5")
set (CROSS_PREFIX "armr5-none-eabi-" CACHE STRING "")

set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER CACHE STRING "")
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER CACHE STRING "")
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER CACHE STRING "")

set (PETALINUX_DIR $ENV{PETALINUX} CACHE STRING "")
set (BSP_DIR ${BSP} CACHE STRING "")

string(REGEX REPLACE "/$" "" PETALINUX_DIR ${PETALINUX_DIR})

# Check for Petalinux 2018.* R5 toolset
if (EXISTS ${PETALINUX_DIR}/tools/linux-i386/gcc-arm-none-eabi-r5)
	set (TOOLCHAIN_DIR ${PETALINUX_DIR}/tools/linux-i386/gcc-arm-none-eabi-r5)
endif()

# Check for Petalinux 2019.* R5 toolset
if (EXISTS ${PETALINUX_DIR}/tools/xsct/gnu/armr5/lin/gcc-arm-none-eabi/bin)
	set (TOOLCHAIN_DIR ${PETALINUX_DIR}/tools/xsct/gnu/armr5/lin/gcc-arm-none-eabi)
endif()

set (CMAKE_C_COMPILER  ${TOOLCHAIN_DIR}/bin/${CROSS_PREFIX}gcc)
set (CMAKE_CXX_COMPILER  ${TOOLCHAIN_DIR}/bin/${CROSS_PREFIX}g++)

## Need to add in some default libs
set (TOOLCHAIN_LINK_LIBS "-lgcc -lc -lm")


##----------------------------------------------------------------------------------------------------------------------
## Set up link flags
set (CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16")

##----------------------------------------------------------------------------------------------------------------------
## Set up compiler flags
set (CMAKE_C_FLAGS "-O2 -mcpu=cortex-r5 -g -DARMR5 -DR5=${R5} -Wall -Wextra -mfloat-abi=hard -mfpu=vfpv3-d16 -Wno-error=cast-function-type")

add_compile_definitions(R5=${R5})

