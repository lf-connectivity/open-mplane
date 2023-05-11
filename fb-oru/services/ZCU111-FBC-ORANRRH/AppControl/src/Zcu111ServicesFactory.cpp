/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111ServicesFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "IServicesCtl.h"
#include "Zcu111FbcOranrrhServices.h"

using namespace Mplane;

// ORAN builds will pull in the ORAN repos - so only define this factory for non-ORAN builds
#ifndef BUILD_IF_ORAN
std::shared_ptr<IServicesCtl> IServicesFactory::create()
{
    static std::shared_ptr<IServicesCtl> instance(std::make_shared<Zcu111FbcOranrrhServices>());
    return instance;
}
#endif
