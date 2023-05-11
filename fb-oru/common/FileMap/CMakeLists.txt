# Cmake file for FileMap

add_sources (SOURCES
	src/FileMap.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FileMap)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/FileMap_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(FileMap_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FileMap_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(FileMap_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

