#ifndef _IAPPSETTINGSFACTORY_H_
#define _IAPPSETTINGSFACTORY_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IAppSettingsFactory.h
 * \brief     Factory for creating AppSettings singleton
 *
 *
 *
 */

#include <memory>

#include "IAppSettings.h"

namespace Mplane
{

class IAppSettings;

/**
 * The IAppSettingsFactory class defines a static class used to return an implementation
 * of the IAppSettings pure virtual interface. It can be used during application initialisation
 * or at runtime to determine feature options, hardware type etc.
 *
 *
 * The following code shows an example of how the application settings can be used.
 *

@code

Discovery::Discovery()
{
    std::shared_ptr<IAppSettings> appSettings( IAppSettingsFactory::getInterface() ) ;
    std::shared_ptr<IAppOptions> options(IAppOptions::getInstance() ) ;

    // SSDP handler
    mSsdp = std::make_shared<Ssdp>(
        appSettings->getAppString(),
        appSettings->getBuildVersion() + "-" + std::to_string(appSettings->getBuildNumber()),
        options->getOption("ethssdp").toString(),
        CACHE_MAX_AGE  );
}

@endcode

 *
 */
class IAppSettingsFactory
{

public:
    /*!
     *
     * @return
     */
    static std::shared_ptr<IAppSettings> getInterface();

};

}

#endif /* _IAPPSETTINGSFACTORY_H_ */
