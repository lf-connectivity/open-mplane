##======================================================================================================================
## Cmake file for applications/shared/Ina226Rd
##
##======================================================================================================================

set (app Ina226Rd)
#initialCapital(board ${BUILD_BOARD})
#set (boardApp ${board}${app})
set (boardApp ${app})

set (SOURCES
    bin-src/${app}.cpp
    src/RegData.cpp
    src/RegDataSingleton.cpp
)

## Libraries used
addRepoLib( libs  xcommon )
addRepoLib( libs  common )
addRepoLib( libs  hardware common )
addRepoLib( libs  hardware ZCU111 )

## Executable
add_executable(${boardApp} ${SOURCES})
addLinkLibs(${boardApp} ${libs})

install(TARGETS ${boardApp} RUNTIME DESTINATION ${APP_ROOTFS}/bin)


