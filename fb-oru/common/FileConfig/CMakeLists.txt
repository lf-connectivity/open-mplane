# Cmake file for FileConfig

add_sources (SOURCES
	src/FileConfigBase.cpp
	src/FileConfig.cpp
	src/FileConfigWriter.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(FileConfig)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/FileConfig_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(FileConfig_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(FileConfig_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(FileConfig_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

