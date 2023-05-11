#ifndef _Zcu111APPCONTROL_H_
#define _Zcu111APPCONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111AppControl.h
 * \brief     Application control for Zcu111
 *
 *
 * \details
 *
 */

#include "OranRrhAppControl.h"

namespace Mplane
{

/**
 *
 */
class Zcu111AppControl:  public OranRrhAppControl
{
public:
    Zcu111AppControl();

    /**
     * destructor
     */
    virtual ~Zcu111AppControl();

};

}

#endif /* _Zcu111APPCONTROL_H_ */
