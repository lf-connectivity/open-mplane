add_sources (SOURCES
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhYangCarrierMgr.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanDelayManagement.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerMgr.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanModuleCap.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfHardware.cpp
	../yang-ZCU111-FBC-ORANRRH/src/CallbackORanSoftwareMgr.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanMplaneInt.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfNetconfServer.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSoftwareManagement.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanPerformanceMgmt.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSync.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanProcessingElement.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanUplaneConf.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanFm.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanTransceiver.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanOperations.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanLbm.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanUserMgmt.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanDhcp.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfInterfaces.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerIetfNetconfAcm.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanFileManagement.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSupervision.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanSyncNotif.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanLog.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanTrace.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanTroubleshooting.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanAldPort.cpp
	../yang-ZCU111-FBC-ORANRRH/src/Zcu111FbcOranrrhHandlerORanAld.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(yang-ATLAS-MPLANE-ORANRRH)
