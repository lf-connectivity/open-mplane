#ifndef _VHI_IBNC_H_
#define _VHI_IBNC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBnc.h
 * \brief     A file to define generic interface to an IBnc (Bnc routing on the 10MHz Reference) Module
 *
 *
 * \details   A file to define generic interface to an IBnc (Bnc routing on the 10MHz Reference) Module
 *
 */

// Includes go here, before the namespace
#include "GlobalTypeDefs.h"
#include "II2c.h"
#include "IDevice.h"
#include <vector>
#include <stdexcept>
#include <memory>

namespace Mplane
{

/*! \brief  Generic IBnc interface
 *
 *  A virtual interface base class defining an interface to a IBnc bus.
 *  The interface contains configuration and control aspects.
 */
class IBnc : public virtual IDevice
{
public:

    /*! \brief BNC Configuration enable enumeration - Enable or Disable
     *
     */
    typedef enum
    {
        configEnable  = 0,
        configDisable = 1,
        configUnset
    } bncConfigEnable_T;

    /*! \brief BNC 1 Configuration enumeration - Output or Input
     *
     */
    typedef enum
    {
        fpgaRef1ToBnc1Output = 0,
        bnc1InputToFpgaRef1  = 1,
        bnc1Unset
    } bnc1Config_T;

    /*! \brief BNC 2 Configuration enumeration - FPGA or BNC3
     *
     */
    typedef enum
    {
        fpgaRef2ToBnc2Output   = 0,
        bnc3InputToBnc2Output  = 1,
        bnc2Unset
    } bnc2Config_T;

    /*! \brief BNC 3 Configuration enumeration - Output or Input
     *
     */
    typedef enum
    {
        fpgaRef3ToBnc3Output = 0,
        bnc3InputToFpgaRef3  = 1,
        bnc3Unset
    } bnc3Config_T;

    /*! \brief BNC 4 Configuration enumeration - FPGA or BNC5
     *
     */
    typedef enum
    {
        fpgaRef4ToBnc4Output   = 0,
        bnc5InputToBnc4Output  = 1,
        bnc4Unset
    } bnc4Config_T;

    /*! \brief BNC 5 Configuration enumeration - Output or Input
     *
     */
    typedef enum
    {
        fpgaRef5ToBnc5Output = 0,
        bnc5InputToFpgaRef5  = 1,
        bnc5Unset
    } bnc5Config_T;

    /*! \brief Sync In/Out Configuration enumeration - Enable or Disable
     *
     */
    typedef enum
    {
        syncConfigEnable    = 0,
        syncConfigDisable   = 1
    } syncConfig_T;

    /*! \brief Destructor
     *
     */
    virtual ~IBnc() { };

    /*! \brief Pure virtual method to get the BNC configuration enable/disable state
     *
     * An enumerated type stating if the BNC configuration is set to enable or disable.
     *
     * \return BNC configuration enable or disable
     */
    virtual bncConfigEnable_T getBncConfigEnable() = 0;

    /*! \brief Pure virtual method to set the BNC configuration enable/disable state
     *
     * An enumerated type setting the BNC configuration is set to enable or disable.
     *
     * \param BNC enable/disable configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual ReturnType::State setBncConfigEnable( bncConfigEnable_T bncConfigEnable) = 0;

    /*! \brief Pure virtual method to get the BNC 1 configuration state
     *
     * An enumerated type stating if the BNC configuration
     *
     * \return Current BNC 1 configuration
     */
    virtual bnc1Config_T getBnc1Config() = 0;

    /*! \brief Pure virtual method to set the BNC 1 configuration
     *
     * An enumerated type setting the BNC 1
     *
     * \param BNC 1 configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual  ReturnType::State setBnc1Config( bnc1Config_T bnc1Config ) = 0;

    /*! \brief Pure virtual method to get the BNC 2 configuration state
     *
     * An enumerated type stating if the BNC configuration
     *
     * \return Current BNC 2 configuration
     */
    virtual bnc2Config_T getBnc2Config() = 0;

    /*! \brief Pure virtual method to set the BNC 2 configuration
     *
     * An enumerated type setting the BNC 2
     *
     * \param BNC 2 configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual  ReturnType::State setBnc2Config( bnc2Config_T bnc2Config ) = 0;

    /*! \brief Pure virtual method to get the BNC 3 configuration state
     *
     * An enumerated type stating if the BNC configuration
     *
     * \return Current BNC 3 configuration
     */
    virtual bnc3Config_T getBnc3Config() = 0;

    /*! \brief Pure virtual method to set the BNC 3 configuration
     *
     * An enumerated type setting the BNC 3
     *
     * \param BNC 3 configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual  ReturnType::State setBnc3Config( bnc3Config_T bnc3Config ) = 0;

    /*! \brief Pure virtual method to get the BNC 4 configuration state
     *
     * An enumerated type stating if the BNC configuration
     *
     * \return Current BNC 4 configuration
     */
    virtual bnc4Config_T getBnc4Config() = 0;

    /*! \brief Pure virtual method to set the BNC 4 configuration
     *
     * An enumerated type setting the BNC 4
     *
     * \param BNC 4 configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual  ReturnType::State setBnc4Config( bnc4Config_T bnc4Config ) = 0;

    /*! \brief Pure virtual method to get the BNC 5 configuration state
     *
     * An enumerated type stating if the BNC configuration
     *
     * \return Current BNC 5 configuration
     */
    virtual bnc5Config_T getBnc5Config() = 0;

    /*! \brief Pure virtual method to set the BNC 5 configuration
     *
     * An enumerated type setting the BNC 5
     *
     * \param BNC 5 configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual  ReturnType::State setBnc5Config( bnc5Config_T bnc5Config ) = 0;

    /*! \brief Virtual method to get the sync out configuration state
     *
     * An enumerated type stating the sync out configuration
     *
     * \return Current sync out configuration
     */
    virtual syncConfig_T getSyncOutConfig() = 0;

    /*! \brief Virtual method to set the sync out configuration
     *
     * An enumerated type setting the sync out configuration
     *
     * \param sync out configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual  ReturnType::State setSyncOutConfig( syncConfig_T syncOutConfig ) = 0;

    /*! \brief Virtual method to get the sync in configuration state
     *
     * An enumerated type stating the sync in configuration
     *
     * \return Current sync in configuration
     */
    virtual syncConfig_T getSyncInConfig() = 0;

    /*! \brief Virtual method to set the sync in configuration
     *
     * An enumerated type setting the sync in configuration
     *
     * \param sync in configuration to set
     *
     * \return Return state of the set command if successful or not
     */
    virtual  ReturnType::State setSyncInConfig( syncConfig_T syncInConfig ) = 0;

    /**
     * \brief   Get an instance of the Reference interface
     * \return  return a reference to the interface
     */
    static std::shared_ptr<IBnc> getInterface( int deviceIndex );

protected:
    IBnc() {};
};

} /* namespace Mplane */

#endif /* _VHI_IBNC_H_ */
