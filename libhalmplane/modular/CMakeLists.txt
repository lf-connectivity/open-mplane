
find_library(TINYXML2 tinyxml2)
find_library(DL dl)

target_link_libraries(halmplane
  ${DL}
  ${TINYXML2}
)

string(CONCAT SRC

  "src/HalMplane.cpp;"
  "src/ModuleLoader.cpp;"
  "src/MplaneAlarms.cpp;"
  "src/MplaneAld.cpp;"
  "src/MplaneAntennaCalibration.cpp;"
  "src/MplaneBeamforming.cpp;"
  "src/MplaneDelayMgmt.cpp;"
  "src/MplaneEcpri.cpp;"
  "src/MplaneExternalio.cpp;"
  "src/MplaneFan.cpp;"
  "src/MplaneHardware.cpp;"
  "src/MplaneInterfaces.cpp;"
  "src/MplaneModuleCapability.cpp;"
#####  "src/MplanePerformanceMgmt.cpp;"
  "src/MplaneProcessingElements.cpp;"
  "src/MplaneSupervision.cpp;"
  "src/MplaneSync.cpp;"
  "src/MplaneTransceiver.cpp;"
  "src/MplaneUplaneConf.cpp;"

)
include_directories("modular/inc")

list(TRANSFORM SRC PREPEND "modular/")
target_sources(halmplane PRIVATE ${SRC})

