/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCalBaseTestCase.h
 * \brief     The Test file header for CommonCalBaseTestCase
 *
 *
 * \details   The Test file header for CommonCalBaseTestCase
 *
 */

#ifndef COMMONCALBASETESTCASE_H_
#define COMMONCALBASETESTCASE_H_


// Includes go here, before the namespace
#include "gtest/gtest.h"


#include "CommonCalBase.h"

namespace Mplane
{

//
class TestCommonCalBase: public CommonCalBase
{
public:

    TestCommonCalBase();

    virtual ~TestCommonCalBase();


    virtual void show();

    virtual ReturnType::State load();


    void setInfo( std::string info );

    void setVersion( int version );


    ReturnType::State mState;

};


}
#endif /* COMMONCALBASETESTCASE_H_ */
