##======================================================================================================================
## Cmake common tasks for installing tarballs
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
## Dummy targets
add_custom_target (memcheck)
add_custom_target (coverage)
add_custom_target (cppcheck)

##----------------------------------------------------------------------------------------------------------------------
set (fpgaCmake ${CMAKE_BINARY_DIR}/installFpga_example.cmake)
set (appCmake  ${CMAKE_BINARY_DIR}/installApp.cmake)
set (libCmake  ${CMAKE_BINARY_DIR}/installLib.cmake)
set (pkgCmake  ${CMAKE_BINARY_DIR}/installPkg.cmake)
set (forceMake ${CMAKE_BINARY_DIR}/dummy.cmake)

logDebug("BUILD_NUMBER=${BUILD_NUMBER}")

    # command to create the cmake install files
    # Only pass the static values down - the files determine the dynamic build settings themselves
    add_custom_command(
            OUTPUT ${fpgaCmake} ${appCmake} ${libCmake} ${pkgCmake} ${forceMake}
            COMMAND ${CMAKE_COMMAND}
                -D GITDIR=${GITDIR}
                -D TARGET=${TARGET}
                -D DEVTOOLS_INSTALLDIR=${DEVTOOLS_INSTALLDIR}
                -D FPGA_MANIFEST=${FPGA_MANIFEST}
                -D STARTUP_APP=${STARTUP_APP}
                -D TOOLCHAIN_LINUX_DIR=${TOOLCHAIN_LINUX_DIR}
                -D GCC_DIR=${GCC_DIR}
                -D GLIBC_DIR=${GLIBC_DIR}
                -D EMBEDDED_PROJECT=${EMBEDDED_PROJECT}
                -D FPGA_FIND_FILE=${FPGA_FIND_FILE}
                -D OS_PKG_DIR=${OS_PKG_DIR}
                -D OS_PKG_NAME=${OS_PKG_NAME}
                -D PROJECT_NAME=${PROJECT_NAME}
                -D PROJECT_SOURCE_DIR=${${PROJECT_NAME}_SOURCE_DIR}
                -D ROOTFS_FILES=${ROOTFS_FILES}
                -D PRODUCT_CODE=${BUILD_PRODUCT_CODE}
                -D VENDOR_CODE=${BUILD_VENDOR_CODE}
                -P ${GITDIR}/buildTools/cmake/Modules/installCmake.cmake
           COMMENT "Install: Creating install CMake files"
    )


    add_custom_target(
           cmake-install-files ALL
           DEPENDS ${fpgaCmake} ${appCmake} ${libCmake} ${pkgCmake} ${forceMake}
           COMMENT "Install: Make install CMake files"
    )


## Ensure the PKG SOURCE install script is created ready for use with the 'install' target
configure_file(
    ${GITDIR}/buildTools/cmake/inc/installSource.cmake.in
    ${CMAKE_BINARY_DIR}/installSource.cmake
    @ONLY)

##----------------------------------------------------------------------------------------------------------------------

## Clean
add_custom_target(clean-rootfs
    COMMAND rm "-rf" "${ROOTFS_DIR}"
)


## Set up the package directory
install(CODE "file(MAKE_DIRECTORY ${PACKAGE_DIR})")

##----------------------------------------------------------------------------------------------------------------------

## APP tarball

# Fpga Tar
logDebug("Run installFpga_example : TARGET=${TARGET}")
install(SCRIPT ${CMAKE_BINARY_DIR}/installFpga_example.cmake)

# App Tgz
#install(SCRIPT ${CMAKE_BINARY_DIR}/installApp.cmake)
add_custom_target(app-tgz
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/installApp.cmake
    DEPENDS ${APP_ROOTFS}
    COMMENT "APP TGZ"
)


##----------------------------------------------------------------------------------------------------------------------

## LIB tarball

## Install required libraries
set (requiredLibs
	libgcc_s*.so*
	libpthread*.so*
)

set (libsList "")
foreach (requiredLib ${requiredLibs})
    file(GLOB libs RELATIVE_PATH "${TOOLCHAIN_LIBS}/${requiredLib}")
    list(APPEND libsList ${libs})
endforeach ()

## Set up the lib directory
install(CODE "file(MAKE_DIRECTORY ${LIB_ROOTFS}/lib)")

logDebug ("libs=${libsList}")
install (FILES ${libsList} DESTINATION ${LIB_ROOTFS}/lib
    PERMISSIONS
        OWNER_EXECUTE OWNER_READ OWNER_WRITE
        GROUP_EXECUTE GROUP_READ
        WORLD_EXECUTE WORLD_READ)

## Copy dev-install from ROS
set (devInstall ${ROS_PATH}/Linux-${TARGET}/dev-install)
file(GLOB devDirs RELATIVE_PATH "${devInstall}/sbin")
install(CODE "file(MAKE_DIRECTORY ${LIB_ROOTFS}/sbin)")

install (DIRECTORY ${devDirs} DESTINATION ${LIB_ROOTFS}
    FILE_PERMISSIONS
        OWNER_EXECUTE OWNER_READ OWNER_WRITE
        GROUP_EXECUTE GROUP_READ
        WORLD_EXECUTE WORLD_READ
    DIRECTORY_PERMISSIONS
        OWNER_EXECUTE OWNER_READ OWNER_WRITE
        GROUP_EXECUTE GROUP_READ
        WORLD_EXECUTE WORLD_READ)

# Lib Tgz
#install(SCRIPT ${CMAKE_BINARY_DIR}/installLib.cmake)
add_custom_target(lib-tgz
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/installLib.cmake
    DEPENDS ${LIB_ROOTFS}
    COMMENT "LIB TGZ"
)


##----------------------------------------------------------------------------------------------------------------------

## All tarballs
add_custom_target(tgz
    DEPENDS app-tgz lib-tgz
)


##----------------------------------------------------------------------------------------------------------------------

## Package
add_custom_target(pkg
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/installPkg.cmake
    DEPENDS tgz
    COMMENT "PACKAGE"
)

##======================================================================================================================

## Source

message("installCommonTasks: PACKAGE_SOURCE_LIST=${PACKAGE_SOURCE_LIST}")
message("installCommonTasks: SOURCES=${SOURCES}")
message("installCommonTasks: SOURCE_PATHS=${SOURCE_PATHS}")

add_custom_target(src-pkg
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/installSource.cmake
    COMMENT "PACKAGE SOURCE"
)
