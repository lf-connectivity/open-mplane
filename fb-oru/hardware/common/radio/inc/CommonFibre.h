#ifndef _hardware_COMMONFIBRE_H_
#define _hardware_COMMONFIBRE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonFibre.h
 * \brief     A file to define the Fibre control that is common to a radio.
 *
 *
 * \details   A file to define the Fibre control that is common to a radio.
 *
 */

// Includes go here, before the namespace
#include "Loggable.h"
#include "CommonCpri.h"
#include "IFibre.h"

namespace Mplane
{

// forward class definitions go here
class ICpri;


/*! \brief  The Common Fibre Interface class
 *
 * This class provides a common implementation of the IFibre interface.
 * It extends the hardware interface IFibre to allow for any common radio-specific
 * processing to be added.
 *
 * This common class collects together the various interfaces used to initialise a CPRI Fibre interface.
 * This class can and should be extended and modified for application specific fibres.
 *
 * It must be implemented as a singleton pattern such that only one IFibre can exist.
 *
 * The singleton class should be instantiated/retrieved by calling the
 * IFibre::getInterface() method. Since static methods cannot be virtual or extended
 * in a sub-class, it is implemented in this class's .cpp file.
 */
class CommonFibre: public IFibre, public Loggable
{
    friend class CommonFibreTestCase;

    /**
     * This class should be instantiated by calling IFibre::getInterface(). See
     * IFibre in the VRH repository for further details.\n
     * IFibre is declared as a friend of this class so that it can instantiate the otherwise protected
     * constructor.
     */
    friend class IFibre;

public:

    /**
     * Singleton
     */
    static std::shared_ptr<IFibre> getInterface() ;

    // public constants

    virtual ~CommonFibre() { }

    /*! @brief  The show function required by Loggable
     */
    virtual void show();

    /*! \brief  The initialise method required by IFibre
     *
     * Method called during system startup, post FPGA image load, to fully
     * initialise the Fibre interface(s).
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State initialise(void);

    /*! \brief  Returns the fibre type for this implementation, required by IFibre
     *
     *  Method returns the fibre type as an enumerated value of type FibreType_t.
     *  The implementation (returned value) will be application specific.
     *
     *  \return a type defined enumerator for the fibre type
     */
    virtual IFibre::FibreType_t getFibreType() const;

    /*! \brief  Get the fibre clock sync source for this implementation
     *
     *  Method returns the current clock sync source.
     *  The implementation (returned value) will be application specific.
     *
     *  \return the current clock sync source, zero-based integer
     */
    virtual int getFibreClockSyncSource();

    /*! \brief  Get the number of fibre ports supported by the hardware, required by IFibre
     *
     * Method used to return the number of fibre ports supported by the hardware.
     *
     * \return the number of fibre ports supported by the hardware.
     */
    virtual UINT32 getNumPorts() const;

    /*! \brief  Returns the fibre type string, required by IFibre
     *
     *  \return the type as a string
     */
    virtual const char* fibreTypeString() const;

    /*! \brief  Get the CPRI access implementation
     *
     *  Method returns the common CPRI access implementation.
     *
     *  \return The CPRI access pointer
     */
    virtual CommonCpriPtr getCpri() const;


protected:

    /*! \brief  Default constructor
     *
     * Construct a base common fibre interface class, that supports a common fibre implementation.
     *
     * A protected constructor is provided for the singleton pattern
     * to return just a single instance of the IFibreControl interface.
     */
    CommonFibre();


private:

    ReturnType::State mInitialised;

    /**
     * Uses the CommonCpri for CPRI access
     */
    CommonCpriPtr mCpri;

};  // end of class CommonFibre

} /* namespace Mplane */

#endif /* _hardware_COMMONFIBRE_H_ */
