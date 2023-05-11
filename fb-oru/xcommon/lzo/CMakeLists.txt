# Cmake file for lzo

add_sources (SOURCES
	src/minilzo.cpp
	src/Lzo.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(lzo)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/minilzo_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(lzo_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(lzo_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(lzo_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

