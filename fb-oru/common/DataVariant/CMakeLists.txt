# Cmake file for DataVariant


add_sources (SOURCES
	src/DataVariant.cpp
	src/DataVariantSettings.cpp
	src/DataVariantBase.cpp
	src/DataVariantList.cpp
	src/DataVariantVector.cpp
	
	# DvType
	src/DvType/DvTypeBase.cpp
	src/DvType/DvTypeNone.cpp
	src/DvType/DvTypeInt.cpp
	src/DvType/DvTypeFloat.cpp
	src/DvType/DvTypeComplex.cpp
	src/DvType/DvTypeString.cpp
	src/DvType/DvTypeEnum.cpp
	src/DvType/DvTypeBool.cpp
	src/DvType/DvTypeEnum.cpp
	src/DvType/DvTypeFreq.cpp
	src/DvType/DvTypePower.cpp
	src/DvType/DvTypeUint.cpp
	src/DvType/DvTypeLong.cpp
	src/DvType/DvTypeDouble.cpp
	src/DvTypeFactory.cpp
	
	# DataVariantType
	src/DataVariantType/DataVariantTypeBase.cpp
	src/DataVariantType/DataVariantTypes.cpp
	src/DataVariantType/DataVariantInt.cpp
	src/DataVariantType/DataVariantFloat.cpp
	src/DataVariantType/DataVariantComplex.cpp
	src/DataVariantType/DataVariantEnum.cpp
	src/DataVariantType/DataVariantBool.cpp
	src/DataVariantType/DataVariantFreq.cpp
	src/DataVariantType/DataVariantPower.cpp
	src/DataVariantType/DataVariantUint.cpp
	src/DataVariantType/DataVariantLong.cpp
	src/DataVariantType/DataVariantDouble.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(DataVariant)

if ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

	# Load google test
	include (gtest)

	include_directories(gtest)
	set(gtest_src
		gtest/DataVariantBase_unittest.cpp
		gtest/DataVariant_benchmark.cpp
		gtest/DataVariant_unittest.cpp
		gtest/DataVariantSettings_unittest.cpp
		gtest/DataVariantList_unittest.cpp
		gtest/DataVariantVector_unittest.cpp
		gtest/Limits_unittest.cpp

	)
	addGtest(DataVariant_GTEST "" ${gtest_src})

	# Add code coverage
	include (coverage)
	addCoverage(DataVariant_GTEST)
	# Add memory leak check
	include (valgrind)
	addMemcheck(DataVariant_GTEST)

endif ( (${TARGET} STREQUAL "x86_64") AND (${BUILD_TEST_SHARED}) )

