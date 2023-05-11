cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (mplane-server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if (ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -fsanitize=address")
endif()

include(GNUInstallDirs)

## xcommon
set(MPLANE_SERVER_SOURCES
  xcommon/Base64/src/Base64.cpp
  xcommon/ByteTransfer/src/dummy.cpp
  xcommon/Crc/src/Crc.cpp
  xcommon/Feature/src/Feature.cpp
  xcommon/Feature/src/GenericFeature.cpp
  xcommon/PathUtils/src/PathUtils.cpp
  xcommon/WaveFile/src/CaptureWave.cpp
  xcommon/WaveFile/src/CaptureWaveData.cpp
  xcommon/WaveFile/src/CaptureWaveHeader.cpp
  xcommon/WaveFile/src/PlaybackWave.cpp
  xcommon/WaveFile/src/PlaybackWaveHeader.cpp
  xcommon/WaveFile/src/WaveFileHeader.cpp
  xcommon/crypt/src/Crypt.cpp
  xcommon/cubicSpline/src/cubicSpline.cpp
  xcommon/cubicSpline/src/matlab_cubic_spline.cpp
  xcommon/cubicSpline/src/matlab_cubic_spline_emxAPI.cpp
  xcommon/cubicSpline/src/matlab_cubic_spline_emxutil.cpp
  xcommon/cubicSpline/src/matlab_cubic_spline_initialize.cpp
  xcommon/cubicSpline/src/matlab_cubic_spline_terminate.cpp
  xcommon/cubicSpline/src/rtGetInf.cpp
  xcommon/cubicSpline/src/rtGetNaN.cpp
  xcommon/cubicSpline/src/rt_nonfinite.cpp
  xcommon/cubicSpline/src/spline.cpp
  xcommon/key/src/GlobalKey.cpp
  xcommon/key/src/Key.cpp
  xcommon/lzo/src/Lzo.cpp
  xcommon/lzo/src/minilzo.cpp
  xcommon/md5/src/Md5Sum.cpp
  xcommon/md5/src/md5.cpp
  xcommon/sha1/src/Sha1.cpp
)

include_directories(xcommon/inc)
include_directories(xcommon/Feature/inc)
include_directories(xcommon/WaveFile/inc)
include_directories(xcommon/cubicSpline/inc)
include_directories(xcommon/fft/inc)
include_directories(xcommon/key/inc)
include_directories(xcommon/lzo/inc)
include_directories(xcommon/md5/inc)

## common
list(APPEND MPLANE_SERVER_SOURCES
  common/AppOptions/src/AppOptions.cpp
  common/Benchmark/src/Benchmark.cpp
  common/BootTimer/src/BootTimer.cpp
  common/DataVariant/src/DataVariant.cpp
  common/DataVariant/src/DataVariantBase.cpp
  common/DataVariant/src/DataVariantList.cpp
  common/DataVariant/src/DataVariantSettings.cpp
  common/DataVariant/src/DataVariantType/DataVariantBool.cpp
  common/DataVariant/src/DataVariantType/DataVariantComplex.cpp
  common/DataVariant/src/DataVariantType/DataVariantDouble.cpp
  common/DataVariant/src/DataVariantType/DataVariantEnum.cpp
  common/DataVariant/src/DataVariantType/DataVariantFloat.cpp
  common/DataVariant/src/DataVariantType/DataVariantFreq.cpp
  common/DataVariant/src/DataVariantType/DataVariantInt.cpp
  common/DataVariant/src/DataVariantType/DataVariantLong.cpp
  common/DataVariant/src/DataVariantType/DataVariantPower.cpp
  common/DataVariant/src/DataVariantType/DataVariantTypeBase.cpp
  common/DataVariant/src/DataVariantType/DataVariantTypes.cpp
  common/DataVariant/src/DataVariantType/DataVariantUint.cpp
  common/DataVariant/src/DataVariantVector.cpp
  common/DataVariant/src/DvType/DvTypeBase.cpp
  common/DataVariant/src/DvType/DvTypeBool.cpp
  common/DataVariant/src/DvType/DvTypeComplex.cpp
  common/DataVariant/src/DvType/DvTypeDouble.cpp
  common/DataVariant/src/DvType/DvTypeEnum.cpp
  common/DataVariant/src/DvType/DvTypeFloat.cpp
  common/DataVariant/src/DvType/DvTypeFreq.cpp
  common/DataVariant/src/DvType/DvTypeInt.cpp
  common/DataVariant/src/DvType/DvTypeLong.cpp
  common/DataVariant/src/DvType/DvTypeNone.cpp
  common/DataVariant/src/DvType/DvTypePower.cpp
  common/DataVariant/src/DvType/DvTypeString.cpp
  common/DataVariant/src/DvType/DvTypeUint.cpp
  common/DataVariant/src/DvTypeFactory.cpp
  common/FileConfig/src/FileConfig.cpp
  common/FileConfig/src/FileConfigBase.cpp
  common/FileConfig/src/FileConfigWriter.cpp
  common/FileMgr/src/FileMgr.cpp
  common/FileStatus/src/FileStatus.cpp
  common/FileStatus/src/NullFileStatus.cpp
  common/Networking/src/IpPortMgr.cpp
  common/Maths/src/Maths.cpp
  common/Path/src/Path.cpp
  common/ServicesMonitor/src/KickWatchdog.cpp
  common/ServicesMonitor/src/ServicesMonitor.cpp
  common/ServicesMonitor/src/ServicesMonitorFactory.cpp
  common/Sftp/src/SftpPath.cpp
  common/configData/src/CommonConfigBase.cpp
  common/configDownloadManagement/src/ConfigCoordinator.cpp
  common/configDownloadManagement/src/ConfigDownload.cpp
  common/configDownloadManagement/src/ConfigDownloadManagement.cpp
  common/configDownloadManagement/src/ConfigDownloadMgrSingleton.cpp
  common/datatype/src/Frequency.cpp
  common/datatype/src/FrequencyOffset.cpp
  common/datatype/src/FrequencyStatic.cpp
  common/datatype/src/Power.cpp
  common/datatype/src/Temperature.cpp
  common/datatype/src/Tokeniser.cpp
  common/logging/src/LogHistoryBuffer.cpp
  common/logging/src/LogList.cpp
  common/logging/src/Loggable.cpp
  common/logging/src/LoggerBase.cpp
  common/logging/src/LoggerHistorySyslog.cpp
  common/logging/src/LoggerSyslog.cpp
  common/service/src/Service.cpp
  common/task/src/Conditional.cpp
  common/task/src/Mutex.cpp
  common/task/src/RecursiveMutex.cpp
  common/task/src/SystemTask.cpp
  common/task/src/Task.cpp
  common/task/src/TaskEvent.cpp
  common/task/src/TaskList.cpp
  common/task/src/TaskPeriodicEvent.cpp
  common/timer/src/NullTimeoutTimer.cpp
  common/timer/src/TimeoutTimer.cpp
)

include_directories(common/inc)
include_directories(common/DataVariant/inc)
include_directories(common/DataVariant/inc/DataVariant)
include_directories(common/DataVariant/inc/DataVariantType)
include_directories(common/DataVariant/inc/DvType)
include_directories(common/FileConfig/inc)
include_directories(common/FileStatus/inc)
include_directories(common/Networking/inc)
include_directories(common/ServicesMonitor/inc)
include_directories(common/config)
include_directories(common/configData/inc)
include_directories(common/configDownloadManagement/inc)
include_directories(common/logging/inc)
include_directories(common/timer/inc)
include_directories(common/vcommoni/inc)

## services-common
list(APPEND MPLANE_SERVER_SOURCES
  services-common/AppServices/src/AppServices.cpp
)

include_directories(services-common/AppServices/inc)

## services
list(APPEND MPLANE_SERVER_SOURCES
  services/ORANRRH/AppControl/src/OranRrhAppControl.cpp
  services/ORANRRH/AppControl/src/OranRrhAppControlFactory.cpp
)

include_directories(services/ORANRRH/AppControl/inc)
include_directories(services/vsi/inc)

## yang-manager-server
list(APPEND MPLANE_SERVER_SOURCES
  yang-manager-server/ConfigParser/src/YangConfig.cpp
  yang-manager-server/ConfigParser/src/YangConfigDownload.cpp
  yang-manager-server/ConfigParser/src/YangConfigParser.cpp
  yang-manager-server/ConfigParser/src/YangConfigSingleton.cpp
  yang-manager-server/ConfigParser/src/YangElement.cpp
  yang-manager-server/ConfigParser/src/YangElementFactories.cpp
  yang-manager-server/NetopeerMonitoringService/src/NetopeerMonService.cpp
  yang-manager-server/NetopeerMonitoringService/src/NetopeerMonServiceSingleton.cpp
  yang-manager-server/RadioDatastore/src/RadioDatastore.cpp
  yang-manager-server/logging/src/LoggerFactory.cpp
  yang-manager-server/services/src/YangServices.cpp
  yang-manager-server/services/src/YangServicesFactory.cpp
  yang-manager-server/ssh/src/SftpMgr.cpp
  yang-manager-server/ssh/src/SftpSession.cpp
  yang-manager-server/ssh/src/SshSession.cpp
  yang-manager-server/yang-handlers/src/XpathUtils.cpp
  yang-manager-server/yang-handlers/src/YangHandler.cpp
  yang-manager-server/yang-handlers/src/YangCarrierMgr.cpp
  yang-manager-server/yang-handlers/src/YangHandlerMgr.cpp
  yang-manager-server/yang-handlers/src/YangPersist.cpp
  yang-manager-server/yang-manager-service/src/YangMgrService.cpp
  yang-manager-server/yang-manager/src/YangModule.cpp
  yang-manager-server/yang-manager/src/YangModuleMgr.cpp
  yang-manager-server/yang-manager/src/YangParam.cpp
  yang-manager-server/yang-manager/src/YangParamUtils.cpp
  yang-manager-server/yang-manager/src/YangUtils.cpp
  yang-manager-server/yang-model-handlers/src/IetfInterfacesHandler.cpp
  yang-manager-server/yang-model-handlers/src/IetfNetconfAcmHandler.cpp
  yang-manager-server/yang-model-handlers/src/IetfNetconfServerHandler.cpp
  yang-manager-server/yang-model-handlers/src/OranModuleCapHandler.cpp
  yang-manager-server/yang-model-handlers/src/OranProcessingElementHandler.cpp
  yang-manager-server/yang-model-handlers/src/OranUserMgmtHandler.cpp
  yang-manager-server/yang-model-handlers/src/OranUplaneConfHandler.cpp
  yang-manager-server/yang-model-handlers/src/OranYangCarrierMgr.cpp
  yang-manager-server/yang-model-handlers/src/OranYangHandlerMgr.cpp
  yang-manager-server/yang-models/src/YangMgrServer.cpp
  yang-manager-server/yang-models/src/YangModuleIanaHardware.cpp
  yang-manager-server/yang-models/src/YangModuleIanaIfType.cpp
  yang-manager-server/yang-models/src/YangModuleIetfCryptoTypes.cpp
  yang-manager-server/yang-models/src/YangModuleIetfDhcpv6Types.cpp
  yang-manager-server/yang-models/src/YangModuleIetfHardware.cpp
  yang-manager-server/yang-models/src/YangModuleIetfInetTypes.cpp
  yang-manager-server/yang-models/src/YangModuleIetfInterfaces.cpp
  yang-manager-server/yang-models/src/YangModuleIetfIp.cpp
  yang-manager-server/yang-models/src/YangModuleIetfNetconfAcm.cpp
  yang-manager-server/yang-models/src/YangModuleIetfNetconfMonitoring.cpp
  yang-manager-server/yang-models/src/YangModuleIetfYangLibrary.cpp
  yang-manager-server/yang-models/src/YangModuleIetfYangTypes.cpp
  yang-manager-server/yang-models/src/YangModuleORanAld.cpp
  yang-manager-server/yang-models/src/YangModuleORanAldPort.cpp
  yang-manager-server/yang-models/src/YangModuleORanAntennaCalibration.cpp
  yang-manager-server/yang-models/src/YangModuleORanCompressionFactors.cpp
  yang-manager-server/yang-models/src/YangModuleORanDelayManagement.cpp
  yang-manager-server/yang-models/src/YangModuleORanDhcp.cpp
  yang-manager-server/yang-models/src/YangModuleORanEcpriDelay.cpp
  yang-manager-server/yang-models/src/YangModuleORanExternalio.cpp
  yang-manager-server/yang-models/src/YangModuleORanFan.cpp
  yang-manager-server/yang-models/src/YangModuleORanFileManagement.cpp
  yang-manager-server/yang-models/src/YangModuleORanFm.cpp
  yang-manager-server/yang-models/src/YangModuleORanHardware.cpp
  yang-manager-server/yang-models/src/YangModuleORanInterfaces.cpp
  yang-manager-server/yang-models/src/YangModuleORanLaa.cpp
  yang-manager-server/yang-models/src/YangModuleORanLaaOperations.cpp
  yang-manager-server/yang-models/src/YangModuleORanLbm.cpp
  yang-manager-server/yang-models/src/YangModuleORanModuleCap.cpp
  yang-manager-server/yang-models/src/YangModuleORanMplaneInt.cpp
  yang-manager-server/yang-models/src/YangModuleORanOperations.cpp
  yang-manager-server/yang-models/src/YangModuleORanPerformanceManagement.cpp
  yang-manager-server/yang-models/src/YangModuleORanProcessingElement.cpp
  yang-manager-server/yang-models/src/YangModuleORanSoftwareManagement.cpp
  yang-manager-server/yang-models/src/YangModuleORanSupervision.cpp
  yang-manager-server/yang-models/src/YangModuleORanSync.cpp
  yang-manager-server/yang-models/src/YangModuleORanTrace.cpp
  yang-manager-server/yang-models/src/YangModuleORanTransceiver.cpp
  yang-manager-server/yang-models/src/YangModuleORanTroubleshooting.cpp
  yang-manager-server/yang-models/src/YangModuleORanUdpEcho.cpp
  yang-manager-server/yang-models/src/YangModuleORanUplaneConf.cpp
  yang-manager-server/yang-models/src/YangModuleORanUsermgmt.cpp
  yang-manager-server/yang-sysrepo/src/LeafContainer.cpp
  yang-manager-server/yang-sysrepo/src/RadioDatastoreSysrepo.cpp
  yang-manager-server/yang-sysrepo/src/SysrepoGetitemsCallback.cpp
  yang-manager-server/yang-sysrepo/src/SysrepoUtils.cpp
  yang-manager-server/yang-sysrepo/src/YangHandlerSysrepo.cpp
  yang-manager-server/yang-sysrepo/src/YangHandlerSysrepo/HandlerCallback.cpp
  yang-manager-server/yang-sysrepo/src/YangHandlerSysrepo/RpcCallback.cpp
  yang-manager-server/yang-sysrepo/src/YangHandlerSysrepoUnlogged.cpp
  yang-manager-server/yang-sysrepo/src/YangParamSysrepo.cpp
  yang-manager-server/yang-sysrepo/src/YangUserAuth.cpp
)

include_directories(yang-manager-server/ConfigParser/inc)
include_directories(yang-manager-server/NetopeerMonitoringService/inc)
include_directories(yang-manager-server/RadioDatastore/inc)
include_directories(yang-manager-server/services/inc)
include_directories(yang-manager-server/ssh/inc)
include_directories(yang-manager-server/vyms/inc)
include_directories(yang-manager-server/yang-handlers/inc)
include_directories(yang-manager-server/yang-manager-service/inc)
include_directories(yang-manager-server/yang-manager/inc)
include_directories(yang-manager-server/yang-model-handlers/inc)
include_directories(yang-manager-server/yang-models/inc)
include_directories(yang-manager-server/yang-sysrepo/inc)

## application
list(APPEND MPLANE_SERVER_SOURCES
  application/Application/src/Application.cpp
)

include_directories(application/Application/inc)
include_directories(application/vappi/inc)

list(APPEND MPLANE_SERVER_SOURCES
  application/main.cpp
)

find_library(CRYPTO crypto)
find_library(HALMPLANE halmplane)
find_library(PTHREAD pthread)
find_library(SSH ssh)
find_library(SSL ssl)
find_library(SYSREPO sysrepo)
find_library(SYSREPO-CPP sysrepo-cpp)
find_library(TINYXML2 tinyxml2)
find_library(YANG yang)
find_library(YANG-CPP yang-cpp)
find_package(ZLIB REQUIRED)

add_executable(mplane-server-app ${MPLANE_SERVER_SOURCES})

target_link_libraries(mplane-server-app
  ${CRYPTO}
  ${HALMPLANE}
  ${PTHREAD}
  ${SSH}
  ${SSL}
  ${SYSREPO-CPP}
  ${SYSREPO}
  ${TINYXML2}
  ${YANG-CPP}
  ${YANG}
  ZLIB::ZLIB
)

install(TARGETS mplane-server-app DESTINATION sbin)
