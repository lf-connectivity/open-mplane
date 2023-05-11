# Cmake file for common/CpriFibreEmu

if (${TARGET} STREQUAL "x86_64")

    add_sources (SOURCES
    	src/CpriFibreEmu.cpp
    )

    ## Cppcheck
    include (cppcheck)
    addCppcheck(CpriFibreEmu)

endif ()


if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
	addRepoLib (libs xcommon)
	addRepoLib (libs common)
	addRepoLib (libs hardware common)

    # Load google test
    include (gtest)

	addTestCommon(TEST_COMMON common)
	addTestCommon(TEST_HW_COMMON hardware)

	include_directories(gtest)
	set(gtest_src
		gtest/CpriEmu_fixture.cpp
		gtest/CpriEmu_unittest.cpp
		gtest/tests.cpp

		# Mocks
		${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
	    ${TEST_HW_COMMON}/TestFpgaKernel.cpp
        ${TEST_HW_COMMON}/TestFpgaMock.cpp
        ${TEST_HW_COMMON}/FpgaRegCapture_fixture.cpp

	)
	addGTest(CpriFibreEmu_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(CpriFibreEmu_GTEST)

	# Add memory leak check
	include (valgrind)
	addMemcheck(CpriFibreEmu_GTEST)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

