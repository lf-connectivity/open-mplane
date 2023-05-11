/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariant_benchmark.cpp
 * \brief     Run benchmark tests on DataVariant
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <gtest/gtest.h>

#include <string.h>
#include <iostream>

#include <memory>
#include "Benchmark.h"
#include "DataVariant.h"

using namespace Mplane ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

static std::stringstream oss ;

	void showDv(const DataVariant& dv)
	{
		oss << dv.getName() << std::endl ;
		oss << dv.toString() << std::endl ;
		oss << dv.toInt() << std::endl ;
		oss << dv.toFloat() << std::endl ;
		oss << dv.toBool() << std::endl ;
//		oss << dv.toComplex() << std::endl ;
	}

}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, Benchmark)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	bench->start("dv") ;

	static std::stringstream ss ;

//	const unsigned ITERATIONS{100000} ;
	const unsigned ITERATIONS{10000} ;
	for (unsigned iter=1; iter <= ITERATIONS; ++iter)
	{
		// process all types

		// string
		{
			DataVariant dv(DataVariantType::String, "test") ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
		}

		// Int
		{
			DataVariant dv(DataVariantType::Int, "test") ;
			dv.set("123") ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toInt() << std::endl ;
			dv.setInt(456) ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toInt() << std::endl ;
		}

		// Float
		{
			DataVariant dv(DataVariantType::Float, "test") ;
			dv.set("123.456") ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toFloat() << std::endl ;
			dv.setFloat(456.789) ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toFloat() << std::endl ;
		}

//		// Complex
//		{
//			DataVariant dv(DataVariantType::Complex, "test") ;
//			dv.set("123.456-j678.901") ;
//			ss << dv.getName() << std::endl ;
//			ss << dv.toString() << std::endl ;
//			ss << dv.toComplex() << std::endl ;
//			dv.setComplex(std::complex<float>(1.1, -2.2)) ;
//			ss << dv.getName() << std::endl ;
//			ss << dv.toString() << std::endl ;
//			ss << dv.toComplex() << std::endl ;
//		}

		// Bool
		{
			DataVariant dv(DataVariantType::Bool, "test") ;
			dv.set("true") ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toBool() << std::endl ;
			dv.setBool(false) ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toBool() << std::endl ;
		}

	}

	std::cerr << test_info->name() << " Benchmark time: " << bench->stop("dv") << std::endl;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, BenchmarkInt)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	bench->start("dv") ;

	static std::stringstream ss ;

//	const unsigned ITERATIONS{1000000} ;
	const unsigned ITERATIONS{100000} ;
	for (unsigned iter=1; iter <= ITERATIONS; ++iter)
	{
		// Int
		{
			DataVariant dv(DataVariantType::Int, "test") ;
			dv.set("123") ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toInt() << std::endl ;
			dv.setInt(456) ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toInt() << std::endl ;
		}
	}

	std::cerr << test_info->name() << " Benchmark time: " << bench->stop("dv") << std::endl;
}


//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, BenchmarkFull)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	bench->start("dv") ;

	const std::vector<DataVariantType::Type> TYPE_LIST{
		DataVariantType::String,
		DataVariantType::Int,
		DataVariantType::Float,
//		DataVariantType::Complex,
		DataVariantType::Bool,
	};
//	const unsigned ITERATIONS{10000} ;
	const unsigned ITERATIONS{1000} ;
	for (unsigned iter=1; iter <= ITERATIONS; ++iter)
	{
		// process all types
		for (auto type : TYPE_LIST)
		{
			DataVariant dv(type, "test") ;
			showDv(dv) ;

			dv.set("123") ;
			showDv(dv) ;

//			dv.setComplex( std::complex<float>(675.893, 26727.6897)) ;
//			showDv(dv) ;

			dv.setBool(true) ;
			showDv(dv) ;

			dv.setInt(456) ;
			showDv(dv) ;

			dv.setFloat(789.01234) ;
			showDv(dv) ;
		}
	}

	std::cerr << test_info->name() << " Benchmark time: " << bench->stop("dv") << std::endl;

//	std::cerr << oss.str() << std::endl ;
}

//-------------------------------------------------------------------------------------------------------------
TEST(DataVariant, BenchmarkComplex)
{
	const ::testing::TestInfo* const test_info =
	  ::testing::UnitTest::GetInstance()->current_test_info();

	std::cout << std::endl << "*** " << test_info->test_case_name() << " Tests ***" <<  std::endl;
	std::cout << test_info->name() << " - START" <<  std::endl;

	std::shared_ptr<Benchmark> bench(Benchmark::getInstance()) ;
	bench->start("dv") ;

	static std::stringstream ss ;

	const unsigned ITERATIONS{100000} ;
	for (unsigned iter=1; iter <= ITERATIONS; ++iter)
	{

		// Complex
		{
			DataVariant dv(DataVariantType::Complex, "test") ;
			dv.set("123.456-j678.901") ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toComplex() << std::endl ;
			dv.setComplex(std::complex<float>(1.1, -2.2)) ;
			ss << dv.getName() << std::endl ;
			ss << dv.toString() << std::endl ;
			ss << dv.toComplex() << std::endl ;
		}

	}

	std::cerr << test_info->name() << " Benchmark time: " << bench->stop("dv") << std::endl;
}
