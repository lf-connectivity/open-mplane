#ifndef _ICALDATA_H_
#define _ICALDATA_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICalData.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "string.h"
#include "GlobalTypeDefs.h"
#include <stdexcept>
#include <memory>


namespace Mplane
{

/**
 * The ICalLoad interface provides interface to cal file loading
 *
 */
class ICalLoad
{
public:


    /**
     * Method called during radio initialisation to load the various calibration
     * data files used by the various calibration data interfaces and populate the
     * ITxCal and IRxCal interface implementations.
     * @return
     */
    virtual ReturnType::State load() = 0;

    /**
     * Method used to indicate that the application has loaded its calibration data
     * @return
     */
    virtual bool isLoaded() = 0;


    /**
     * Default destructor
     */
    virtual ~ICalLoad(){}

};


/**
 * This class defines a base set of functionality expected to be implemented by
 * all calibration data interfaces. This data must include a general information string and
 * version number.
 *
 * The load() method is called during initialisation to load the calibration data from
 * from its particular data store. Once successfully the isLoaded() method is expected
 * to return true.
 *
 */
class ICalBase : public virtual ICalLoad
{
public:

	/**
     * Return a general information string associated with the creation of the calibration
     * data, this data is set by the final implementation using the protected setInfo() method.
     * @return calibration information string
     */
    virtual std::string getInfo() = 0;

    /**
     * Return the version number of the calibration data, this defaults to -1 and must be set by
     * the final calibration data implementation using the protected setVersion() method.
     * @return
     */
    virtual int getVersion() = 0;

    /**
     * Empty virtual destructor for pure virtual interface
     */
    virtual ~ICalBase() {}
};


/**
 * The ICalData interface provides a common base implementation that can be incrementally
 * applied to functionality associated with any number of radio types. It defines access
 * methods used to return the base calibration data interface common to a number of
 * types. This interface can be used to first load the calibration data and secondly
 * provide an interface to the basic calibration object that can be dynamically cast
 * to a known high level implementation.
 *
 * If a particular hardware configuration doesn't support a specific calibration data
 * type, calling the appropriate get method will throw an exception that will cause the
 * application to terminate. This is a logical programming error that must be fixed.
 *
 */
class ICalData : public virtual ICalLoad
{
public:

	// Uses the ICalLoad interface : load() and isLoaded()

    /**
     * Default destructor
     */
    virtual ~ICalData(){}

};


class ICalDataFactory
{
public:
    /** @brief  Get the singleton instance of the calibration data interface
     *
     *  Used to get a reference to the single instance of the radio hardware
     *  calibration data object. This must be implemented using the singleton pattern by the
     *  specific radio implementation.
     *
     *  Must be define in: hardware/<BOARD>/radio/src/<Board>CalDataFactory.cpp
     *
     *  Test mock defined in: vrh/test/src/TestICalData.cpp
     *
     *
     */
    static std::shared_ptr<ICalData> getInterface(void);

};


}


#endif /* _ICALDATA_H_ */
