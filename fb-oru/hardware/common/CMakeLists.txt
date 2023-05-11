##======================================================================================================================
## Cmake file for hardware/common lib
##
##======================================================================================================================

##----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.0.1 FATAL_ERROR)
project (hardwareCommon CXX)
set (version "0.1")

##----------------------------------------------------------------------------------------------------------------------
if (NOT GITDIR)

	get_filename_component (GITDIR ${PROJECT_SOURCE_DIR} DIRECTORY)
	list(APPEND CMAKE_MODULE_PATH ${GITDIR}/buildTools/cmake/Modules)

endif ()

##----------------------------------------------------------------------------------------------------------------------
## Get shared include
include(rse)

##----------------------------------------------------------------------------------------------------------------------
## Add all the includes directories under this directory
addIncludes ()

##----------------------------------------------------------------------------------------------------------------------
# Uses VHI & VSI interfaces
addInterfaceIncludes(hardware)

##----------------------------------------------------------------------------------------------------------------------
# Use of the repository libs
useRepoLib (xcommon)
useRepoLib (common)

##----------------------------------------------------------------------------------------------------------------------
## Library Source

add_subdirectory (psu)

add_subdirectory (radioConfig)
add_subdirectory (HighSpeedEthernet)
add_subdirectory (remoteProc)
add_subdirectory (embeddedMgr)
add_subdirectory (driver)
add_subdirectory (RegDevice)
add_subdirectory (RegModel)
add_subdirectory (bus)
add_subdirectory (I2cToSpi)

add_subdirectory (RrhFreqPolicy)
add_subdirectory (delay)
add_subdirectory (systemFpga)
add_subdirectory (systemClockInput)
add_subdirectory (systemReboot)
add_subdirectory (RssiEmu)

add_subdirectory (agc)
add_subdirectory (attenuator)
add_subdirectory (caldata)
add_subdirectory (cpri)
add_subdirectory (cpriDelays)
add_subdirectory (DelaysMgr)
add_subdirectory (equaliser)
add_subdirectory (fpga)
add_subdirectory (frequencyconstants)
add_subdirectory (gpio)
add_subdirectory (hardwareSettings)
add_subdirectory (hdlc)
add_subdirectory (led)
add_subdirectory (License)
add_subdirectory (mdio)
add_subdirectory (synth)
add_subdirectory (systemled)
add_subdirectory (carrier)
add_subdirectory (radio)
add_subdirectory (FpgaComms)
add_subdirectory (FpgaMsgTokens)
add_subdirectory (FpgaCommsMsg)
add_subdirectory (fault)
add_subdirectory (heartbeat)
add_subdirectory (sfpdata)
add_subdirectory (FpgaIrqTask)

add_subdirectory (FpgaIrqEmu)
add_subdirectory (SpiEmu)
add_subdirectory (FpgaRegsEmu)
add_subdirectory (FpgaCommsEmu)

add_subdirectory (memory)
add_subdirectory (sensors)
add_subdirectory (refClock)
add_subdirectory (rfModule)
add_subdirectory (retMotor)
add_subdirectory (serial)
add_subdirectory (rfBandData)
add_subdirectory (resamplerData)
add_subdirectory (regData)

##----------------------------------------------------------------------------------------------------------------------
## Perform all of the common tasks required to create the library package
include(libraryCommonTasks)



