##======================================================================================================================
## Cmake common tasks for installing cut-down ATE application
##
##======================================================================================================================

## Ensure the ATE install script is created ready for use with the 'install' target
configure_file(
    ${GITDIR}/buildTools/cmake/inc/installAte.cmake.in 
    ${CMAKE_BINARY_DIR}/installAte.cmake 
    @ONLY)

## Set up the directories
install(CODE "file(MAKE_DIRECTORY ${ATE_ROOTFS})")
install(CODE "file(MAKE_DIRECTORY ${ATE_ROOTFS}/${FLASH_APP_DIR})")
install(CODE "file(MAKE_DIRECTORY ${ATE_ROOTFS}/${FLASH_LIB_DIR})")

## Run the process to get file list and create tarball
add_custom_target(ate-tgz
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/installAte.cmake
    DEPENDS app-tgz
    COMMENT "ATE TGZ"
)

add_dependencies(tgz ate-tgz)



