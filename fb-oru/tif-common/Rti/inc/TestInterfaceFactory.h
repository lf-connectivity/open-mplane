/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestInterfaceFactory.h
 * \brief     Factory for creating Mplane::TestInterfaceBase objects
 *
 *
 * \details   Provides a factory that the application can use to create the appropriate board-specific test interface
 *
 */


#ifndef TESTINTERFACEFACTORY_H_
#define TESTINTERFACEFACTORY_H_

#include <memory>
#include "TestInterfaceBase.h"

namespace Mplane {

class TestInterfaceFactory
{
public:

    static std::shared_ptr<TestInterfaceBase> createInstance();
};

}
#endif /* TESTINTERFACEFACTORY_H_ */
