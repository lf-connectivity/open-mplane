#ifndef _hardware_MDIO_H_
#define _hardware_MDIO_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mdio.h
 * \brief     A file to define the interface to the Management Data Input/Output (MDIO)
 *
 *
 * \details   A file to define the interface to the Management Data Input/Output (MDIO)
 *
 */

#include "GlobalTypeDefs.h"
#include "Loggable.h"

#include "IGpioKernel.h"
#include "IMdio.h"
#include "Device.h"

namespace Mplane
{

class Mdio : public virtual IMdio, public Device, public Loggable
{
public:

    friend class MdioTestCases;

    /*!
     * \brief Mdio Constructor
     *
     * \param the device Index for this driver device
     */
    explicit Mdio( int deviceIndex );

    /*!
     *
     * \brief Mdio Destructor
     */
	virtual ~Mdio();

    /*!
     * \brief Method used to initialise the device.
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    ReturnType::State initialise( void );

    /*!
     * \brief Method used to initialise the device.
     *
     * \return RT_OK if successful, RT_other otherwise
     */
    ReturnType::State doInit( void );

	virtual void show( void );

protected:
	static const UINT16 PHY_LED_REGISTER    = 0x0016;   //!> This magic number has been inherited from the original (legacy) ETNA RRH
	static const UINT16 LED_BEHAVIOUR       = 0x45BF;   //!> This magic number has been inherited from the original (legacy) ETNA RRH

	static const UINT16 ECB_BOARD_ID        = 0x09;     //!> ECB board ID value
	static const UINT16 ECB_RB_BOARD_ID     = 0x0C;     //!> ECB RB board ID value

	static const ULONG  RGMIIO_FER_ADDR     = 0x0B00;   //!> This is the RG MIIO Function Enable Register in the PPC. Its full address is 0xFE60 0B00
	                                                    //   See PPC405EX/EXr Embedded Processor user manual. Revision 1.25 - June 20, 2012. Page 680.

    static const UINT32 MDIO_EN_MASK       = 0x03;      //!> Bits 12 and 13 contain the MDIO
    static const UINT32 MDIO_EN_SHIFT      = 18;        //!> Shift value of 18 to access bits 13 and 12.
    static const UINT32 MDIO_EMAC_DISABLE  = 0x00;      //!> 0 0 - Disabled
    static const UINT32 MDIO_EMAC_1_EN     = 0x01;      //!> 0 1 - EMAC1
    static const UINT32 MDIO_EMAC_0_EN     = 0x02;      //!> 1 0 - EMAC0
    static const UINT32 MDIO_EMAC_0_RES    = 0x03;      //!> 1 1 - reserved.

    /**
     * Kernel interface singleton
     */
    std::shared_ptr<IGpioKernel> device ;

};

}  // end of namespace AxeAxis

#endif /* _hardware_MDIO_H_ */
