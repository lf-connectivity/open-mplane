# Cmake file for observer

add_sources (SOURCES
)

## Cppcheck
include (cppcheck)
addCppcheck(observer)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

    set (libs "")
    addRepoLib (libs xcommon)
	addTestCommon(TEST_COMMON common)

	include_directories(gtest)
	set(gtest_src
		gtest/Observer_unittest.cpp
		
		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addGtest(observer_GTEST "${libs}" ${gtest_src})

	# Load cppunit
	include (cppunit)

	include_directories(test)
	set(test_src
		test/ObserverTestCase.cpp
		test/ObserverTestCode.cpp
		test/ObserverTests.cpp
		
		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addCppunitTest(observer_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(observer_TEST)
	addCoverage(observer_GTEST)
	
	# Add memory leak check
	include (valgrind)
	addMemcheck(observer_TEST)
	addMemcheck(observer_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

