##======================================================================================================================
## RSE CMake settings
##
##======================================================================================================================

# Include guard
if (_INCLUDED_SETTINGS)
	return ()
endif (_INCLUDED_SETTINGS)
set (_INCLUDED_SETTINGS 1)


##----------------------------------------------------------------------------------------------------------------------
## logDebug( <message> ... )
##
## Function that displays the message(s) if $DEBUG_CMAKLIST is true
##
function (logDebug)

	if (DEBUG_CMAKELIST)
		foreach (msg ${ARGV})
			message (STATUS "DEBUG: ${msg}")
		endforeach ()
	endif()

endfunction (logDebug)

##----------------------------------------------------------------------------------------------------------------------
## getEnvVar( <var> <default> )
##
## Macro that creates a new variable based on the current environment variable value with the same name. If the env
## var is not set then uses the specified default value
##
macro (getEnvVar var default)

	set (${var} $ENV{${var}})
	logDebug("getEnvVar(${var}) ENV=${${var}} (default=${default})")
	if (NOT DEFINED ${var})
		set (${var} ${default})
		logDebug("getEnvVar(${var}) : set default=${default}")
	endif()

endmacro (getEnvVar)

##----------------------------------------------------------------------------------------------------------------------
## getCachedEnvVar( <var> <default> <description> )
##
## Macro that first checks for a set environment variable and if present uses that value. If not it uses the cached variable
## or default if cached variable isn't set. The final value is then saved in the cache
##
macro (getCachedEnvVar var default description)

	set (envVar $ENV{${var}})
	logDebug("getCachedEnvVar(${var}) ENV=${envVar} (default=${default})")
	if (DEFINED envVar)

		set (${var} ${envVar})
		logDebug("getCachedEnvVar(${var}) = ENV ${envVar}")

	else()
	    # See if got cached value
    	if (NOT DEFINED ${var})

    		logDebug("getCachedEnvVar(${var}) : getEnvVar default = ${default}")

    		# get the variable
    		getEnvVar( ${var} "${default}" )

    	endif()
	endif()

	# save to the cache
	set (val ${${var}})
	if (DEFINED val)
		set (${var} ${${var}} CACHE STRING "${description}" FORCE)
		logDebug("Saved ${var} = ${${var}} to cache")
	endif()
	
endmacro (getCachedEnvVar)

##----------------------------------------------------------------------------------------------------------------------
## readMakeSettings( <target>, <paths> )
##
## Macro that reads in the ros make settings file and sets the paths accordingly.
##
function (readMakeSettings target)

logDebug ("readMakeSettings ${target} ${ARGN}")

	find_file (mkSettingsFilename NAMES ${target}.mk PATHS ${ARGN} NO_DEFAULT_PATH)
	if (${mkSettingsFilename} STREQUAL "mkSettingsFilename-NOTFOUND")
	    message(FATAL_ERROR "Unable to read ROS make include file for ${target}. Have you built ros for ${target} yet?")
	endif()

logDebug ("readMakeSettings mkSettingsFilename=${mkSettingsFilename}")

	set (contents "")
	file (STRINGS ${mkSettingsFilename} contents)

	foreach (varVal ${contents})
		string(FIND ${varVal} "=" pos)
		string(SUBSTRING ${varVal} 0 ${pos} var)
		math (EXPR pos "${pos}+1")
		string(SUBSTRING ${varVal} ${pos} -1 val)
		logDebug ("varVal: ${var} = ${val}")

		# Define this variable in the caller's scope
		set (${var} ${val} PARENT_SCOPE)
	endforeach ()

endfunction (readMakeSettings)

##----------------------------------------------------------------------------------------------------------------------
## readMakePkgSettings( <target>, <paths> )
##
## Macro that reads in the ros make settings file and sets the paths accordingly.
##
function (readMakePkgSettings target)

logDebug ("readMakePkgSettings ${target} ${ARGN}")

	find_file (mkPkgFilename NAMES ${target}.mk PATHS ${ARGN} NO_DEFAULT_PATH)
	if (${mkPkgFilename} STREQUAL "mkPkgFilename-NOTFOUND")
	    message(FATAL_ERROR "Unable to read ROS make include file for ${target}. Have you built ros for ${target} yet?")
	endif()

