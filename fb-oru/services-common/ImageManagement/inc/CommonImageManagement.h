#ifndef _COMMONIMAGEMANAGEMENT_SVC_H_
#define _COMMONIMAGEMANAGEMENT_SVC_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      EtnaRadioImageManagement.h
 * \brief     A file to contain the ETNA radio Image Management
 *
 *
 * \brief     This file defines the ETNA radio Image Management
 *
 */

// Includes go here, before the namespace

#include "ImageManagement.h"

namespace Mplane
{

class CommonImageManagement: public ImageManagement
{

public:

    /**
     * Constructor
     */
    CommonImageManagement();

    /**
     * destructor
     */
    ~CommonImageManagement() { }


protected:


private:

};


} /* namespace Mplane */


#endif /* _COMMONIMAGEMANAGEMENT_SVC_H_ */
