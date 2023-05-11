##======================================================================================================================
## Cmake settings file for install
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
## settings
set (ROOTFS_DIR ${CMAKE_BINARY_DIR}/rootfs)
set (TMP_ROOTFS ${ROOTFS_DIR}/tmp)
set (APP_ROOTFS ${ROOTFS_DIR}/APP)
set (LIB_ROOTFS ${ROOTFS_DIR}/LIB)
set (ATE_ROOTFS ${ROOTFS_DIR}/ATE)
set (SRC_ROOTFS ${ROOTFS_DIR}/SRC)
set (PACKAGE_DIR ${CMAKE_BINARY_DIR}/packages)
set (EXTRAS_DIR ${CMAKE_BINARY_DIR}/extras)

message("installSettings.cmake: BUILD_SUFFIX=${BUILD_SUFFIX}")

set (PACKAGE_BASE_NAME ${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION}${BUILD_SUFFIX}-${BUILD_VERSION}-${BUILD_NUMBER})

set (PACKAGE_APP_NAME ${PACKAGE_BASE_NAME}-APP)
set (PACKAGE_LIB_NAME ${PACKAGE_BASE_NAME}-LIB)
set (PACKAGE_SRC_NAME ${PACKAGE_BASE_NAME}-SRC)
set (PACKAGE_FILE_NAME ${BUILD_BOARD}-${BUILD_APPLICATION}${BUILD_SUFFIX}-${BUILD_VERSION}-${BUILD_NUMBER}.pkg)

#set (ATE_TGZ ${BUILD_BOARD}-${BUILD_APPLICATION}-${BUILD_VERSION}-${BUILD_NUMBER}.tgz)

set (FPGA_MANIFEST ${TMP_ROOTFS}/fpga-manifest)
set (FPGADIR ${GITDIR}/fpga/images/${BUILD_BOARDAPPNAME})

set (FLASH_DIR nandflash)
set (FLASH_APP_DIR ${FLASH_DIR}/app-images)
set (FLASH_LIB_DIR ${FLASH_DIR}/lib-images)
