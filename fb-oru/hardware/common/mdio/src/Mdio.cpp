/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mdio.cpp
 * \brief     Define the Management Data Input/Output (Mdio) interface class
 *
 *
 * \details   Define the Management Data Input/Output (Mdio) interface class
 *
 */

#include <netinet/in.h>
#include <linux/sockios.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>

#include <memory>

#include "GlobalTypeDefs.h"
#include "IRadioInfo.h"
#include "Mdio.h"

using namespace Mplane;

Mplane::Mdio::Mdio( int deviceIndex ) :
	Device( Device::MDIO, deviceIndex, "Front Panel Ethernet" ),
	Loggable("Mdio","DV"),
	device( IGpioKernel::getInstance() )
{
}

Mplane::Mdio::~Mdio()
{
}

ReturnType::State Mplane::Mdio::initialise( void )
{
    ReturnType::State   returnState;
    struct ifreq        socketsInterface;

    eventInfo("--- Mdio initialise ---");

    /*
     * Device initialisation from startup.
     */

    // Create an instance of the radio Info so we can extract the board ID.
    std::shared_ptr<IRadioInfo> radioInfo = IRadioInfoFactory::create();

    UINT16 *dataPtr = (UINT16 *) &socketsInterface.ifr_ifru;

    memset(&socketsInterface, 0, sizeof (socketsInterface) );

    strcpy(socketsInterface.ifr_ifrn.ifrn_name, "eth_cdi"); // eth_cdi - Ethernet Control and Debug Interface.

    /* Open a control socket. */
    UINT16 controlSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (controlSocket < 0)
    {
        throw std::runtime_error("Mdio::Initialise - failed to open socket") ;
    }
    else
    {
        returnState = ReturnType::RT_OK;
    }

    // Note that dataPtr points to the address of socketsInterface.ifr_ifru
    // This is inherited code and it is not clear why it was done this way!
    dataPtr[1] = PHY_LED_REGISTER; // reg_num
    dataPtr[2] = LED_BEHAVIOUR;    // val_in - Note concept of direction is reversed in linux device driver

    UINT16 ioControl = ioctl(controlSocket, SIOCSMIIREG, &socketsInterface);

    if (ioControl < 0)
    {
        throw std::runtime_error("Mdio::Initialise - failed to write to Ethernet PHY MDIO");
    }

    return returnState;
}

ReturnType::State Mplane::Mdio::doInit(void)
{
    eventInfo("--- Mdio doInit ---");

    return initialise();
}

void Mplane::Mdio::show()
{
    eventInfo("Mdio: ");
}
