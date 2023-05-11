#ifndef _COMMON_CONFIG_BASE_H_
#define _COMMON_CONFIG_BASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonConfigBase.h
 * \brief     Common configuration record base class used by all configuration record implementation
 *
 *
 * \details   Common configuration record base class used by all configuration record implementation
 *
 */

#include "IConfigData.h"
#include "Loggable.h"

namespace Mplane
{

class CommonConfigBase: public IConfigBase, public Loggable
{
public:
    CommonConfigBase( const char* objectName,  const char* subUnitId = "RH");

    /**
     * Pure virtual method to force inheritors to implement.
     */
    virtual void show() = 0;

    /**
     * Method used to provide path to load the configuration
     */
    virtual void setPath(std::shared_ptr<IConfigDownload> download) override;

    /**
     * Method used to get the path to load the configuration
     */
    virtual std::string getPath() override;

    /**
     * Pure virtual interface that must be implemented by the actual configuration record.
     * This method is called early in system initialisation to load and parse the data
     * associated with a specific configuration data type.
     *
     * @return RT_OK on success otherwise RT_XXX error indication
     */
    virtual ReturnType::State load() = 0;

    /**
     * Return a general information string associated with the creation of the configuration
     * data, this data is set by the final implementation using the protected setInfo() method.
     * @return configuration information string
     */
    virtual std::string getInfo();

    /**
     * Return the version number of the configuration data, this defaults to -1 and must be set by
     * the final configuration data implementation using the protected setVersion() method.
     * @return
     */
    virtual int getVersion();

    /**
     * Method set by the class that implements the load() method to indicate that the configuration
     * data has been successfully loaded, it can be changed using the protected setLoaded() method.
     * @return
     */
    virtual bool isLoaded();

    /**
     * Simple virtual destructor
     */
    virtual ~CommonConfigBase();


protected:

    /**
     * Method used to set the data loaded flag.
     * @param loaded
     */
    void setLoaded( bool loaded );

    /**
     * Method used to set the configuration data information.
     * @param info
     */
    void setInfo( const std::string& info );

    /**
     * Method used to set the configuration data version.
     * @param version
     */
    void setVersion( int version );

private:
    int mVersion;           //>! Holds the configuration data version number, initialised to -1
    std::string mInfo;      //>! Holds the configuration data information string
    bool mIsLoaded;         //>! Flag used to indicate if the configuration data is successfully loaded
    std::shared_ptr<IConfigDownload> mConfigDownload;//!> Config download object
};

}

#endif /* _COMMON_CONFIG_BASE_H_ */
