/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierUtils.h
 * \brief     ICarrier helper functions
 *
 *
 * \details   Contains a collection of useful functions that operate on the ICarrier interface but don't need any internal
 * 			  data details. Also includes general carrier-related utilities/templates
 *
 */


#ifndef CARRIERUTILS_H_
#define CARRIERUTILS_H_

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <vector>
#include <iostream>

#include "ICarrier.h"
#include "Frequency.h"

//=============================================================================================================
// NAMESPACE: Mplane::CarrierUtils
//=============================================================================================================
namespace Mplane {

namespace CarrierUtils {


	/**
	 * @brief Is carrier being enabled
	 *
	 * Utility method to check to see if the carrier has just been changed to state ENABLED
	 *
	 * @param carrier	Carrier object to access
	 * @return True if state changed to ENABLE
	 */
	inline const bool isEnabling(const ICarrier& carrier)
	{
		return carrier.getStateChanged() && (carrier.getState() == ICarrier::STATE_ENABLE) ;
	}

	inline const bool isEnabling(const ICarrier* carrier)
	{
		if (!carrier)
			return false ;
		return isEnabling(*carrier) ;
	}

    /**
     * @brief Is carrier being disabled
     *
     * Utility method to check to see if the carrier has just been changed to state DISABLED
     *
	 * @param carrier	Carrier object to access
     * @return True if state changed to DISABLE
     */
	inline const bool isDisabling(const ICarrier& carrier)
	{
		return carrier.getStateChanged() && (carrier.getState() == ICarrier::STATE_DISABLE) ;
	}

	inline const bool isDisabling(const ICarrier* carrier)
	{
		if (!carrier)
			return false ;
		return isDisabling(*carrier) ;
	}

    /**
     * @brief True if configured and enabled
     *
     * Method used to verify to caller that the carrier has been successfully configured
     * and that it has been enabled.
     *
	 * @param carrier	Carrier object to access
     * @return true if configured and active
     */
	inline const bool isEnabled(const ICarrier& carrier)
	{
	    return carrier.isConfigured() && (carrier.getState() == ICarrier::STATE_ENABLE) ;
	}

	inline const bool isEnabled(const ICarrier* carrier)
	{
		if (!carrier)
			return false ;
	    return isEnabled(*carrier) ;
	}

    /**
     * @brief True if carrier is active on this TX antenna
     *
     * Method used to verify to caller that the carrier is enabled and active on the specified TX path.
     *
	 * @param carrier	Carrier object to access
     * @param path zero based Tx path selector
     * @return true if active on this TX path
     */
	inline const bool isTxActive(const ICarrier& carrier, unsigned path)
	{
		// skip if Carrier not enabled
		if (!isEnabled(carrier))
			return false ;

		// see if TX container is set
		if (carrier.getTxContainer(path) == 0)
			return false ;

		// active on this antenna
	    return true ;
	}

	inline const bool isTxActive(const ICarrier* carrier, unsigned path)
	{
		if (!carrier)
			return false ;
	    return isTxActive(*carrier, path) ;
	}

    /**
     * @brief True if carrier is active on this RX antenna
     *
     * Method used to verify to caller that the carrier is enabled and active on the specified RX path.
     *
	 * @param carrier	Carrier object to access
     * @param path zero based Rx path selector
     * @return true if active on this RX path
     */
	inline const bool isRxActive(const ICarrier& carrier, unsigned path)
	{
		// skip if Carrier not enabled
		if (!isEnabled(carrier))
			return false ;

		// see if RX container is set
		if (carrier.getRxContainer(path) == 0)
			return false ;

		// active on this antenna
	    return true ;
	}

	inline const bool isRxActive(const ICarrier* carrier, unsigned path)
	{
		if (!carrier)
			return false ;
	    return isRxActive(*carrier, path) ;
	}

    /**
     * @brief True if carrier has changed
     *
     * Method used to verify to the caller that this carrier has got un-applied
     * changes
     *
	 * @param carrier	Carrier object to access
     * @return true if carrier has changes
     */
	inline const bool isChanged(const ICarrier& carrier)
	{
		return carrier.isChanged() ;
	}

