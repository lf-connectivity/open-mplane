##======================================================================================================================
## Cmake file 
##
# Add user code here
# %%->

# <-%%
#
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
# Add user project definition code here. e.g.
#   cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
#   project (yang-swtoolsShared CXX)
#   set (version "0.1")
#
#   if (NOT GITDIR)
#	  get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
#	  list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)
#   endif ()
#
# %%->

# <-%%

##----------------------------------------------------------------------------------------------------------------------
# Add user code here e.g.
#  include(rse)  
#
# %%->

# <-%%

##----------------------------------------------------------------------------------------------------------------------
# Add user code here e.g.
#  addIncludes ()
#
# %%->

# <-%%

##----------------------------------------------------------------------------------------------------------------------
# Use of the repository libs
# Add user code here
# %%->

# <-%%

##----------------------------------------------------------------------------------------------------------------------
## Library Source
add_sources (SOURCES

	src/YangModuleIanaHardware.cpp
	src/YangModuleIanaIfType.cpp
	src/YangModuleIetfCryptoTypes.cpp
	src/YangModuleIetfDhcpv6Types.cpp
	src/YangModuleIetfHardware.cpp
	src/YangModuleIetfInetTypes.cpp
	src/YangModuleIetfInterfaces.cpp
	src/YangModuleIetfIp.cpp
	src/YangModuleIetfNetconfAcm.cpp
	src/YangModuleIetfNetconfMonitoring.cpp
	src/YangModuleIetfYangLibrary.cpp
	src/YangModuleIetfYangTypes.cpp
	src/YangModuleORanAldPort.cpp
	src/YangModuleORanAld.cpp
	src/YangModuleORanAntennaCalibration.cpp
	src/YangModuleORanCompressionFactors.cpp
	src/YangModuleORanDelayManagement.cpp
	src/YangModuleORanDhcp.cpp
	src/YangModuleORanEcpriDelay.cpp
	src/YangModuleORanExternalio.cpp
	src/YangModuleORanFan.cpp
	src/YangModuleORanFileManagement.cpp
	src/YangModuleORanFm.cpp
	src/YangModuleORanHardware.cpp
	src/YangModuleORanInterfaces.cpp
	src/YangModuleORanLaaOperations.cpp
	src/YangModuleORanLaa.cpp
	src/YangModuleORanLbm.cpp
	src/YangModuleORanModuleCap.cpp
	src/YangModuleORanMplaneInt.cpp
	src/YangModuleORanOperations.cpp
	src/YangModuleORanPerformanceManagement.cpp
	src/YangModuleORanProcessingElement.cpp
	src/YangModuleORanSoftwareManagement.cpp
	src/YangModuleORanSupervision.cpp
	src/YangModuleORanSync.cpp
	src/YangModuleORanTrace.cpp
	src/YangModuleORanTransceiver.cpp
	src/YangModuleORanTroubleshooting.cpp
	src/YangModuleORanUdpEcho.cpp
	src/YangModuleORanUplaneConf.cpp
	src/YangModuleORanUsermgmt.cpp


# Add user code here
# %%->
	src/YangMgrServer.cpp
# <-%%
)

# Add user code here
# %%->

# <-%%

# Add user code here
# %%->
## Cppcheck
include (cppcheck)
addCppcheck(yangmodels)


if (${TARGET} STREQUAL "x86_64")

    addRepoLib(libs xcommon)
    addRepoLib(libs common)

    # Load google test
    include (gtest)

	include_directories(gtest)
	set(gtest_src
        gtest/tests.cpp
		gtest/yangmodel_unittest.cpp

		# Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
# 	addGtest(yangmodel_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
# 	addCoverage(yangmodel_GTEST)

	# Add memory leak check
	include (valgrind)
# 	addMemcheck(yangmodel_GTEST)


endif (${TARGET} STREQUAL "x86_64")
# <-%%
