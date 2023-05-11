#ifndef _TIFTESTIMAGEMANAGEMENT_H_
#define _TIFTESTIMAGEMANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TifTestImageManagement.h
 * \brief     A file to contain the TIF test  Image Management
 *
 *
 * \brief     This file defines the TIF test  Image Management
 *
 */

// Includes go here, before the namespace

#include "ImageManagement.h"

namespace Mplane
{

class TifTestImageManagement: public ImageManagement
{

public:

    /**
     * Constructor
     */
    TifTestImageManagement();

    /**
     * destructor
     */
    ~TifTestImageManagement() { }


protected:


private:

};


} /* namespace Mplane */


#endif /* _TIFTESTIMAGEMANAGEMENT_H_ */
