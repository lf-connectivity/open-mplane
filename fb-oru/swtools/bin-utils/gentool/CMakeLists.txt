# Cmake file for bin-utils/gentool
if (${TARGET} STREQUAL "x86_64")

    set (GENTOOL_SOURCES
        main-src/GentoolMain.cpp
    )

    set (libs ${PROJECT_NAME})

    ## Uses tinyxml2
    addRosLib(libs tinyxml2)

    ## Libraries used
    addRepoLib( libs  xcommon )
    addRepoLib( libs  common )
    addRepoLib( libs  swtools shared )

    ## Executable
    add_executable(GenTool ${GENTOOL_SOURCES})
    addLinkLibs(GenTool ${libs})

    ## Install
    install (TARGETS GenTool DESTINATION ${LOCAL_INSTALL_DIR}/bin)

endif (${TARGET} STREQUAL "x86_64")

