/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRadioState.h
 * \brief     Interface for Radio State
 *
 *
 * \details   Defines the expected interface for the radio state
 *
 */


#ifndef IRADIO_STATE_H_
#define IRADIO_STATE_H_

#include <memory>
#include <vector>

namespace Mplane
{

/*! @brief Radio State
 *
 * The purpose of the IRadioState class is to provide a generic
 * interface to the power control loop in the application.
 *
 * The Radio States implements the singleton pattern so that only one radio state
 * can exist with the system.
 *
 * An implementation of the IRadioState needs to provide the getState() method so that the subject can get the current PCL state
 * and it also needs to call Subject notify() method on state changes.
 *
 */
class IRadioState
{
public:
	virtual ~IRadioState() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the RadioState within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IRadioState> getInstance( void );

	/**
	 * IRadioState states
	 */
	typedef enum RadioStatesType
	{
		RADIO_STATE_INITIAL,
		RADIO_STATE_NORMAL,
		RADIO_STATE_NORMAL_STANDBY,
		RADIO_STATE_NORMAL_SW_DOWNLOAD,
		RADIO_STATE_FAILED_CPRI_LINK_FAIL,
		RADIO_STATE_DEGRADED,
		RADIO_STATE_FAILED
	} RadioStatesType_T;

    /* Assign strings to the RadioStatesType ENUM above. Ensure that the
     * ordering is the same */

	const char* mStateNames[7] = { "INITIAL", "NORMAL",	"STANDBY", "SW DOWNLOAD", "CPRI LINK FAILURE", "DEGRADED", "FAILED" };

     /**
      * Returns the current Radio state
      * @return Radio state
      */
     virtual RadioStatesType getState() const =0 ;

     /**
      * This method is to show the Radio State status.
      */
     virtual void showRadioState() = 0;

} ;

}

#endif /* IRADIO_STATE_H_ */
