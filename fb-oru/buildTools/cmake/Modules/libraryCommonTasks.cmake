##======================================================================================================================
## CMake Inlcude file - common tasks for creating a library are added here 
##
## Uses variables:
##    $LIBRARY_DEPENDS    - Set to a list of libraries that this library depends on
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
## Create library
logDebug("libraryCommonTasks: PROJECT=${PROJECT_NAME} CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} SOURCES=${SOURCES}") 
add_library (${PROJECT_NAME} STATIC ${SOURCES})

##----------------------------------------------------------------------------------------------------------------------
## Add library dependencies
if (LIBRARY_DEPENDS)
    target_link_libraries(${PROJECT_NAME} ${LIBRARY_DEPENDS})
endif ()

##----------------------------------------------------------------------------------------------------------------------
## Coverage
include (coverage)
addCoverageTarget()

##----------------------------------------------------------------------------------------------------------------------
## Cppcheck
include (cppcheck)
addCppcheckTarget()

##----------------------------------------------------------------------------------------------------------------------
## Memory leak
include (valgrind)
addMemcheckTarget()

##----------------------------------------------------------------------------------------------------------------------
## Use CPack

# Set which files/dirs to ignore
set (CPACK_SOURCE_IGNORE_FILES
"/.git/"
"/.gitignore/"
"/gtest/"
"/test/"
"/doc/"
"/build/"
)

# Specify the package(s)
#SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_SOURCE_GENERATOR "TGZ")

# Patch number
SET(CPACK_PACKAGE_VERSION "${BUILD_VERSION}-${BUILD_NUMBER}")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "${BUILD_NUMBER}")

include (CPack)

## Create source package
add_custom_target(pkg_source
    COMMAND ${CMAKE_MAKE_PROGRAM} package_source
    COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/_CPack_Packages
    COMMENT Create source package and clean out source copies
)


##----------------------------------------------------------------------------------------------------------------------
## Package up the library
exportLib()


