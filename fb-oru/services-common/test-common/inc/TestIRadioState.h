/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestRadioState.h
 * \brief     Interface for Radio State
 *
 *
 * \details   Defines the expected interface for the radio state
 *
 */


#ifndef TEST_RADIO_STATE_H_
#define TEST_RADIO_STATE_H_

#include <memory>

#include "IRadioState.h"

namespace Mplane
{

class TestRadioState : public IRadioState
{
public:
	virtual ~TestRadioState() {}

    /*! @brief  Get the singleton instance
     *
     *  Method used to obtain a reference to the single instance of the PCL within the system.
     *
     *  @return the singleton instance
     */
    static std::shared_ptr<IRadioState> getInstance( void );

     /**
      * Returns the current Radio state
      * @return Radio state
      */
     virtual RadioStatesType getState() const ;

     /**
      * This method is to show the Radio State status.
      */
     virtual void showRadioState() ;

protected:
     IRadioState::RadioStatesType mRadioState;

} ;

}

#endif /* TEST_RADIO_STATE_H_ */
