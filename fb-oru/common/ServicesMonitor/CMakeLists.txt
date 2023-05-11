# Cmake file for ServicesMonitor

add_sources (SOURCES
	src/KickWatchdog.cpp
	src/ServicesMonitor.cpp
	src/ServicesMonitorFactory.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(ServicesMonitor)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	# Load cppunit
	include (cppunit)

	addTestCommon(TEST_COMMON common)

	include_directories(test)
	set(test_src
		test/ServicesMonitorTestCase.cpp
		test/ServicesMonitorTests.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addCppunitTest(ServicesMonitor_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(ServicesMonitor_TEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(ServicesMonitor_TEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

