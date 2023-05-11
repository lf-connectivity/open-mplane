# Cmake file for helper/common/Model

add_sources (SOURCES
	#src/DiscoveryTestHelper.cpp
	src/DpdTestHelper.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(helperCommonModel)

## Tests
##add_subdirectory(gtest)
