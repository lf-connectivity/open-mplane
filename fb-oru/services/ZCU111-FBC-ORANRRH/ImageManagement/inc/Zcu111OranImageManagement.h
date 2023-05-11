#ifndef _Zcu111OranImageManagement_SVC_H_
#define _Zcu111OranImageManagement_SVC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111OranImageManagement.h
 * \brief     A file to contain the ZCU111 Image Management
 *
 *
 * \brief     This file defines the ZCU111 radio Image Management
 *
 */

#include "ImageManagement.h"

namespace Mplane
{

class Zcu111OranImageManagement: public ImageManagement
{

public:

    /**
     * Constructor
     */
    Zcu111OranImageManagement();

    /**
     * destructor
     */
    ~Zcu111OranImageManagement() { }


protected:


private:

};


} /* namespace Mplane */


#endif /* _Zcu111OranImageManagement_SVC_H_ */
