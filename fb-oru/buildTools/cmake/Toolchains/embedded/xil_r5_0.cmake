##======================================================================================================================
## Settings for ARM R5-0 builds
##
## Useage: cmake -DCMAKE_TOOLCHAIN_FILE=~/git/buildTools/cmake/Toolchains/embedded/xil_r5_0.cmake <src>
##
## Needs the following environment variables defined:
##
## PETALINUX	- path to petalinux installation
##
##======================================================================================================================

message ("xil_r5_0.cmake: GITDIR=${GITDIR} PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}") 

##----------------------------------------------------------------------------------------------------------------------
if (NOT GITDIR)

	get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
	
	# Given a source path, keep stripping off directories until the path is the top-level git path
	# in which we expect at least buildTools directory to be present
	while (NOT IS_DIRECTORY ${GITDIR}/buildTools)
		
		get_filename_component (GITDIR ${GITDIR} DIRECTORY)

	endwhile ()
	
endif ()

list(APPEND CMAKE_MODULE_PATH "${GITDIR}/buildTools/cmake/Toolchains/embedded")

set (R5 "0")
include(xil_r5)
