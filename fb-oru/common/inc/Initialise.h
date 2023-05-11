#ifndef _COMM_INITIALISE_H_
#define _COMM_INITIALISE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Initialise.h
 * \brief     A file to contain a common interface to an Initialise class
 *
 *
 * \details   This file defines a common interface to an Initialise class
 *
 */

#include "GlobalTypeDefs.h"
#include <string>
#include <sys/time.h>

namespace Mplane
{

/*! \brief The common Initialise base class
 *
 * Initialise is a base class that provides functionality for other subsystems
 * to use.
 * The users MUST implement the pure virtual methods for initialise()
 * as per their requirements.
 *
 * Thus, this class forms a base class for all radio software modules to use,
 * meaning that a radio controlling software module that controls the tasks
 * instantiation and initialisation sequence can be assured of consistent
 * interface behaviour from all software subsystems.
 *
 * Post initialisation, the getter methods can be used to
 * get some history that is retained for the duration of the radio existence.
 *
 * Trace and debug output during initalisation is directed to a specific
 * log file for intialisation only, and is then available at anytime
 * thereafter, to allow access to the events that occurred during system
 * initialisation.
 *
 * An example of how a user would use this interface is:
 *
 * \code
 * #include "GlobalTypeDefs.h"
 *
 * class TestInitialise : public Initialise
 * {
 * public:
 *     virtual ReturnType::State _initialise();
 *
 * };
 *
 * ReturnType::State TestInitialise::_initialise()
 * {
 *     if (isInitComplete())
 *     {
 *         return ReturnType::RT_ALREADY_INITIALISED;
 *     }
 *
 *     setInitStartTime();
 *     ReturnType::State result;
 *     std::string* resultString = new std::string();
 *
 *     result = ReturnType::RT_OK;
 *     *resultString = "INITIALISED OK";
 *
 *     setInitResult(result);
 *     setInitResultString(resultString);
 *     setInitComplete();
 *     setInitEndTime();
 *     setInitDurationTime();
 *
 *     delete resultString;
 *
 *     return result;
 * }
 *
 * \endcode
 */

class Initialise
{
    /*
     * In an OFF_TARGET build we allow the Test harness to be our friend
     */
    friend class InitialiseTestCase;

public:

    /*! \brief  The initialise method
     *
     *  Method called during system startup.
     *
     *  It performs basic initialisation for the common behaviour and then
     *  calls the specific doInit() implementation done by inheritors.
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    ReturnType::State _initialise();

    /*! \brief  The doInit method
     *
     *  Method called by the initialise() method.
     *  This is pure virtual and MUST be implemented by inheritors.
     *
     *  The implementation is expected to set the following before returning:
     *  mInitResult - eg. to ReturnType::RT_OK if all is ok
     *  mInitResultString - eg. to "INITIALISED OK" if all is ok
     *
     *  \return state of RT_OK if successful, RT_other if not.
     */
    virtual ReturnType::State doInit() = 0;

    /*! \brief  Get the initialise result
     *
     *  Method used to return the result of the initialise action
     *
     *  \return  the result of the initialise action
     */
    ReturnType::State getInitResult();

    /*! \brief  Get the initialise result string
     *
     *  Method used to return the result of the initialise action as a string
     *
     *  \return  the resulting string of the initialise action
     */
    std::string& getInitResultString();

    /*! \brief  Get the time of when the initialise is called
     *
     *  Gets the time of when the initialise is called, from the system clock
     *
     *  \return  time when initialise called
     */
    struct timeval* getInitStartTime();

    /*! \brief  Get the time of when the initialise is completed
     *
     *  Gets the time of when the initialise is completed, from the system clock
     *
     *  \return  time when initialise completed
     */
    struct timeval* getInitEndTime();

    /*! \brief  Get the time duration for the initialise in units microseconds
     *
     *  Gets the time duration for the initialise
     *
     *  \return  time duration for the initialise
     */
    int getInitDurationTime();

    /*! \brief  Returns the status of initialisation
     *
     *  Gets the status of the initialisation.
     *
     *  \return  true if init is complete, false otherwise
     */
    bool isInitComplete();


protected:

    /*
     * Protected methods to allow friend classes access to the FPGA
     */

    /*! \brief  Default constructor
     *
     *  Ensure we can only be constructed via an implementing class.
     */
    Initialise();

    /*! Destructor
     *
     *  Destructor, should never be called.
     */
    virtual ~Initialise();


    /*! \brief  Set the initialise result
     *
     *  Method used to set the result of the initialise action.
     *  This will only set the value if the initialisation is not complete, to
     *  avoid situations where the result is modified post initialisation.
     *
     *  \param  value to set
     */
    void setInitResult(ReturnType::State value);

    /*! \brief  Set the initialise result string
     *
     *  Method used to set the result of the initialise action as a string
     *  This will only set the value if the initialisation is not complete, to
     *  avoid situations where the result is modified post initialisation.
     *
     *  \param  value  to set
     */
    void setInitResultString(std::string& value);

    /*! \brief  Set the time of when the initialise is called
     *
     *  Sets the time of when the initialise is called, from the system clock.
     *  This will only set the value if the initialisation is not complete, to
     *  avoid situations where the result is modified post initialisation.
     *
     */
    void setInitStartTime();

    /*! \brief  Set the time of when the initialise is completed
     *
     *  Sets the time of when the initialise is completed, from the system clock.
     *  This will only set the value if the initialisation is not complete, to
     *  avoid situations where the result is modified post initialisation.
     *
     */
    void setInitEndTime();

    /*! \brief  Set the time duration for the initialise
     *
     *  Sets the time duration for the initialise.
     *  This will only set the value if the initialisation is not complete, to
     *  avoid situations where the result is modified post initialisation.
     *
     */
    void setInitDurationTime();

    /*! \brief  Sets the status of initialisation to true, init complete
     *
     *  Sets the status of the initialisation to true.
     *
     */
    void setInitComplete();


private:

    /*!
     * The result of the initialise implementation.
     */
    ReturnType::State mInitResult;

    /*!
     * The result of the initialise implementation as a string.
     */
    std::string mInitResultString;

    /*!
     * Initialise start time
     */
    struct timeval mInitStartTime;

    /*!
     * Initialise end time
     */
    struct timeval mInitEndTime;

    /*!
     * Initialise duration time, in microseconds
     */
    int mInitDurationTime;

    /*!
     * Indicates if the initialisation is complete
     */
    bool mInitComplete;

};


} /* namespace Mplane */

#endif /* _COMM_INITIALISE_H_ */
