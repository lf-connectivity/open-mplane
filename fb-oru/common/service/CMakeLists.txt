# Cmake file for service

add_sources (SOURCES
	src/Service.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(service)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	# Load cppunit
	include (cppunit)

	include_directories(test)
	set(test_src
		test/ServiceTestCase.cpp
		test/ServiceTests.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addCppunitTest(service_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(service_TEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(service_TEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

