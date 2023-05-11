# Cmake file for ros-tests
if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")

	addRepoLib(libs xcommon)

	addTestCommon(TEST_COMMON common)

    ##--------------------------------------------------------
    ## i2cenv mock
    set(i2cenv_src
        gtest/mock-bin/I2cEnv.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
    )
	# Create the test executable from the sources
	add_executable(i2cenv ${i2cenv_src})

	# Link with gtest lib and this project lib
	getCurrentLib(lib)
	addLinkLibs(i2cenv ${lib} ${libs})
    target_link_libraries(i2cenv rt)

    ##--------------------------------------------------------
    ## nc mock
    set(nc_src
        gtest/mock-bin/nc.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
    )
	# Create the test executable from the sources
	add_executable(nc ${nc_src})

	# Link with gtest lib and this project lib
	getCurrentLib(lib)
	addLinkLibs(nc ${lib} ${libs})
    target_link_libraries(nc rt)

    ##--------------------------------------------------------
    ## reboot mock
    set(reboot_src
        gtest/mock-bin/reboot.cpp
    )
	# Create the test executable from the sources
	add_executable(reboot ${reboot_src})

	# Link with gtest lib and this project lib
	getCurrentLib(lib)
	addLinkLibs(reboot ${lib} ${libs})
    target_link_libraries(reboot rt)


    ##--------------------------------------------------------
    ## Tests

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/rc_unittest.cpp
		gtest/tests.cpp

		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
	addGtest(ros_GTEST "${libs}" ${gtest_src})
   	add_dependencies(ros_GTEST i2cenv nc reboot)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

