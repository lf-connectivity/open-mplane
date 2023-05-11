#ifndef _TESTFTUUUT_H_
#define _TestFTUUUT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestArtUut.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IArtUut.h"
#include "Observer.hpp"
#include "ICpriPortHandler.h"

namespace Mplane
{

class TestArtUut: public IArtUut, public ISetArtUutAddr, public Observer<ICpriPortHandler>
{
public:
    TestArtUut();

    /**
     * Method returns true if the unit under test is successfully connected
     * to the factory test unit
     * @return true if connceted
     */
    virtual bool isConnected();
    /**
     * If the unit under test is connected through an IP protocol over Ethernet, through either
     * CPRI or direct 10/100/1G connection the FTU will determine its allocated IP address.
     *
     * if not connected an empty ip address 0.0.0.0 is returned.
     *
     * @return string representing the unit under tests allocated IP address, eg 192.168.1.0
     */
    virtual std::string getIpAddress();

    /**
     * Method used to return the negotiated CPRI line rate for the master connection.
     *
     * @return string representing the CPRI line rate.
     */
    virtual std::string getCpriLineRate();

    /*!
     * Method used to set the CPRI line rate to a specific value. This will cause the
     * CPRI link to re-negotiate the link.
     *
     * For the ART implementation of this interface, the new rate will be set but it
     * is assumed that exiting IP over CPRI will remain active and that no new DHCP request
     * will be made. So the change in state be ignored by the UUT connection monitor and the
     * UUT IP address will be retained.
     *
     * @return true if correctly set otherwise false.
     */
    virtual bool setCpriLineRate(int lineRate );


    /**
     * This method is used to issue a L1 reset request on the CPRI slave port.
     */
    virtual void cpriL1Reset();


    ~TestArtUut();

    /**
     * Implement the update method that will be called as part of the ICproPortHandler
     * observer pattern. This callback method will be called in the context of the FibreServices thread
     * when there is a change in the CPRI state.
     *
     * @param subject
     */
    virtual void update(ICpriPortHandler& subject);

    /**
     * Used by the observer/Subject pattern to name objects that observe subjects.
     * @return
     */
    virtual const char* name() const;

    /**
     * Method used by helper Mplane::FtuGetIPAddr thread  to set the reported unit under test
     * IP address. If no valid address is received it will be set to 255.255.255.255 to indicate
     * no address found. This will be reset to 0.0.0.0 when
     * @param ipAddr
     */
    virtual void setIPAddress( std::string ipAddr );

};

}

#endif /* _FTUUUT_H_ */
