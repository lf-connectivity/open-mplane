##======================================================================================================================
## CPPUNIT CMake functions
##
##======================================================================================================================

## Guard from multiple includes
if (_INCLUDED_CPPUNIT)
	return ()
endif ()
set (_INCLUDED_CPPUNIT 1)

## Guard - only use for x86_64
if (NOT ${TARGET} STREQUAL "x86_64")
	return ()
endif ()


##----------------------------------------------------------------------------------------------------------------------
## Set up for cppunit compiling
include_directories (${LOCAL_INSTALL_DIR}/include)
#find_library (CPPUNIT_LIB2 cppunit PATHS ${LOCAL_INSTALL_DIR}/lib)
#message("CPPUNIT=${CPPUNIT_LIB2} LOCAL_INSTALL_DIR=${LOCAL_INSTALL_DIR}")
set (CPPUNIT_LIB ${LOCAL_INSTALL_DIR}/lib/libcppunit.a)

##----------------------------------------------------------------------------------------------------------------------
## addCppunitTest(<name> <libs> <sources>...)
## 
## Function that adds a CPPUNIT Test based test executable, <name>, built from <sources> and adds the test <name>
## so that CTest will run it. Adds the current library and any additional libs specified by <libs> to the link targets.
##
macro (addCppunitTest name libs)

if (${TARGET} STREQUAL "x86_64")
	# Create the test executable from the sources
	add_executable(${name} ${ARGN})
	
	# Link with gtest lib and this project lib
	getCurrentLib(lib)
	addLinkLibs(${name} ${CPPUNIT_LIB} ${lib} ${libs})
    target_link_libraries(${name} rt)
	
	# Create a test
	add_test(${name} ${name})
endif()

endmacro (addCppunitTest)

