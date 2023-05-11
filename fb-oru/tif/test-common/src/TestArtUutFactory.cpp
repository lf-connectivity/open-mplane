/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestArtUutFactory.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "TestArtUut.h"

using namespace Mplane;
/**
 * The following provides the common CPRI interface class.
 */
std::shared_ptr<IArtUut> Mplane::IArtUut::getInterface()
{
    static std::shared_ptr<IArtUut> _pInstance(new TestArtUut());

    return _pInstance;
}
