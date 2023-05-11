#ifndef _VRH_IFIBRE_H_
#define _VRH_IFIBRE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFibre.h
 * \brief     Pure virtual interface that defines methods to a Fibre interface
 *
 *
 * \details   Pure virtual interface that defines methods to a Fibre interface
 *
 */

#include <memory>
#include "GlobalTypeDefs.h"

namespace Mplane
{

/*! \brief Provides a standard interface to the Fibre links.
 *
 * The IFibre interface is provided to allow for the creation of
 * a singleton class that will provide the entry point to the fibre control
 * process. The following example shows how the interface is used.
 *
 * \code
 *
 * {
 *     std::shared_ptr<IFibre> fibre = IFibre::getInterface();
 *
 *     fibre->intialise();
 * }
 * \endcode
 *
 */
class IFibre
{
public:

    /*! \brief  Fibre type identities
     *
     * Identities for each Fibre interface type.
     *
     */
    typedef enum FibreType
    {
        FibreTypeCpri = 1,
		FibreTypeObsai = 2,
		FibreTypeOran = 3,

    } FibreType_t;

    /*! \brief  Get the singleton instance
     *
     * Method defines a static method used to get the single instance of
     * the generic fibre interface.
     *
     * \note Since this is a static method, it cannot be pure virtual and as such
     * it must have an implementation in the corresponding hardware-specific library.
     *
     * \return reference to the single instance of IFibre interface
     */
    static std::shared_ptr<IFibre> getInterface();

    /*! \brief  The initialise method
     *
     * Method called during system startup, post FPGA image load, to fully
     * initialise the Fibre interface(s).
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise(void) = 0;

    /*! \brief  Get the fibre type for this implementation
     *
     *  Method returns the fibre type as an enumerated value of type FibreType_t.
     *  The implementation (returned value) will be application specific.
     *
     *  \return a type defined enumerator for the fibre type
     */
    virtual FibreType_t getFibreType() const = 0;

    /*! \brief  Get the fibre clock sync source for this implementation
     *
     *  Method returns the current clock sync source.
     *  The implementation (returned value) will be application specific.
     *
     *  \return the current clock sync source, zero-based integer
     */
    virtual int getFibreClockSyncSource() = 0;

    /*! \brief  Get the number of fibre ports supported by the hardware
     *
     * Method used to return the number of fibre ports supported by the hardware.
     *
     * \return the number of fibre ports supported by the hardware.
     */
    virtual UINT32 getNumPorts() const = 0;

    /*! \brief  Get the fibre type string
     *
     *  \return the type as a string
     */
    virtual const char* fibreTypeString() const = 0;

    /**
     * Protected destructor prevent object deletion.
     */
    virtual ~IFibre() { };


protected:

};


} /* namespace Mplane */

#endif /* _VRH_IFIBRE_H_ */
