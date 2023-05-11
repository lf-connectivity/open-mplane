# Cmake file for bin-utils/regtool
if (${TARGET} STREQUAL "x86_64")

    set (APPNAME RegTool)

    set (REGTOOL_SOURCES
    )

    set (libs ${PROJECT_NAME})

    ## Uses tinyxml2
    addRosLib(libs tinyxml2)

    ## Libraries used
    addRepoLib( libs  common )
    addRepoLib( libs  xcommon )
    addRepoLib( libs  swtools shared )

    ## Executable
    add_executable(RegTool ${REGTOOL_SOURCES} main-src/regtoolMain.cpp)
    addLinkLibs(RegTool ${libs})

    ## Install
    install (TARGETS RegTool DESTINATION ${LOCAL_INSTALL_DIR}/bin)

endif (${TARGET} STREQUAL "x86_64")

