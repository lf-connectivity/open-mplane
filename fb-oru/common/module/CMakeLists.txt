# Cmake file for module

add_sources (SOURCES
	src/Module.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(module)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load cppunit
	include (cppunit)

    set (libs "")
    addRepoLib (libs xcommon)

	addTestCommon(TEST_COMMON common)

	include_directories(test)
	set(test_src
		test/ModuleTestCase.cpp
		test/ModuleTests.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addCppunitTest(module_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(module_TEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(module_TEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