logDebug ("readMakePkgSettings mkPkgFilename=${mkPkgFilename}")

	set (contents "")
	file (STRINGS ${mkPkgFilename} contents)

	foreach (varVal ${contents})
		string(FIND ${varVal} "=" pos)
		string(SUBSTRING ${varVal} 0 ${pos} var)
		math (EXPR pos "${pos}+1")
		string(SUBSTRING ${varVal} ${pos} -1 val)
		logDebug ("varVal: ${var} = ${val}")

		# Define this variable in the caller's scope
		set (${var} ${val} PARENT_SCOPE)
	endforeach ()

endfunction (readMakePkgSettings)

##----------------------------------------------------------------------------------------------------------------------
## readVariablesFile( <filename> )
##
## Function that reads in a text file containing variable=value pairs and loads the variables into the parent scope
##
function (readVariablesFile filename)

    logDebug("readVariables(${filename})")

	file (STRINGS ${filename} contents)

	foreach (varVal ${contents})
		string(FIND ${varVal} "=" pos)
		string(SUBSTRING ${varVal} 0 ${pos} var)
		math (EXPR pos "${pos}+1")
		string(SUBSTRING ${varVal} ${pos} -1 val)
		logDebug ("varVal: ${var} = ${val}")

		# Define this variable in the caller's scope
		set (${var} ${val} PARENT_SCOPE)
	endforeach ()

endfunction (readVariablesFile)


##----------------------------------------------------------------------------------------------------------------------
## readFpgaManifest( <fpgaTgz> )
##
## Function that extracts the fpga manifest and sets the parent variables BUILD_FPGA_PART and BUILD_FPGA_BUILD
##
function (readFpgaManifest fpgaTgz)

    if (fpgaTgz)

        set (TEMP_DIR "${CMAKE_BINARY_DIR}/tmp")
#        message( "Reading FPGA manifest into ${TEMP_DIR}" )

        ## Set up a temp area
        file(MAKE_DIRECTORY ${TEMP_DIR})

        execute_process(
            COMMAND rm -f ${TEMP_DIR}/manifest
            WORKING_DIRECTORY ${TEMP_DIR}
        )
        execute_process(
            COMMAND tar xf ${fpgaTgz} -O manifest
            OUTPUT_FILE ${TEMP_DIR}/manifest
            WORKING_DIRECTORY ${TEMP_DIR}
        )
        readVariablesFile( ${TEMP_DIR}/manifest )

        # Manifest will contain something like:
        #Enclosure=DIT
        #RadioBoard=c2g6_Phoenix
        #RxPorts=2
        #TxPorts=2
        #FpgaModel=XC7K160T
        #FpgaPartName=xc7k160t-ffg676-2
        #BuildNumber=4991
        #Cutdown=no
        #AirStandard=
        #Fibre=CPRI
        #IseVerName=ise14_6

        set (BUILD_FPGA_PART ${FpgaPartName} PARENT_SCOPE)
        set (BUILD_FPGA_BUILD ${BuildNumber} PARENT_SCOPE)

        # Clean up
        execute_process(
            COMMAND rm -f ${TEMP_DIR}/manifest
            WORKING_DIRECTORY ${TEMP_DIR}
        )

    endif ()

endfunction (readFpgaManifest)


##----------------------------------------------------------------------------------------------------------------------
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "VAR ${_variableName}=${${_variableName}}")
#endforeach()
#
#execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "environment")

##----------------------------------------------------------------------------------------------------------------------
## Settings
getCachedEnvVar (BUILD_BOARD "ETNA" "Board")
getCachedEnvVar (BUILD_APPLICATION "FTU" "Application")
getCachedEnvVar (BUILD_CUSTOMER "AXIS" "Customer")
getCachedEnvVar (BUILD_DUPLEX "FDD" "Duplex")
getCachedEnvVar (BUILD_FIBRE_INTERFACE "CPRI" "Fibre Interface")
getCachedEnvVar (BUILD_FPGA_VENDOR "xilinx" "FPGA vendor name")
getCachedEnvVar (BUILD_PRODUCT_CODE "ABC-1234" "Product Code")
getCachedEnvVar (BUILD_VENDOR_CODE "AX" "Vendor Code")
getCachedEnvVar (BUILD_SUFFIX "" "Suffix appended to build name. Variant on standard build using the same software, just different build settings")

