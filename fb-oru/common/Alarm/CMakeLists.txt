# Cmake file for common/Alarm

add_sources (SOURCES
	src/Alarm.cpp
	src/AlarmLatched.cpp
    src/AlarmsList.cpp
    src/AlarmPackage.cpp
    src/AlarmBuilder.cpp
    src/AlarmMonitor.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Alarm)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/Alarm_unittest.cpp
		gtest/AlarmPackage_unittest.cpp
		gtest/AlarmBuilder_unittest.cpp
		gtest/AlarmMonitor_unittest.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(Alarm_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Alarm_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(Alarm_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

