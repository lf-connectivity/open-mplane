#ifndef _VRH_IIDEEPROM_H_
#define _VRH_IIDEEPROM_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IIdEeprom.h
 * \brief     A file to define generic interface to an ID EEPROM
 *
 *
 * \details   A file to define generic interface to an ID EEPROM
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include <memory>
#include <vector>
#include <stdexcept>

namespace Mplane
{

/*! \brief  Generic ID EEPROM interface
 *
 *  A virtual interface base class defining an interface to ID EEPROM.
 *  The interface contains configuration and control aspects.
 */
class IIdEeprom
{
public:

    /*! \brief Constructor
     *
     */
    IIdEeprom() { };

    /*! \brief  Read the ID EEPROM. This will lock the bus and perform the read
     *
     *  Do the read from the chip.
     *
     *  \param byteAddress is the start address.
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State readAtomic( UINT32 byteAddress, UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) = 0;

    /*! \brief  Write to the ID EEPROM. This will lock the bus and perform the write
     *
     *  Do the write to the chip.
     *
     *  \param byteAddress is the start address.
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State writeAtomic(UINT32 byteAddress, UINT16 dataLen, UINT8* dataPtr) = 0;

    /*! \brief  Read the ID EEPROM. This does not lock the bus
     *
     *  Do the read from the chip.
     *
     *  \param numberOfBytesToRead  The number of bytes that we wish to read
     *  \param bufferPtrToWriteTo   The buffer that we wish the data to be written to
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State read( UINT8  numberOfBytesToRead,
                                    UINT8* bufferPtrToWriteTo ) = 0;

    /*! \brief  Write to the ID EEPROM. This does not lock the bus
     *
     *  Do the write to the chip.
     *
     *  \param byteAddress is the start address.
     *  \param dataLen is the number of words to write.
     *  \param dataPtr is the buffer containing the data to write.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State write(UINT32 byteAddress, UINT16 dataLen, UINT8* dataPtr) = 0;

    /*! \brief  Load the ID EEPROM contents
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State load() = 0;

    /*! \brief  Check whether ID EEPROM data is read and parsed
     *
     *  \return true/false
     */
    virtual bool isLoaded(void) = 0;

    /*! \brief Destructor
     *
     */
    virtual ~IIdEeprom() { };


};

} /* namespace Mplane */

#endif /* _VRH_IIDEEPROM_H_ */
