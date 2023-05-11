# Cmake file for common/SpiEmu

if ( ${TARGET} STREQUAL "x86_64" )

    add_sources (SOURCES
    	src/SpiEmu.cpp
    	src/SpiBusEmu.cpp
    	src/plugins/SpiPluginBase.cpp
    	src/plugins/SpiPluginAttnPE4302.cpp
    	src/plugins/SpiPluginAd9122.cpp
    	src/plugins/SpiPluginAmc7812.cpp
    	src/plugins/Amc7812/Amc7812Handler.cpp
    	src/plugins/Amc7812/Amc7812Profile.cpp
    	src/plugins/Amc7812/Amc7812Temperature.cpp
    	src/plugins/Amc7812/Amc7812Adc.cpp
    	src/plugins/Amc7812/Amc7812Voltage.cpp
    	src/plugins/Amc7812/Amc7812PowerDetect.cpp
    )

    ## Cppcheck
    include (cppcheck)
    addCppcheck(SpiEmu)

if ( ${BUILD_TEST_SHARED} )

    	# Add code coverage
    	include (coverage)

    	# Add memory leak check
    	include (valgrind)


endif ()

endif ()

