/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      bitTable.cpp
 * \brief     
 *
 *
 * \details   
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include <time.h>

#include <iostream>
#include <random>
#include <bitset>
#include <vector>


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main(void)
{
	std::default_random_engine generator( (int) ::time(0) );
	std::uniform_int_distribution<int> distribution(0,127);


	std::bitset<128> bits ;
	std::vector<uint8_t> table(128) ;
	std::vector<uint8_t> reverse(128) ;

	for (int i=0; i<128; ++i)
	{
		int val(distribution(generator)) ;
		while (bits[val])
		{
			val = distribution(generator) ;
		}

		table[i] = (uint8_t)(val) ;
		bits.set(val) ;

		// generate reverse lookup
		reverse[val] = i % 32 ;
	}

	// table
	unsigned expected{0} ;
	unsigned sum{0} ;
	for (unsigned i=0; i < 128;)
	{
		for (unsigned j=0; j < 16; ++j, ++i)
		{
			printf("0x%02x, ", table[i]) ;
			sum += table[i] ;
			expected += i ;
		}

		std::cout << std::endl ;
	}
	std::cout << std::endl ;


	// reverse lookup
	for (unsigned i=0; i < 128;)
	{
		for (unsigned j=0; j < 16; ++j, ++i)
		{
			printf("0x%02x, ", reverse[i]) ;
		}

		std::cout << std::endl ;
	}
	std::cout << std::endl ;



	if (sum != expected)
		std::cerr << "Calculation error!" << std::endl ;


	return 0 ;
}

