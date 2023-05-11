# Cmake file for helper/ORANRRH/Model

add_sources (SOURCES
	src/YangConfigTestHelper.cpp
	src/YangTestTestHelper.cpp
	src/Dot1agdMonTestHelper.cpp
	src/NetopeerMonTestHelper.cpp
	src/YangManagerTestHelper.cpp
)


## Cppcheck
include (cppcheck)
addCppcheck(ORANRRHModel)