	inline const bool isChanged(const ICarrier* carrier)
	{
		if (!carrier)
			return false ;
		return isChanged(*carrier) ;
	}

	/**
	 * Get the frequency bandwidth of this carrier type
	 * @param carrierType	Mplane::ICarrier type enumeration
	 * @return bandwidth as an Mplane::Frequency
	 */
	inline const Frequency typeBandwidth(const ICarrier::Type carrierType)
	{
		Frequency bandwidth ;
		switch (carrierType)
		{
			case ICarrier::CARRTYPE_WCDMA: 	bandwidth = Frequency(5.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_LTE1_4: bandwidth = Frequency(1.4, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_LTE3: 	bandwidth = Frequency(3.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_LTE5: 	bandwidth = Frequency(5.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_LTE10: 	bandwidth = Frequency(10.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_LTE15: 	bandwidth = Frequency(15.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_LTE20: 	bandwidth = Frequency(20.0, Frequency::MHz) ; break ;

			case ICarrier::CARRTYPE_PIM1_4:	bandwidth = Frequency(1.4, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_PIM3: 	bandwidth = Frequency(3.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_PIM5: 	bandwidth = Frequency(5.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_PIM10: 	bandwidth = Frequency(10.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_PIM15: 	bandwidth = Frequency(15.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_PIM20: 	bandwidth = Frequency(20.0, Frequency::MHz) ; break ;

			// Pretend to be 20MHz for these wideband type(s)
			case ICarrier::CARRTYPE_IBW153_6: bandwidth = Frequency(20.0, Frequency::MHz) ; break ;

			// 5G NR carrier types
			case ICarrier::CARRTYPE_5GNR25: bandwidth = Frequency(25.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR30: bandwidth = Frequency(30.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR40: bandwidth = Frequency(40.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR50: bandwidth = Frequency(50.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR60: bandwidth = Frequency(60.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR70: bandwidth = Frequency(70.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR80: bandwidth = Frequency(80.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR90: bandwidth = Frequency(90.0, Frequency::MHz) ; break ;
			case ICarrier::CARRTYPE_5GNR100: bandwidth = Frequency(100.0, Frequency::MHz) ; break ;

			case ICarrier::CARRTYPE_NONE: 	bandwidth = Frequency(0.0, Frequency::MHz) ; break ;

			default: 						bandwidth = Frequency(5.0, Frequency::MHz) ; break ;
		}
		return bandwidth ;
	}

	/**
	 * Debug utility that displays the contents of a vector prefixing each output by "[idx]"
	 * NOTE: Expects the vector to be 0-based
	 * @param vec	The vector to show
	 */
	template <typename T>
	inline void showVector(const std::vector<T>& vec, std::ostream& os = std::cout)
	{
		for (unsigned idx = 0; idx < vec.size(); ++idx)
		{
			if (idx > 0)
				os << " " ;
			os << "[" << idx << "]:" << vec.at(idx) ;
		}
	}

	/**
	 * Debug utility that displays the contents of a vector prefixing each output by "[idx]". Also uses the vector
	 * of change flags to mark any changed values with '*'
	 * NOTE: Expects the vectors to be 0-based
	 * @param vec	The vector to show
	 * @param changeVec	Vector of change flags (type must be convertible to boolean)
	 */
	template <typename T, typename TC>
	inline void showVector(const std::vector<T>& vec, std::vector<TC> changeVec, std::ostream& os = std::cout)
	{
		for (unsigned idx = 0; idx < vec.size(); ++idx)
		{
			if (idx > 0)
				os << " " ;
			os << "[" << idx << "]:" << vec.at(idx) ;
			if (changeVec.at(idx))
				os << "*" ;
		}
	}
} // namespace CarrierUtils

} // namespace Mplane



// Make carrier printable
inline std::ostream& operator << (std::ostream& os, const Mplane::ICarrier& carrier)
{
	carrier.showCarrier(os) ;
	return os;
}



#endif /* CARRIERUTILS_H_ */
