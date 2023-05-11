/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LedSX1509b.cpp
 * \brief     Implementation of methods defined in the LedSX1509b class
 *
 *
 * \details   Implementation of methods defined in the LedSX1509b class
 *
 */

#include <string.h>
#include "ILed.h"
#include "II2c.h"
#include "LedSX1509b.h"
#include "GlobalTypeDefs.h"

using namespace Mplane;

// Note this device only support 7 bit addressing
Mplane::LedSX1509b::LedSX1509b(std::shared_ptr<II2c> theI2c, UINT8 i2cAddress): Loggable("LedSX1509b","DV"), mI2c( theI2c )
{
    mI2cData.i2cAddrMode = sevenBitAddrMode;
    mI2cDeviceAddress    = i2cAddress;

    mRegDataA = 0x00; // Initialise the local member mRegDataA
    mRegDataB = 0x00; // Initialise the local member mRegDataB
}

Mplane::LedSX1509b::~LedSX1509b()
{
}

ReturnType::State Mplane::LedSX1509b::initialise(void)
{
    /*
     * This assumes that the I2C has already been initialised.
     */
    ReturnType::State returnState = ReturnType::RT_OK;

    eventInfo("--- LedSX1509b Initialisation ---");

    show();

    UINT8 clkRegData[]      = { mI2cDeviceAddress, regAddrClock, regValueClockOscSrcInternal }; // Set the clock register
    UINT8 miscRegData[]     = { mI2cDeviceAddress, regAddrMisc, ( regValueMiscLedDriverALog |
                                                                  regValueMiscLedDriverBLog |
                                                                  regValueMiscClkX ) };         // Set up the misc register
    mRegDataA = 0x00;
    mRegDataB = 0x00;

    UINT8 dataRegDataA[]    = { mI2cDeviceAddress, regAddrDataA, mRegDataA };                   // Set all LEDs off on Data A
    UINT8 dataRegDataB[]    = { mI2cDeviceAddress, regAddrDataB, mRegDataB };                   // Set all LEDs off on Data B

    //                        { TOn,  IOn,  Off,  TRise, TFall, TOn,  IOn,  Off,  TRise, TFall }
    UINT8 nonFadeLedData[]  = { 0x00, 0x00, 0x00,               0x00, 0x00, 0x00               };
    UINT8 fadeLedData[]     = { 0x00, 0x00, 0x00, 0x00,  0x00,  0x00, 0x00, 0x00, 0x00,  0x00  };

    UINT8 dataEnableDataA[] = { mI2cDeviceAddress, regAddrLEDDriverEnableA, 0xff };             // Enable all outputs on Data A
    UINT8 dataEnableDataB[] = { mI2cDeviceAddress, regAddrLEDDriverEnableB, 0xff };             // Enable all outputs on Data B

    UINT8 dataDirDataA[]    = { mI2cDeviceAddress, regAddrDirA, 0x00 };                         // All outputs on Data A
    UINT8 dataDirDataB[]    = { mI2cDeviceAddress, regAddrDirB, 0x00 };                         // All outputs on Data B

    // Write the data out to the I2C device.
    write((UINT8*)&clkRegData,         sizeof(clkRegData));
    write((UINT8*)&miscRegData,        sizeof(miscRegData));
    write((UINT8*)&dataRegDataA,       sizeof(dataRegDataA));
    write((UINT8*)&dataRegDataB,       sizeof(dataRegDataB));

    // Write the rest of the LED data
    UINT8 data[12];
    UINT8 dataLength;

    data[0] = mI2cDeviceAddress; // Fill out device address that we are writing to

    for( UINT8 ledNumber = led1T; ledNumber <= led4B; ledNumber ++ )
    {
        data[1] = redLedTOnRegs[ledNumber]; // Fill out which TOn register we will write to... and its green neighbour!

        if( (led2T == ledNumber) || (led2B == ledNumber) || (led4T == ledNumber) || (led4B == ledNumber) )
        {
            memcpy( &data[2], &fadeLedData, sizeof(fadeLedData) );

            dataLength = sizeof(fadeLedData) + 2;
        }
        else
        {
            memcpy( &data[2], &nonFadeLedData, sizeof(nonFadeLedData) );

            dataLength = sizeof(nonFadeLedData) + 2;

        }

        write((UINT8*)&data,  dataLength);
    }

    write((UINT8*)&dataEnableDataA,     sizeof(dataEnableDataA));
    write((UINT8*)&dataEnableDataB,     sizeof(dataEnableDataB));
    write((UINT8*)&dataDirDataA,        sizeof(dataDirDataA));
    write((UINT8*)&dataDirDataB,        sizeof(dataDirDataB));

    return returnState;
}

