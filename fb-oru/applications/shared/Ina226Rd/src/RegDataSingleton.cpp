/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegDataFactory.cpp
 * \brief     Singleton factory for IRegData interface
 *
 *
 * \details   This file contains the implementation of the IRegData class
 *
 */

#include "IRegData.h"
#include "RegData.h"

using namespace Mplane;

/**
 * The following provides the IRegData singleton instance
 */
std::shared_ptr<IRegData> Mplane::IRegData::singleton()
{
    static std::shared_ptr<IRegData> _pInstance(new RegData());

    return _pInstance;
}
