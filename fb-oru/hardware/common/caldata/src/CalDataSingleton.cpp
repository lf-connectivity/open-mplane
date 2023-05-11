/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CalDataSingleton.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "CalData.h"

using namespace Mplane;

std::shared_ptr<ICalData> Mplane::ICalDataFactory::getInterface()
{
    static std::shared_ptr<ICalData> _pInstance( new CalData() );

    return _pInstance;
}
