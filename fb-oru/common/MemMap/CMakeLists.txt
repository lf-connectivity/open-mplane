# Cmake file for MemMap

add_sources (SOURCES
	src/MemMap-dummy.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(MemMap)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/MemMap_unittest.cpp
		gtest/MemMapTests.cpp
	)
	addGtest(MemMap_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(MemMap_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(MemMap_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