getEnvVar (BUILD_TEST_SHARED "0")
getEnvVar (BUILD_TYPE "radio")

getEnvVar (BUILD_NUMBER "1")
getEnvVar (BUILD_VERSION "0.0")
getEnvVar (BUILD_MAKEFILE_VERSION "0")

set (BUILD_APPNAME ${BUILD_CUSTOMER}-${BUILD_APPLICATION})
set (BUILD_BOARDAPPNAME ${BUILD_BOARD}-${BUILD_APPNAME})

#message(STATUS "++ BUILD_APPLICATION=${BUILD_APPLICATION}")
#message(STATUS "++ BUILD_BOARD='${BUILD_BOARD}'")
#message(STATUS "++ BUILD_CUSTOMER='${BUILD_CUSTOMER}'")
#message(STATUS "++ BUILD_DUPLEX='${BUILD_DUPLEX}'")
#message(STATUS "++ BUILD_FIBRE_INTERFACE='${BUILD_FIBRE_INTERFACE}'")

##----------------------------------------------------------------------------------------------------------------------
## FPGA (if specified)
getEnvVar (BUILD_FPGA_TARBALL "")
set (BUILD_FPGA_PART "")
set (BUILD_FPGA_BUILD "")

# Read the manifest if we can
if (BUILD_FPGA_TARBALL)
    readFpgaManifest(${BUILD_FPGA_TARBALL})
endif ()

##----------------------------------------------------------------------------------------------------------------------
## Re-create environment
set (BUILD_VARS "BUILD_BOARD=${BUILD_BOARD}")
set (BUILD_VARS "${BUILD_VARS} BUILD_APPLICATION=${BUILD_APPLICATION} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_CUSTOMER=${BUILD_CUSTOMER} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_DUPLEX=${BUILD_DUPLEX} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_FIBRE_INTERFACE=${BUILD_FIBRE_INTERFACE} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_NUMBER=${BUILD_NUMBER} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_VERSION=${BUILD_VERSION} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_PRODUCT_CODE=${BUILD_PRODUCT_CODE} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_VENDOR_CODE=${BUILD_VENDOR_CODE} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_SUFFIX=${BUILD_SUFFIX} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_FPGA_VENDOR=${BUILD_FPGA_VENDOR} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_FPGA_TARBALL=${BUILD_FPGA_TARBALL} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_TEST_SHARED=${BUILD_TEST_SHARED} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_MAKEFILE_VERSION=${BUILD_MAKEFILE_VERSION} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_TYPE=${BUILD_TYPE} ")

set (BUILD_CMAKE_VARS "-DBUILD_BOARD=${BUILD_BOARD}")
list (APPEND BUILD_CMAKE_VARS -DBUILD_APPLICATION=${BUILD_APPLICATION})
list (APPEND BUILD_CMAKE_VARS -DBUILD_CUSTOMER=${BUILD_CUSTOMER})
list (APPEND BUILD_CMAKE_VARS -DBUILD_DUPLEX=${BUILD_DUPLEX})
list (APPEND BUILD_CMAKE_VARS -DBUILD_FIBRE_INTERFACE=${BUILD_FIBRE_INTERFACE})
list (APPEND BUILD_CMAKE_VARS -DBUILD_NUMBER=${BUILD_NUMBER})
list (APPEND BUILD_CMAKE_VARS -DBUILD_VERSION=${BUILD_VERSION})
list (APPEND BUILD_CMAKE_VARS -DBUILD_PRODUCT_CODE=${BUILD_PRODUCT_CODE})
list (APPEND BUILD_CMAKE_VARS -DBUILD_VENDOR_CODE=${BUILD_VENDOR_CODE})
list (APPEND BUILD_CMAKE_VARS -DBUILD_SUFFIX=${BUILD_SUFFIX})
list (APPEND BUILD_CMAKE_VARS -DBUILD_FPGA_VENDOR=${BUILD_FPGA_VENDOR})
list (APPEND BUILD_CMAKE_VARS -DBUILD_FPGA_TARBALL=${BUILD_FPGA_TARBALL})
list (APPEND BUILD_CMAKE_VARS -DBUILD_TEST_SHARED=${BUILD_TEST_SHARED})
list (APPEND BUILD_CMAKE_VARS -DBUILD_MAKEFILE_VERSION=${BUILD_MAKEFILE_VERSION})
list (APPEND BUILD_CMAKE_VARS -DBUILD_TYPE=${BUILD_TYPE})

