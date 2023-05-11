# Cmake file for common/Rti

add_sources (SOURCES
	src/Tif.cpp
	src/RtiMsgEditor.cpp
	src/RtiMsgHandler.cpp
	src/RtiTelnet.cpp
	src/RtiSettings.cpp
	src/TestInterfaceBase.cpp
	src/CmdNode/DirCmd.cpp
	src/CmdNode/EntryCmd.cpp
	src/Nodes/DirClass.cpp
	src/Nodes/EntryFunc.cpp
	src/Nodes/EntryVar.cpp
	src/Nodes/RtiDirEntry.cpp
	src/Nodes/TestReadVar.cpp
	src/Nodes/TestVar.cpp
	src/Nodes/TestWriteVar.cpp
	src/ScriptsNode/DirScripts.cpp
	src/ScriptsNode/DirScriptsBase.cpp
	src/ScriptsNode/EntryScripts.cpp
	src/SettingsNode/EntrySettings.cpp
	src/Ati.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Rti)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TYPE} STREQUAL "radio") )

    set (libs "common")
	addRepoLib(libs xcommon)
	addRepoLib(libs swtools shared)

    # common hardware
	addRepoLib(libs hardware common)

	addShared(TIF_SHARED tif)

	# Load google test
	include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/DirNode_unittest.cpp
		gtest/GtestFile.cpp
		gtest/rti_fixture.cpp
		gtest/rti_unittest.cpp
		gtest/RtiMsgEditor_unittest.cpp
		gtest/rtiserver_unittest.cpp
		gtest/itif_unittest.cpp
		gtest/RtiTests.cpp
		gtest/Model/TestingTestInterface.cpp
		gtest/Model/TestingTestMethods.cpp
		gtest/Model/TestInjected.cpp

		# Test mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_COMMON}/TestImageManagement.cpp
	    ${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_HW_COMMON}/TestFpgaKernel.cpp
	    ${TEST_HW_COMMON}/TestFpgaMock.cpp
	    ${TEST_HW_COMMON}/TestSystemClockInput.cpp
	    ${TEST_HW_COMMON}/TestSystemClockInputSingleton.cpp
	    ${TEST_HW_COMMON}/TestBus.cpp
	)
	addGtest(Rti_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Rti_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(Rti_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TYPE} STREQUAL "radio") )

