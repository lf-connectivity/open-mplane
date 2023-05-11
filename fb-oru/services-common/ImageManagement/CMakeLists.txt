# Cmake file for common/rxService

add_sources (SOURCES
	src/CommonImageManagement.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(ImageManagement)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    # Add code coverage
    include (coverage)

    # Add memory leak check
    include (valgrind)


endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