#message ("BUILD_CMAKE_VARS: ${BUILD_CMAKE_VARS}")

## Create valid enumeration names
set(INVALID_CHARS "[\\.\\$ ]")
string(REGEX REPLACE ${INVALID_CHARS} "_" BUILD_ENUM_APPLICATION ${BUILD_APPLICATION})
string(REGEX REPLACE ${INVALID_CHARS} "_" BUILD_ENUM_BOARD ${BUILD_BOARD})
string(REGEX REPLACE ${INVALID_CHARS} "_" BUILD_ENUM_CUSTOMER ${BUILD_CUSTOMER})
string(REGEX REPLACE ${INVALID_CHARS} "_" BUILD_ENUM_DUPLEX ${BUILD_DUPLEX})
string(REGEX REPLACE ${INVALID_CHARS} "_" BUILD_ENUM_FIBRE_INTERFACE ${BUILD_FIBRE_INTERFACE})

set (BUILD_VARS "${BUILD_VARS} BUILD_ENUM_APPLICATION=${BUILD_ENUM_APPLICATION} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_ENUM_BOARD=${BUILD_ENUM_BOARD} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_ENUM_CUSTOMER=${BUILD_ENUM_CUSTOMER} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_ENUM_DUPLEX=${BUILD_ENUM_DUPLEX} ")
set (BUILD_VARS "${BUILD_VARS} BUILD_ENUM_FIBRE_INTERFACE=${BUILD_ENUM_FIBRE_INTERFACE} ")

list (APPEND BUILD_CMAKE_VARS -DBUILD_ENUM_APPLICATION=${BUILD_ENUM_APPLICATION})
list (APPEND BUILD_CMAKE_VARS -BUILD_ENUM_BOARD=${BUILD_ENUM_BOARD})
list (APPEND BUILD_CMAKE_VARS -DBUILD_ENUM_CUSTOMER=${BUILD_ENUM_CUSTOMER})
list (APPEND BUILD_CMAKE_VARS -DBUILD_ENUM_DUPLEX=${BUILD_ENUM_DUPLEX})
list (APPEND BUILD_CMAKE_VARS -DBUILD_ENUM_FIBRE_INTERFACE=${BUILD_ENUM_FIBRE_INTERFACE})


#message(STATUS "++ BUILD_ENUM_APPLICATION='${BUILD_ENUM_APPLICATION}' BUILD_APPLICATION=${BUILD_APPLICATION}")
#message(STATUS "++ BUILD_ENUM_BOARD='${BUILD_ENUM_BOARD}'")
#message(STATUS "++ BUILD_ENUM_CUSTOMER='${BUILD_ENUM_CUSTOMER}'")
#message(STATUS "++ BUILD_ENUM_DUPLEX='${BUILD_ENUM_DUPLEX}'")
#message(STATUS "++ BUILD_ENUM_FIBRE_INTERFACE='${BUILD_ENUM_FIBRE_INTERFACE}'")


## Compile #defines
if (NOT CMAKE_SCRIPT_MODE_FILE)
	message(STATUS "CMAKE_VERSION=${CMAKE_VERSION} TARGET=${TARGET}")
	message(STATUS "Add TARGET definition (not script mode)")
	STRING(TOUPPER ${TARGET} TARGET_UC)
	add_compile_definitions(TARGET_${TARGET_UC}=1)

	add_compile_definitions(PRODUCT_CODE="${BUILD_PRODUCT_CODE}")
	add_compile_definitions(VENDOR_CODE="${BUILD_VENDOR_CODE}")
endif()

##----------------------------------------------------------------------------------------------------------------------
getCachedEnvVar (BUILD_ROS_PATH "" "ROS build path")
set (ROS_PATH ${BUILD_ROS_PATH})
message(STATUS "settings.cmake: BUILD_ROS_PATH=${BUILD_ROS_PATH} ROS_PATH=${ROS_PATH}")

