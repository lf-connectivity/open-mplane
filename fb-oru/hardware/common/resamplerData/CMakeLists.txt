# Cmake file for common/resamplerData

add_sources (SOURCES
	src/CommonResamplerConfig.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(resamplerData)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/CommonResamplerConfigTests.cpp
		gtest/CommonResamplerConfigTestCase.cpp
	)
	addGtest(Resampler_GTEST "common" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Resampler_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(Resampler_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )
