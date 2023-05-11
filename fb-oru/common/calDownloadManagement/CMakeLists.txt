# Cmake file for imageManagement

add_sources (SOURCES
	src/CalDownloadManagement.cpp
	src/CalDownloadMgrSingleton.cpp
	src/CalDownload.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(calDownloadManagement)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    ## Libraries used
    addRepoLib( libs  xcommon )

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/cm_fixture.cpp
		gtest/CalDownload_unittest.cpp
		gtest/CalDownloadManagement_unittest.cpp
        gtest/RxCalDownload.cpp
        gtest/TxCalDownload.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(calDownloadManagement_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(calDownloadManagement_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(calDownloadManagement_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

