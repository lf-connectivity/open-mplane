# Cmake file for common/License

add_sources (SOURCES
	src/SavedFeature.cpp
	src/SavedGenericFeature.cpp
	src/SavedKey.cpp
	src/SavedInternalKey.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(License)

if (${TARGET} STREQUAL "x86_64")

	set (libs "")
	addRepoLib(libs common)
	addRepoLib(libs xcommon)

	addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HARDWARE_COMMON hardware)


	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/SavedFeature_unittest.cpp
		gtest/SavedKey_unittest.cpp
		gtest/tests.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(License_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(License_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(License_GTEST)


endif (${TARGET} STREQUAL "x86_64")

