# Cmake file for common/rfBandData

add_sources (SOURCES
	src/CommonRfBandConfig.cpp
	src/CommonRxRfBandConfig.cpp
	src/CommonTxRfBandConfig.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(rfBandData)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/CommonRFBandConfigTests.cpp
		gtest/CommonRxRFBandTestCase.cpp
		gtest/CommonTxRFBandTestCase.cpp
	)
	addGtest(RFBand_GTEST "common" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(RFBand_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(RFBand_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
