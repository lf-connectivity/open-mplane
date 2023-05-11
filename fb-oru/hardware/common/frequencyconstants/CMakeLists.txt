# Cmake file for common/frequencyconstants

add_sources (SOURCES
	src/CommonSawFrequencyConst.cpp
	src/CommonRxFrequencyConst.cpp
	src/CommonTxFrequencyConst.cpp

	src/RadioConfigSawFreqConst.cpp
	src/RadioConfigRxFreqConst.cpp
	src/RadioConfigTxFreqConst.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(frequencyconstants)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/CommonFrequencyConstTests.cpp
		gtest/CommonRxFrequencyConstantTestCase.cpp
		gtest/CommonTxFrequencyConstTestCase.cpp
	)
	addGtest(frequencyconstants_GTEST "common" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(frequencyconstants_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(frequencyconstants_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

