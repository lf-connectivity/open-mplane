#ifndef _ETNAFTURADIOCONTROLTESTCASE_H_
#define _ETNAFTURADIOCONTROLTESTCASE_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RrhAppControlTestCase.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include "OranRrhAppControl.h"

namespace Mplane
{

class RrhAppControlTest: public OranRrhAppControl
{
public:

    RrhAppControlTest(): runWasCalled( false )
    {
    };
    virtual ~RrhAppControlTest()
    {

    };
    virtual void show()
    {

    }

    bool runWasCalled;
protected:

    virtual void run()
    {
        runWasCalled = true;
    }

};

}


#endif /* _ETNAFTURADIOCONTROLTESTCASE_H_ */
