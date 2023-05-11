/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FrequencyUtils.h
 * \brief     Frequency helper functions
 *
 *
 * \details   Contains a collection of useful functions that operate on the Frequency interface but don't need any internal
 * 			  data details.
 *
 */


#ifndef FREQUENCYUTILS_H_
#define FREQUENCYUTILS_H_

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <vector>
#include <iostream>

#include "Frequency.h"

//=============================================================================================================
// NAMESPACE: Mplane::FrequencyUtils
//=============================================================================================================
namespace Mplane {

namespace FrequencyUtils {


	/**
	 * @brief range
	 *
	 * Utility method that takes a centre frequency and a bandwidth and converts them into a min & max
	 * frequency
	 *
	 * @param centre	Centre frequency
	 * @param bandwidth	Bandwidth frequency
	 * @return vector of 2 frequencies index 0 = min, index 1 = max
	 */
	inline const std::vector<Frequency> range(const Frequency& centre, const Frequency& bandwidth)
	{
		std::vector<Frequency> min_max ;

		// remove const
		Frequency halfBandwidth = bandwidth ;
		halfBandwidth /= 2 ;
		Frequency centreFreq = centre ;


		if (centreFreq >= halfBandwidth)
			min_max.push_back(centreFreq - halfBandwidth) ;
		else
			min_max.push_back(0.0) ;
		min_max.push_back(centreFreq + halfBandwidth) ;

		return min_max ;
	}

	/**
	 * @brief range
	 *
	 * Utility method that takes a centre frequency and a bandwidth and converts them into a min & max
	 * frequency
	 *
	 * @param centre	Centre frequency
	 * @param bandwidth	Bandwidth frequency
	 * @param min		Reference to minimum frequency (set by function)
	 * @param max		Reference to maximum frequency (set by function)
	 */
	inline void range(const Frequency& centre, const Frequency& bandwidth, Frequency& min, Frequency& max)
	{
		std::vector<Frequency> min_max = range(centre, bandwidth) ;
		min = min_max.at(0) ;
		max = min_max.at(1) ;
	}

} // namespace FrequencyUtils

} // namespace Mplane



#endif /* FREQUENCYUTILS_H_ */
