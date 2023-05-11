#ifndef _COMMONALDPORT_H_
#define _COMMONALDPORT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonAldPort.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IAldPort.h"
#include "CommonPort.h"

namespace Mplane
{

class CommonAldPort:  public virtual IAldPort, public CommonPort
{
public:

	CommonAldPort( int index, char const* name, std::shared_ptr<Hdlc> hdlc);

    virtual ~CommonAldPort();

    /**
     * This method returns the HDLC interface to communicate to the devices on ALD port
     *
     * @return Pointer to Hdlc class
     */
    virtual std::shared_ptr<Hdlc> getHdlc() ;

    /**
     * This method indicates whether DC power can be turned ON/OFF on this port
     *
     * @return bool
     */
    virtual bool isDCPowerControlSupported(void) override;

    /**
     * This method provides the DC power supply status
     *
     * @return DC power status
     */
    virtual bool isDCPowerOn(void) override;

    /**
     * This method is to turn ON/OFF
     *
     * @return None
     */
    virtual void setDCPower(bool) override;

    /**
     * This method indicates whether overcontrol detection is supported on this port
     *
     * @return bool
     */
    virtual bool isOvercurrentDetectionSupported(void) override;

    /**
     * This method registers callbacks for overcurrent notifications
     *
     * @return bool
     */
    virtual void registerOvercurrentCb(OverCurrentFuncCb cb) override;

protected:

    bool mDcPowerStatus;
    std::vector<OverCurrentFuncCb> mOverCurrentCb;

private:

    std::shared_ptr<Hdlc> mHdlc;    //!> Pointer to HDLC object to communicate on the port
};


}




#endif /* _COMMONALDPORT_H_ */
