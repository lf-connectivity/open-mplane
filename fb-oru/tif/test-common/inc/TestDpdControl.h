/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestDpdControl.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTDPDCONTROL_H_
#define TESTDPDCONTROL_H_


#include <IDpdControl.h>

namespace Mplane {

class TestDpdControl : public virtual IDpdControl
{
public:
	TestDpdControl() {}
	virtual ~TestDpdControl() {}

    // IDpdControl interface

    /**
     * This method will reset the DPD on the specified channel to
     * unity gain
     * \param tx - tx path [0..MAX-1] to be reset
     * \return true if all ok; false on failure
     */
    virtual bool resetDpd(unsigned tx) override {return true;}

    /**
     * This method will enable adaption of the DPD on the specified
     * channel
     * \param tx - tx path to enable
     * \param timeoutMs - timeout time in millisecs
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx, unsigned timeoutMs) override {return true;}
    virtual bool startDpd(unsigned tx) override {return true;}

    /**
     * This method will stop the DPD on the specified channel
     * \param tx - tx path [0..MAX-1] to be restarted
     * \return true if all ok; false on failure
     */
    virtual bool stopDpd(unsigned tx) override {return true;}

    /**
     * This method will send the latest PAPR target to the DPD for this tx path
     * \param tx - tx path [0..MAX-1] to be restarted
     * \return true if all ok; false on failure
     */
    virtual bool setPapr(unsigned tx, const Power& papr) {return true;}

    virtual bool setSRxAtten(unsigned tx, const Power& papr) {return true;}

} ;


}

#endif /* TESTDPDCONTROL_H_ */
