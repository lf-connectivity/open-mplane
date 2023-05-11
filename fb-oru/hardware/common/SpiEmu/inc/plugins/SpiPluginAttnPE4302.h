/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginAttnPE4302.h
 * \brief     Attenuator plugin
 *
 *
 * \details
 *
 */


#ifndef SPIPLUGINATTNPE4302_H_
#define SPIPLUGINATTNPE4302_H_

#include <memory>
#include <map>

#include "Power.h"
#include "SpiPluginBase.h"

namespace Mplane {

/*!
 * \class SpiPluginAttnPE4302
 */
class SpiPluginAttnPE4302 : public SpiPluginBase {
public:
	static std::shared_ptr<ISpiPlugin> factory(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) ;

	SpiPluginAttnPE4302(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) ;
	virtual ~SpiPluginAttnPE4302() ;

	/**
	 * Process the write data and read/write to the read data variable
	 * @param select
	 * @param writeData
	 * @param readData
	 * @return true if ok; false on error
	 */
	virtual bool handleData(unsigned select, unsigned writeData, unsigned writeNumBits, unsigned& readData, unsigned readNumBits) override ;

	// Interface specific to this model
	Power getAtten() const ;

private:
	Power mAtten ;
} ;

}

#endif /* SPIPLUGINATTNPE4302_H_ */
