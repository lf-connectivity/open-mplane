##======================================================================================================================
## Settings for local builds
##
## Useage: cmake -DCMAKE_TOOLCHAIN_FILE=~/git/buildTools/cmake/Toolchains/embedded/x86_64.cmake <src>
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
if (NOT GITDIR)

	get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
	
	# Given a source path, keep stripping off directories until the path is the top-level git path
	# in which we expect at least buildTools directory to be present
	while (NOT IS_DIRECTORY ${GITDIR}/buildTools)
		
		get_filename_component (GITDIR ${GITDIR} DIRECTORY)

	endwhile ()
	
endif ()

list(APPEND CMAKE_MODULE_PATH "${GITDIR}/buildTools/cmake/Toolchains")

# use the normal toolchain
include(x86_64)
