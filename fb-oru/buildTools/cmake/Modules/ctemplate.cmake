##======================================================================================================================
## CTemplate CMake functions
##
##======================================================================================================================

## Guard from multiple includes
if (_INCLUDED_CTEMPLATE)
	return ()
endif ()
set (_INCLUDED_CTEMPLATE 1)

## Guard - only use for x86_64
if (NOT ${TARGET} STREQUAL "x86_64")
	return ()
endif ()


##----------------------------------------------------------------------------------------------------------------------
## Set up for cppunit compiling
include_directories (${LOCAL_INSTALL_DIR}/include)
set (CTEMPLATE_LIB ${LOCAL_INSTALL_DIR}/lib/libctemplate.a)

##----------------------------------------------------------------------------------------------------------------------
## addCTemplate(<var>)
## 
## Function that adds a CTEMPLATE lib to list of libs. x86_64 only
##
macro (addCTemplate var)

if (${TARGET} STREQUAL "x86_64")

    list (APPEND ${var} ${CTEMPLATE_LIB})
    set (${var} ${${var}} PARENT_SCOPE)
	
endif()

endmacro (addCTemplate)

