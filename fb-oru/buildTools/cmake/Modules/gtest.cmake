##======================================================================================================================
## Google Test CMake functions
##
##======================================================================================================================

## Guard from multiple includes
if (_INCLUDED_GTEST)
	return ()
endif ()
set (_INCLUDED_GTEST 1)

##----------------------------------------------------------------------------------------------------------------------
if (${TARGET} STREQUAL "x86_64")
    find_package (gtest 1.7.0 REQUIRED PATHS ${GITDIR}/buildTools/sysroot/lib)
    include_directories (SYSTEM ${gtest_INCLUDE_DIRS})
endif ()


##----------------------------------------------------------------------------------------------------------------------
## addGtest(<name> <libs> <sources>...)
## 
## Function that adds a Google Test based test executable, <name>, built from <sources> and adds the test <name>
## so that CTest will run it. Adds the current library and any additional libs specified by <libs> to the link targets.
##
macro (addGtest name libs)

    if (${TARGET} STREQUAL "x86_64")
    	# Create the test executable from the sources
    	add_executable(${name} ${ARGN})
    	
    	# Link with gtest lib and this project lib
    	getCurrentLib(lib)
    	addLinkLibs(${name} gtest_main ${lib} ${libs})
        target_link_libraries(${name} rt)
    	
    	# Create a test
    	add_test(NAME ${name} COMMAND ${name} --gtest_output=xml:gtest.xml)
    
    endif()

endmacro (addGtest)

##----------------------------------------------------------------------------------------------------------------------
## addGtestNolib(<name> <libs> <sources>...)
## 
## Function that adds a Google Test based test executable, <name>, built from <sources> and adds the test <name>
## so that CTest will run it. Adds any additional libs specified by <libs> to the link targets.
##
macro (addGtestNolib name libs)

    if (${TARGET} STREQUAL "x86_64")
    	# Create the test executable from the sources
    	add_executable(${name} ${ARGN})
    	
    	# Link with gtest lib and this project lib
    	getCurrentLib(lib)

    	addLinkLibs(${name} gtest_main ${libs})
        target_link_libraries(${name} rt)
    	
    	# Create a test
    	add_test(NAME ${name} COMMAND ${name} --gtest_output=xml:gtest.xml)
    
    endif()

endmacro (addGtestNolib)


