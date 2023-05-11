##======================================================================================================================
## Create CMAKE files for an install
##
##======================================================================================================================


##----------------------------------------------------------------------------------------------------------------------

## Ensure the FPGA install script is created ready for use with the 'install' target
configure_file(
    ${GITDIR}/buildTools/cmake/inc/installFpga_example.cmake.in
    ${CMAKE_BINARY_DIR}/installFpga_example.cmake
    @ONLY)

## Ensure the APP install script is created ready for use with the 'install' target
configure_file(
    ${GITDIR}/buildTools/cmake/inc/installApp.cmake.in
    ${CMAKE_BINARY_DIR}/installApp.cmake
    @ONLY)

## Ensure the LIB install script is created ready for use with the 'install' target
configure_file(
    ${GITDIR}/buildTools/cmake/inc/installLib.cmake.in
    ${CMAKE_BINARY_DIR}/installLib.cmake
    @ONLY)

## Ensure the PKG install script is created ready for use with the 'install' target
configure_file(
    ${GITDIR}/buildTools/cmake/inc/installPkg.cmake.in
    ${CMAKE_BINARY_DIR}/installPkg.cmake
    @ONLY)
