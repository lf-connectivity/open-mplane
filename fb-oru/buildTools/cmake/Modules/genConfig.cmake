##======================================================================================================================
## Cmake - creates config header
##
##======================================================================================================================
message(STATUS "SDP genConfig: START ${PROJECT_BINARY_DIR}")

# Override these values from the current environment settings (if set)
set(envBuildNum $ENV{BUILD_NUMBER})
if (DEFINED envBuildNum)
    set(BUILD_NUMBER $ENV{BUILD_NUMBER})
endif()

set(envBuildVer $ENV{BUILD_VERSION})
if (DEFINED envBuildVer)
    set(BUILD_VERSION $ENV{BUILD_VERSION})
endif()

set(envBuildVer $ENV{BUILD_FPGA_PART})
if (DEFINED envBuildVer)
    set(BUILD_FPGA_PART $ENV{BUILD_FPGA_PART})
endif()

set(envBuildVer $ENV{BUILD_FPGA_BUILD})
if (DEFINED envBuildVer)
    set(BUILD_FPGA_BUILD $ENV{BUILD_FPGA_BUILD})
endif()

set (BUILD_LAB 0)
set(envBuildVer $ENV{BUILD_LAB})
if (DEFINED envBuildVer)
    set(BUILD_LAB $ENV{BUILD_LAB})
endif()

set(envBuildVer $ENV{BUILD_MAKEFILE_VERSION})
if (DEFINED envBuildVer)
    set(BUILD_MAKEFILE_VERSION $ENV{BUILD_MAKEFILE_VERSION})
endif()

set(envBuildVer $ENV{FEATURE_LIST})
if (DEFINED envBuildVer)
    set(FEATURE_LIST $ENV{FEATURE_LIST})
endif()

set(envBuildVer $ENV{TIF_FEATURE_LIST})
if (DEFINED envBuildVer)
    set(TIF_FEATURE_LIST $ENV{TIF_FEATURE_LIST})
endif()

#message(STATUS "genConfig: FEATURE_LIST=${FEATURE_LIST}")
if ("${FEATURE_LIST}" STREQUAL "")
    set (FEATURES "")
else()
    string (REPLACE ":" ";" FEATURES ${FEATURE_LIST})
endif()
message(STATUS "SDP genConfig: FEATURES=${FEATURES}")

## Stop now if no features
if ("${FEATURES}" STREQUAL "")
	message(STATUS "SDP Skip config generation")
	return()
endif ()

#message(STATUS "genConfig: TIF_FEATURE_LIST=${TIF_FEATURE_LIST}")
if ("${TIF_FEATURE_LIST}" STREQUAL "")
    set (TIF_FEATURES "")
else()
    string (REPLACE ":" ";" TIF_FEATURES ${TIF_FEATURE_LIST})
endif()
#message(STATUS "genConfig: TIF_FEATURES=${TIF_FEATURES}")

# Process list
get_cmake_property(_variableNames VARIABLES)
set (BUILD_FEATURES_TEXT "")
foreach (feat ${FEATURES})

    ## Update variables
    set (FEAT_${feat} $ENV{FEAT_${feat}})
    set (BUILD_FEATURES_TEXT "${BUILD_FEATURES_TEXT}${feat}=$ENV{FEAT_${feat}} ")

message(STATUS "genConfig: FEAT_${feat} ${FEAT_${feat}}")

endforeach()
foreach (tif ${TIF_FEATURES})

    # Special case where value is boolean (TRUE/FALSE)
    set (value $ENV{TIF_${tif}})
    set (BUILD_FEATURES_TEXT "${BUILD_FEATURES_TEXT}${tif}=$ENV{${tif}} ")

endforeach()



## SDP - Disable this to minimise updates to the generated config.h files (which then reduces the build time)
## vvvvv
##
# Get the repository settings
#file(GLOB dirs RELATIVE ${GITDIR} ${GITDIR}/*)
set(REPOLIST "")
#foreach(dir ${dirs})
#    if (IS_DIRECTORY ${GITDIR}/${dir})
###        message(STATUS "genConfig : dir=${dir}")
#        execute_process(
#            COMMAND git rev-parse HEAD
#            WORKING_DIRECTORY ${GITDIR}/${dir}
#            OUTPUT_VARIABLE git
#            ERROR_VARIABLE giterr
#            OUTPUT_STRIP_TRAILING_WHITESPACE
#        )
#
#        if (git)
#            list (APPEND REPOLIST "${dir}:${git}")
#        endif()
#    endif()
#endforeach()
##
## ^^^^

#message(STATUS "REPOLIST=${REPOLIST}")
#message(STATUS "genConfig: ${PROJECT_BINARY_DIR}/config.h : TARGET=${TARGET} BUILD_FPGA_BUILD=${BUILD_FPGA_BUILD} PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

#if (${TARGET} STREQUAL "x86_64")
#    set(REPOLIST "")
#endif()

## Get creation date/time
## SDP - Disable time part of timestamp to minimise updates to config.h files (which then reduces the build time)
## vvvvv
##string(TIMESTAMP CREATE_DATETIME "%d/%m/%Y %H:%M:%S")
string(TIMESTAMP CREATE_DATETIME "%d/%m/%Y 00:00:00")
## ^^^^^

## Features
message(STATUS "SDP FEATURES=${FEATURES}")
set (FEATURES_DEFINES "")
foreach (feat ${FEATURES})

    set (FEAT_${feat} $ENV{FEAT_${feat}})
    
    # convert any problem chars to '_' for C++
    set (feat_value ${FEAT_${feat}})
	string(REGEX REPLACE "[-\\/ ]+" "_" feat_value ${feat_value})
    message(STATUS "genConfig: Feature define: ${feat_value}")
    
    set (FEATURES_DEFINES "${FEATURES_DEFINES}#define FEAT_${feat}_${feat_value}\n")

endforeach()

## TIF Feature-based settings
message(STATUS "TIF_FEATURES=${TIF_FEATURES}")
set (TIF_FEATURE_DEFINES "")
foreach (tif ${TIF_FEATURES})

    set (TIF_FEATURE_DEFINES "${TIF_FEATURE_DEFINES}#define ${tif}  $ENV{${tif}}\n")

endforeach()


##----------------------------------------------------------------------------------------------------------------------
configure_file (
	"${GITDIR}/buildTools/cmake/inc/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	@ONLY
)

#configure_file (
#	"${GITDIR}/buildTools/cmake/inc/config.h.in"
#	"${PROJECT_BINARY_DIR}/config.h.new"
#	@ONLY
#)
#
#execute_process( COMMAND ${CMAKE_COMMAND} -E compare_files ${PROJECT_BINARY_DIR}/config.h.new ${PROJECT_BINARY_DIR}/config.h
#                 RESULT_VARIABLE compare_result
#)
#if( compare_result EQUAL 0)
#    message("SDP The files are identical.")
#elseif( compare_result EQUAL 1)
#    message("SDP The files are different.")
#else()
#    message("SDP Error while comparing the files.")
#endif()
#
#execute_process(
#    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_BINARY_DIR}/config.h.new ${PROJECT_BINARY_DIR}/config.h
#)

message(STATUS "SDP genConfig: END ${PROJECT_BINARY_DIR}")
