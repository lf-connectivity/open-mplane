# Cmake file for helper/common/Model

add_sources (SOURCES
	src/FibreTestHelper.cpp
	src/AgcTestHelper.cpp
	src/AlarmsTestHelper.cpp
	src/CalTestHelper.cpp
	src/CarrierTestHelper.cpp
	src/CarrierFreqOffsetTestHelper.cpp
	src/EmbeddedTestHelper.cpp
	src/EqualiserTestHelper.cpp
	src/DelaysTestHelper.cpp
	src/DevicesRxadcTestHelper.cpp

	src/OranFpgaTestHelper.cpp
	src/FpgaTestHelper.cpp
	src/FtpTestHelper.cpp
	src/FreqConstTestHelper.cpp
	src/GpioTestHelper.cpp
	src/HeartbeatTestHelper.cpp
	src/ImagesAppTestHelper.cpp
	src/ImagesFpgaTestHelper.cpp
	src/ImagesLibTestHelper.cpp
	src/ImagesOsTestHelper.cpp
	src/ImagesTestHelper.cpp
	src/IpTestHelper.cpp
	src/IpListTestHelper.cpp
	src/LedTestHelper.cpp
	src/PsuTestHelper.cpp
	src/RegDevicesTestHelper.cpp
	src/SystemLoggingTestHelper.cpp
	src/SystemBootTestHelper.cpp
	src/SystemTcpTestHelper.cpp
	src/SystemIpTestHelper.cpp
	src/SystemMemTestHelper.cpp
	src/SystemConfigTestHelper.cpp
	src/SystemTestHelper.cpp
    src/TxPclTestHelper.cpp
	src/PaTestHelper.cpp
    src/VswrTestHelper.cpp
    src/I2cTestHelper.cpp
    src/RxPortTestHelper.cpp
    src/TxPortTestHelper.cpp
    src/SrxPortTestHelper.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(helperCommonModel)

## Tests
#SDP#add_subdirectory(gtest)
