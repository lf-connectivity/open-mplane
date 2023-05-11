# Cmake file for AnsiEsc
add_sources (SOURCES
	src/AnsiEsc.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(AnsiEsc)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/AnsiEsc_unittest.cpp
	)
	addGtest(AnsiEsc_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(AnsiEsc_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(AnsiEsc_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

