# Cmake file for Benchmark

add_sources (SOURCES
	src/Benchmark.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(Benchmark)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/Benchmark_unittest.cpp
	)
	addGtest(Benchmark_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(Benchmark_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(Benchmark_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

