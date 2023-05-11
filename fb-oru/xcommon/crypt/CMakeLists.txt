# Cmake file for crypt

add_sources (SOURCES
	src/Crypt.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(crypt)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Crypt_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(crypt_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(crypt_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(crypt_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