ReturnType::State Mplane::LedSX1509b::setLed(UINT8 ledNumber,
                                              UINT8 ledColour,
                                              UINT8 ledState,
                                              UINT8 ledRate)
{
#ifdef OFF_TARGET
    logDebugNormal("%s - ", __func__);
#endif

    ReturnType::State returnState;

    if( (NUM_LEDS > ledNumber) && (0xff >= ledRate ) )
    {
        // The breathing effect is only available on certain LED's
        if( (led1T == ledNumber) || (led1B == ledNumber) || (led3T == ledNumber) || (led3B == ledNumber) )
        {
            if( ILed::LED_BREATH == ledState )
            {
                ledState = ILed::LED_FLASH;
            }
        }

        // Set default data
        UINT8 IOn     = 0xff;
        UINT8 TOn     = ledRate;
        UINT8 IOff    = 0x00;
        UINT8 TOff    = ledRate;
        UINT8 TRise   = 0x00;
        UINT8 TFall   = 0x00;

        // Depending on the ledState set the parameters as required
        switch(ledState)
        {
        case ILed::LED_OFF:
            IOn = 0x00;
            break;
        case ILed::LED_ON:
            TOn = 0x00;
            break;
        case ILed::LED_FLASH:
            // TOn and TOff are set as part of the default data above
            break;
        case ILed::LED_BREATH:
            IOn     = 0xf0;
            IOff    = 0x04;
            TRise   = (ledRate / 1.5);
            TFall   = (ledRate / 1.5);
            break;
        }

        // Initialise the Red and Green parameters
        UINT8 redIOn     = IOn;
        UINT8 redTOn     = TOn;
        UINT8 redIOff    = IOff;
        UINT8 redTOff    = TOff;
        UINT8 redTRise   = TRise;
        UINT8 redTFall   = TFall;
        UINT8 greenIOn   = IOn;
        UINT8 greenTOn   = TOn;
        UINT8 greenIOff  = IOff;
        UINT8 greenTOff  = TOff;
        UINT8 greenTRise = TRise;
        UINT8 greenTFall = TFall;

        // The default is orange/amber. If this is not the required colour, then turn off the other LED
        if( ILed::LED_RED == ledColour )
        {
            greenIOn  = 0x00;
            greenIOff = 0x00;
        }
        else if ( ILed::LED_GREEN == ledColour )
        {
            redIOn  = 0x00;
            redIOff = 0x00;
        }

        UINT8 data[12]; // Holder for the entire data packet.
        UINT8 dataLength;

        data[0] = mI2cDeviceAddress;        // Fill out device address that we are writing to
        data[1] = redLedTOnRegs[ledNumber]; // Fill out which TOn register we will write to... and its green neighbour!

        // If we are dealing with led 2 or 4 then we need to set all the data including the fade data
        if( (led2T == ledNumber) || (led2B == ledNumber) || (led4T == ledNumber) || (led4B == ledNumber) )
        {
            // Load the fade data ready to be copied in to the main data holder
            UINT8 fadeLedData[] = { (UINT8)  (redTOn & regMaskTOn),
                                    (UINT8)   redIOn,
                                    (UINT8)(((redTOff << regMaskShiftOffTOff ) & regMaskOffTOff) | (UINT8)( redIOff & regMaskOffIOff)),
                                    (UINT8)  (redTRise & regMaskTRise),
                                    (UINT8)  (redTFall & regMaskTFall),
                                    (UINT8)  (greenTOn & regMaskTOn),
                                    (UINT8)   greenIOn,
                                    (UINT8)(((greenTOff << regMaskShiftOffTOff ) & regMaskOffTOff) | (UINT8)( greenIOff & regMaskOffIOff)),
                                    (UINT8)  (greenTRise & regMaskTRise),
                                    (UINT8)  (greenTFall & regMaskTFall) };

            memcpy( &data[2], &fadeLedData, sizeof(fadeLedData) );

            dataLength = sizeof(fadeLedData) + 2;
        }
        else
        {
            // Load the non fade data ready to be copied in to the main data holder
            UINT8 nonFadeLedData[] = { (UINT8)  (redTOn & regMaskTOn),
                                       (UINT8)   redIOn,
                                       (UINT8)(((redTOff << regMaskShiftOffTOff ) & regMaskOffTOff) | (UINT8)( redIOff & regMaskOffIOff)),
                                       (UINT8)  (greenTOn & regMaskTOn),
                                       (UINT8)   greenIOn,
                                       (UINT8)(((greenTOff << regMaskShiftOffTOff ) & regMaskOffTOff) | (UINT8)( greenIOff & regMaskOffIOff)) };

            memcpy( &data[2], &nonFadeLedData, sizeof(nonFadeLedData) );

            dataLength = sizeof(nonFadeLedData) + 2;
        }

        // Now write the data
        write((UINT8*)&data, dataLength);

        returnState = ReturnType::RT_OK;
    }
    else
    {
        returnState = ReturnType::RT_OUT_OF_RANGE;

        eventInfo("%s - value out of range ! ledNumber = %d ledRate = %d", __func__, ledNumber, ledRate);
    }

    return returnState;
}

ReturnType::State Mplane::LedSX1509b::write(UINT8* data, UINT16 dataLen)
{
    return mI2c->write(dataLen, data);
}

void Mplane::LedSX1509b::show()
{
    eventInfo("LED SX1509B");

    eventInfo("I2C Device Address = 0x%04x", (mI2cDeviceAddress >> 1)); // Device address shift by 1 to offset WR LSB
}
