#ifndef _COMMONCALBASE_H_
#define _COMMONCALBASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCalBase.h
 * \brief     Common calibration record base class used by all calibration record implementation
 *
 *
 * \details   Common calibration record base class used by all calibration record implementation
 *
 */

#include "ICalData.h"
#include "Loggable.h"

namespace Mplane
{

class CommonCalBase: public ICalBase, public Loggable
{
public:
    CommonCalBase( const char* objectName,  const char* subUnitId = "RH");

    /**
     * Pure virtual method to force inheritors to implement.
     */
    virtual void show() = 0;

    /**
     * Pure virtual interface that must be implemented by the actual calibration record.
     * This method is called early in system initialisation to load and parse the data
     * associated with a specific calibration data type.
     *
     * @return RT_OK on success otherwise RT_XXX error indication
     */
    virtual ReturnType::State load() = 0;

    /**
     * Return a general information string associated with the creation of the calibration
     * data, this data is set by the final implementation using the protected setInfo() method.
     * @return calibration information string
     */
    virtual std::string getInfo();

    /**
     * Return the version number of the calibration data, this defaults to -1 and must be set by
     * the final calibration data implementation using the protected setVersion() method.
     * @return
     */
    virtual int getVersion();

    /**
     * Method set by the class that implements the load() method to indicate that the calibration
     * data has been successfully loaded, it can be changed using the protected setLoaded() method.
     * @return
     */
    virtual bool isLoaded();

    /**
     * Simple virtual destructor
     */
    virtual ~CommonCalBase();


protected:

    /**
     * Method used to set the data loaded flag.
     * @param loaded
     */
    void setLoaded( bool loaded );

    /**
     * Method used to set the calibration data information.
     * @param info
     */
    void setInfo( const std::string& info );

    /**
     * Method used to set the calibration data version.
     * @param version
     */
    void setVersion( int version );

private:
    int mVersion;           //>! Holds the calibration data version number, initialised to -1
    std::string mInfo;      //>! Holds the calibration data information string
    bool mIsLoaded;         //>! Flag used to indicate if the calibration data is successfully loaded

};

}

#endif /* _COMMONCALBASE_H_ */
