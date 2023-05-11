/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SpiPluginAmc7812.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef SPIPLUGINAMC7812_H_
#define SPIPLUGINAMC7812_H_

#include <memory>
#include <map>

#include "plugins/IAmc7812Handler.h"
#include "SpiPluginBase.h"

namespace Mplane {

/*!
 * \class SpiPluginAmc7812
 */
class SpiPluginAmc7812 : public SpiPluginBase {
public:
	static std::shared_ptr<ISpiPlugin> factory(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) ;

	SpiPluginAmc7812(unsigned bus, unsigned devId, unsigned devNum, unsigned shift) ;
	virtual ~SpiPluginAmc7812() ;

	/**
	 * Process the write data and read/write to the read data variable
	 * @param select
	 * @param writeData
	 * @param readData
	 * @return true if ok; false on error
	 */
	virtual bool handleData(unsigned select, unsigned writeData, unsigned writeNumBits, unsigned& readData, unsigned readNumBits) override ;

private:
	enum class Amc7812Op {
		WRITE,
		READ1,
		READ2
	};
	Amc7812Op mOp ;

	unsigned mAddress ;
	std::map<unsigned, std::shared_ptr<IAmc7812Handler>> mHandlers ;
} ;

}

#endif /* SPIPLUGINAMC7812_H_ */
