# Cmake file for WaveFile

add_sources (SOURCES
	src/CaptureWave.cpp
	src/CaptureWaveData.cpp
	src/CaptureWaveHeader.cpp
	src/PlaybackWave.cpp
	src/PlaybackWaveHeader.cpp
	src/WaveFileHeader.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(WaveFile)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/CaptureWaveHeader_unittest.cpp
		gtest/PlaybackWave_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(WaveFile_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(WaveFile_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(WaveFile_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

