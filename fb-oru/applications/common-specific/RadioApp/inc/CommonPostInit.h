/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonPostInit.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef COMMONPOSTINIT_H_
#define COMMONPOSTINIT_H_

#include <memory>
#include "IRadio.h"

namespace Mplane {

class Ati ;

/**
 * The CommonPostInit class provides a common implementation of the IRadioPostInit
 * pure virtual base class.
 */
class CommonPostInit : public IRadioPostInit {
public:
	CommonPostInit() ;
	virtual ~CommonPostInit() ;

    /**
     * This method will be called by the IRadio once the initialisation has successfully completed. NOTE: The
     * method is NOT called if initialisation fails.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State operator()() override ;

    /**
	 * Singleton for this class
	 */
	static std::shared_ptr<CommonPostInit> getInterface() ;

private:
    /**
     * Test Interface
     */
    std::shared_ptr< Ati >	mAti ;
} ;

}

#endif /* COMMONPOSTINIT_H_ */
