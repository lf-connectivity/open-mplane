/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginAd9122.h
 * \brief	  AD9122
 *
 *
 * \details
 *
 */


#ifndef SPIPLUGINAd9122_H_
#define SPIPLUGINAd9122_H_

#include <memory>
#include <vector>
#include "GlobalTypeDefs.h"

#include "SpiPluginBase.h"

namespace Mplane {

/*!
 * \class SpiPluginAd9122
 */
class SpiPluginAd9122 : public SpiPluginBase {
public:
	static std::shared_ptr<ISpiPlugin> factory(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) ;

	SpiPluginAd9122(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) ;
	virtual ~SpiPluginAd9122() ;

	/**
	 * Process the write data and read/write to the read data variable
	 * @param select
	 * @param writeData
	 * @param readData
	 * @return true if ok; false on error
	 */
	virtual bool handleData(unsigned select, unsigned writeData, unsigned writeNumBits, unsigned& readData, unsigned readNumBits) override ;

private:
	std::vector<UINT8> mRegs ;
} ;

}

#endif /* SPIPLUGINAd9122_H_ */
