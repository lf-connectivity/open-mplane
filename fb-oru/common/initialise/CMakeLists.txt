# Cmake file for initialise

add_sources (SOURCES
	src/Initialise.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(initialise)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load cppunit
	include (cppunit)

    addRepoLib( libs  xcommon )
	addTestCommon(TEST_COMMON common)

	include_directories(test)
	set(test_src
		test/InitialiseTestCase.cpp
		test/InitialiseTests.cpp
		
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addCppunitTest(initialise_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(initialise_TEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(initialise_TEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

