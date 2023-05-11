/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MdioFactory.cpp
 * \brief     Management Data Input/Output singleton instance factory
 *
 *
 * \details   Management Data Input/Output singleton instance factory
 *
 */

#include "Mdio.h"

namespace Mplane
{

std::shared_ptr<IMdio> IMdio::getInterface( int deviceIndex )
{
    static std::shared_ptr<IMdio> instance( std::make_shared<Mdio>( deviceIndex ) );

    return instance;
}

} // namespace Mplane
