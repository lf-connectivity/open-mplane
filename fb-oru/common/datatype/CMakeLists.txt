# Cmake file for datatype

add_sources (SOURCES
	src/Frequency.cpp
	src/FrequencyOffset.cpp
	src/FrequencyStatic.cpp
	src/Power.cpp
	src/Temperature.cpp
	src/Tokeniser.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(datatype)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/FrequencyOffsetTestCase.cpp
		gtest/FrequencyTestCase.cpp
		gtest/PowerTestCase.cpp
		gtest/TemperatureTestCase.cpp
		gtest/TokeniserTestCase.cpp
	)
	addGtest(datatype_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(datatype_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(datatype_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

