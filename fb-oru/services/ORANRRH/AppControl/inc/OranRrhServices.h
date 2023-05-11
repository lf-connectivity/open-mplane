#ifndef _ORANRRH_APPSERVICES_H_
#define _ORANRRH_APPSERVICES_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranRrhServices.h
 * \brief     Class extends the IServicesCtl interface to provide control of host application services.
 *
 *
 * \details   Class extends the IServicesCtl interface to provide control of host application services.
 *
 */
#include "AppServices.h"

namespace Mplane
{

class OranRrhServices: public AppServices
{
    friend class ApplicationServicesTestCase;
    friend class RrhServicesTestCases;
    friend class RrhServicesTestCases_unittest_Test;

public:

    OranRrhServices();

    virtual ~OranRrhServices();

};

}

#endif /* _ORANRRH_APPSERVICES_H_ */
