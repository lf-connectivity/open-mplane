# Cmake file for common/FpgaIrqEmu

if ( ${TARGET} STREQUAL "x86_64" )

    add_sources (SOURCES
    	src/FpgaIrqEmu.cpp
    	src/FpgaIrqDevice.cpp
    )

    ## Cppcheck
    include (cppcheck)
    addCppcheck(FpgaIrqEmu)

if ( ${BUILD_TEST_SHARED} )

    set (libs "")
    addRepoLib(libs xcommon)
    addRepoLib(libs common)

    # Load google test
    include (gtest)
    
    addTestCommon(TEST_COMMON common)
    addTestCommon(TEST_HW_COMMON hardware)
    
    include_directories(gtest)
    set(gtest_src
        gtest/FpgaIrqEmu_unittest.cpp
        gtest/tests.cpp
        ${TEST_COMMON}/TestIloggerFactory.cpp
        ${TEST_COMMON}/BootEnvSingleton.cpp
    )
    addGtest(FpgaIrqEmu_GTEST "${libs}" ${gtest_src})

endif ()

endif ()

