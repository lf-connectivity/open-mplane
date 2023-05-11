/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestCarrier.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef TESTCARRIER_H_
#define TESTCARRIER_H_

#include "CommonCarrier.h"
#include "CommonCarrierServer.h"


namespace Mplane {

const unsigned MAX_CARRIERS{4} ;
const unsigned MAX_CARRIERS_PER_TXPATH{2} ;
const unsigned MAX_CARRIERS_PER_RXPATH{2};
const unsigned MAX_TXPATHS{2};
const unsigned MAX_RXPATHS{2};


class TestRadioCarrier: public CommonCarrier
{
public:
	TestRadioCarrier(unsigned carrierIndex, unsigned MAX_TXPATHS, unsigned MAX_RXPATHS) :
		CommonCarrier(carrierIndex, MAX_TXPATHS, MAX_RXPATHS)
	{}

    virtual ~TestRadioCarrier() {}

};


class TestRadioCarrierServer: public CommonCarrierServer
{
public:
    TestRadioCarrierServer() :
        CommonCarrierServer( MAX_CARRIERS, MAX_CARRIERS_PER_TXPATH,
        		MAX_CARRIERS_PER_RXPATH, MAX_TXPATHS, MAX_RXPATHS )
    {
        // test add carrier methods with good index
        for( unsigned index = 0; index < MAX_CARRIERS; index++ )
        {
        	TestRadioCarrier *carrierSetter = new TestRadioCarrier( index, MAX_TXPATHS, MAX_RXPATHS );
            addCarrierSetter( *carrierSetter ) ;
            TestRadioCarrier *carrier = new TestRadioCarrier( index, MAX_TXPATHS, MAX_RXPATHS );
            addCarrier( *carrier ) ;
        }

    }

    virtual ~TestRadioCarrierServer() {}

    void writeErrorMsg(char* str)
    {
        setCarrierFailureStr( str );
    }

private:
    std::vector<TestRadioCarrier>	mCarriers ;
    std::vector<TestRadioCarrier>	mCarrierSetters ;
};



}

#endif /* TESTCARRIER_H_ */
