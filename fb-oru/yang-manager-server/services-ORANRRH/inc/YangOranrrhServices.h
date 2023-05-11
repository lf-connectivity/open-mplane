#ifndef _YANGORANRRH_APPSERVICES_H_
#define _YANGORANRRH_APPSERVICES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangOranrrhServices.h
 * \brief     Implementation of YANG ORAN radio services interface to create and controls all radio services
 *
 *
 * \details   Implementation of YANG ORAN radio services interface to create and controls all radio services
 *
 */
#include "OranRrhServices.h"

namespace Mplane
{

class YangOranrrhServices: public OranRrhServices
{
public:

	YangOranrrhServices();

    virtual ~YangOranrrhServices();

};

}

#endif /* _YANGORANRRH_APPSERVICES_H_ */