# Full build path will be of the form:
# ${ROS_BUILDDIR}/${BUILD_BOARD}_${BUILD_APPLICATION}
#
# Strip off the final dir to get back to ${ROS_BUILDDIR}
#
if (NOT ${BUILD_ROS_PATH} STREQUAL "")
	message(STATUS "settings.cmake: get_filename_component(ROS_BUILDDIR ${ROS_PATH} DIRECTORY)")
	get_filename_component(ROS_BUILDDIR ${ROS_PATH} DIRECTORY)
	
	# Force search to this path
	set (ROS_MAKE_PATHS
		${ROS_PATH}/make
	)
	
	message(STATUS "ROS path specified as '${ROS_PATH}' - ROS_BUILDDIR=${ROS_BUILDDIR}")
	
	message(STATUS "settings.cmake: ROS_PATH=${ROS_PATH}")
	message(STATUS "ROS_BUILDDIR=${ROS_BUILDDIR}")
	message(STATUS "ROS_MAKE_PATHS=${ROS_MAKE_PATHS}")
	message(STATUS "BUILD_TEST_SHARED=${BUILD_TEST_SHARED}")

endif()

##----------------------------------------------------------------------------------------------------------------------
## Set up features

#message(STATUS "--ALL VARS------------------")
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
#message(STATUS "----------------------------")
#
#message(STATUS "--CACHE VARS------------------")
#get_cmake_property(_variableNames CACHE_VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
#message(STATUS "----------------------------")



# Create list of features
getEnvVar (FEATURE_LIST "")
#message(STATUS "settings: FEATURE_LIST=${FEATURE_LIST}")
if ("${FEATURE_LIST}" STREQUAL "")
    set (FEATURES "")
else()
    string (REPLACE ":" ";" FEATURES ${FEATURE_LIST})
endif()
#message(STATUS "settings: FEATURES=${FEATURES}")
set (BUILD_VARS "${BUILD_VARS} FEATURE_LIST=${FEATURE_LIST} ")
list (APPEND BUILD_CMAKE_VARS -DFEATURE_LIST=${FEATURE_LIST})

# Process list and get feature values
get_cmake_property(_variableNames VARIABLES)
foreach (feat ${FEATURES})
        
    ## Update variables
    set (BUILD_VARS "${BUILD_VARS} FEAT_${feat}=$ENV{FEAT_${feat}} ")
    set (FEAT_${feat} "$ENV{FEAT_${feat}}")

	if (NOT CMAKE_SCRIPT_MODE_FILE)
	
	    ## Compile definition
	    add_compile_definitions(FEAT_${feat}="$ENV{FEAT_${feat}}")	# define var=value
	    
	    # create a define that is the var_value so we can #ifdef on it
	    # NOTE: Don't do this here because it's added to config.h
	    ##add_compile_definitions(FEAT_${feat}_$ENV{FEAT_${feat}})	
	endif()
    
endforeach()

# Create list of feature libraries
getEnvVar (FEATURE_LIBS_LIST "")
#message(STATUS "settings: FEATURE_LIBS_LIST=${FEATURE_LIBS_LIST}")
if ("${FEATURE_LIBS_LIST}" STREQUAL "")
    set (FEATURE_LIBS "")
else()
    string (REPLACE ":" ";" FEATURE_LIBS ${FEATURE_LIBS_LIST})
endif()
set (BUILD_VARS "${BUILD_VARS} FEATURE_LIBS_LIST=${FEATURE_LIBS_LIST} ")
list (APPEND BUILD_CMAKE_VARS -DFEATURE_LIBS_LIST=${FEATURE_LIBS_LIST})

# Create list of rootfs file list files
getEnvVar (ROOTFS_FILES "")
#message(STATUS "settings: ROOTFS_FILES=${ROOTFS_FILES}")
set (BUILD_VARS "${BUILD_VARS} ROOTFS_FILES=${ROOTFS_FILES} ")
list (APPEND BUILD_CMAKE_VARS -DROOTFS_FILES=${ROOTFS_FILES})




##----------------------------------------------------------------------------------------------------------------------
message(STATUS "settings: BUILD_VARS=${BUILD_VARS}")


# Add features subdir to module search path
list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules/Features)


##----------------------------------------------------------------------------------------------------------------------
## Debug
getCachedEnvVar (DEBUG_CMAKELIST "0" "Debug cmake build scripts (set level greater than 0)")
#set (DEBUG_CMAKELIST "1")

