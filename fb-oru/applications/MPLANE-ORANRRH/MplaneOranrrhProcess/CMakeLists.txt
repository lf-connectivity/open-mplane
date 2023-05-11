##======================================================================================================================
## Cmake file for applications/MPLANE-ORANRRH/MplaneOranrrhProcess
##
##======================================================================================================================

appStart(MplaneOranrrhProcess
 	src/NetStatusFactory.cpp
)

## Uses pcap
addRosLib(libs pcap)
## Uses tinyxml2
addRosLib(libs tinyxml2)

addRepoLib( libs  oran-libs zlib )
addRepoLib( libs  oran-libs ssl )
addRepoLib( libs  oran-libs crypto )
addRepoLib( libs  oran-libs libssh )
addRepoLib( libs  oran-libs sysrepo )
addRepoLib( libs  oran-libs sysrepo-cpp )
addRepoLib( libs  oran-libs pcre )
addRepoLib( libs  oran-libs yang )
addRepoLib( libs  oran-libs yangcpp )

## Libraries used
addRepoLib( libs  common )
addRepoLib( libs  xcommon )
addRepoLib( libs  halmplane)
addRepoLib( libs  hardware common )
addRepoLib( libs  hardware ${BUILD_BOARD} )
addRepoLib( libs  hardware ${BUILD_BOARD}_${BUILD_APPLICATION} )
addRepoLib( libs  services common )
addRepoLib( libs  services ${BUILD_BOARD} )
addRepoLib( libs  services ${BUILD_APPLICATION} )
addRepoLib( libs  services ${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION} )
addRepoLib( libs  swtools shared)
addRepoLib( libs  tif-common )
addRepoLib( libs  tif-common helper/common )
addRepoLib( libs  tif common-model )
addRepoLib( libs  tif helper/common )
addRepoLib( libs  tif helper/${BUILD_BOARD} )
addRepoLib( libs  tif helper/ORANRRH )
addRepoLib( libs  tif ${BUILD_BOARD} )
addRepoLib( libs  tif ${BUILD_BOARD}_${BUILD_APPLICATION} )
addRepoLib( libs  tif ${BUILD_BOARD}-${BUILD_CUSTOMER}-${BUILD_APPLICATION} )
addRepoLib( libs  yang-manager-server )
addRepoLib( libs  applications common )
addRepoLib( libs  applications common-specific )

list(APPEND libs "-ldl -lrt")

appEnd()
