#ifndef _TIFTESTIMAGEMANAGEMENT_H_
#define _TIFTESTIMAGEMANAGEMENT_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestImageManagement.h
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

class TestImageManagement: public ImageManagement
{

public:

    /**
     * Constructor
     */
    TestImageManagement();

    /**
     * Constructor with new top-level storage directory (for testing)
     */
    TestImageManagement(const std::string& topdir) ;

    /**
     * destructor
     */
    ~TestImageManagement() { }


protected:


private:

};


} /* namespace Mplane */


#endif /* _TIFTESTIMAGEMANAGEMENT_H_ */
