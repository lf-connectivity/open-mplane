# Cmake file for task

add_sources (SOURCES
	src/Conditional.cpp
	src/Mutex.cpp
	src/RecursiveMutex.cpp
	src/Task.cpp
	src/TaskEvent.cpp
	src/TaskPeriodicEvent.cpp
	src/TaskList.cpp
	src/SystemTask.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(task)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/SystemTask_unittest.cpp
		gtest/TaskEvent_unittest.cpp
		gtest/TaskPeriodicEvent_unittest.cpp
		gtest/QueueBuffer_unittest.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addGtest(task_GTEST "${libs}" ${gtest_src})

	# Load cppunit
	include (cppunit)

	include_directories(test)
	set(test_src
		test/ConditionalTestCase.cpp
		test/MutexTestCase.cpp
		test/RecursiveMutexTestCase.cpp
		test/TaskTestCase.cpp
		test/TaskTests.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
		${TEST_COMMON}/TestImageManagement.cpp
		${TEST_COMMON}/TestImageManagementFactory.cpp
		${TEST_COMMON}/NetStatusSingleton.cpp
	)
	addCppunitTest(task_TEST "${libs}" ${test_src})

	# Add code coverage
	include (coverage)
	addCoverage(task_TEST)
	addCoverage(task_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(task_TEST)
	addMemcheck(task_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

