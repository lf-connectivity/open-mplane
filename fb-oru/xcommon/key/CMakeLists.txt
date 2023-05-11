# Cmake file for key

add_sources (SOURCES
	src/GlobalKey.cpp
	src/Key.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(key)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	set (libs "")
#	addRepoLib (libs common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
#		gtest/bitTable.cpp
		gtest/Key_unittest.cpp
		gtest/tests.cpp
	)
	addGtest(key_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(key_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(key_GTEST)
	
	
	## Utils
	set(convert_src
		utils/convertTem.cpp
	)
	
	# Create the test executable from the sources
	add_executable(convertTem ${convert_src})
	
	# Link with this project lib
	getCurrentLib(lib)
	addLinkLibs(convertTem ${lib} ${libs})
    target_link_libraries(convertTem rt)
	

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

