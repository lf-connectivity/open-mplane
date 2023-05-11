#ifndef _Zcu111FbcOranrrhServices_H_
#define _Zcu111FbcOranrrhServices_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111FbcOranrrhServices.h
 * \brief     Class extends the IServicesCtl interface to provide control of host application services.
 *
 *
 * \details   Class extends the IServicesCtl interface to provide control of host application services.
 *
 */
#include "OranRrhServices.h"

namespace Mplane
{

class Zcu111FbcOranrrhServices: public OranRrhServices
{
public:

    Zcu111FbcOranrrhServices();

    virtual ~Zcu111FbcOranrrhServices();

};

}

#endif /* _Zcu111FbcOranrrhServices_H_ */
