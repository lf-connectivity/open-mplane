# Cmake file for imageManagement

add_sources (SOURCES
	src/ImageTask.cpp
	src/ImageTypes.cpp
	src/ImageFundamental.cpp
	src/ImageBase.cpp
	src/Md5List.cpp
	src/ImageManagement.cpp
	src/AppImage.cpp
	src/LibImage.cpp
	src/NullLibImage.cpp
	src/FpgaImage.cpp
	src/OsImage.cpp
	src/PkgImage.cpp
	src/ZipImage.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(imageManagement)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

    set (libs "")
    addRepoLib (libs xcommon)

	addTestCommon(TEST_COMMON common)

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/tests.cpp
		gtest/im_fixture.cpp
		gtest/ImageManagement_unittest.cpp
		gtest/ImageTypes_unittest.cpp
		gtest/ImageBase_unittest.cpp
		gtest/AppImage_unittest.cpp
		gtest/LibImage_unittest.cpp
		gtest/OsImage_unittest.cpp
		gtest/PkgImage_unittest.cpp
		gtest/FpgaImage_unittest.cpp
		gtest/Md5List_unittest.cpp

		# Test Mock
		${TEST_COMMON}/TestIloggerFactory.cpp
		${TEST_COMMON}/BootEnvSingleton.cpp
	)
#SDP#	addGtest(imageManagement_GTEST "${libs}" ${gtest_src})

	# Add code coverage
	include (coverage)
#SDP#	addCoverage(imageManagement_GTEST)
	# Add memory leak check
	include (valgrind)
#SDP#	addMemcheck(imageManagement_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

