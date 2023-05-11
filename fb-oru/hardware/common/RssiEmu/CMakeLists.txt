# Cmake file for common/RssiEmu

if (${TARGET} STREQUAL "x86_64")

    add_sources (SOURCES
    	src/RssiEmu.cpp
    )

    ## Cppcheck
    include (cppcheck)
    addCppcheck(RssiEmu)

endif ()


if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs xcommon)
	addRepoLib (libs common)

    # Load google test
    include (gtest)

	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/CpriEmu_fixture.cpp
		gtest/CpriEmu_unittest.cpp
		gtest/tests.cpp

		# Mocks
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
        ${TEST_HW_COMMON}/FpgaRegCapture_fixture.cpp

	)
#	addGTest(RssiEmu_GTEST "${libs}" ${gtest_src})
#
	# Add code coverage
#	include (coverage)
#	addCoverage(RssiEmu_GTEST)
#
	# Add memory leak check
#	include (valgrind)
#	addMemcheck(RssiEmu_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

