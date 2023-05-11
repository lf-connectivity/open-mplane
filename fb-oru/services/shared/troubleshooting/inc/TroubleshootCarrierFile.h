/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootCarrierFile.h
 * \brief     A TroubleshootFile for carrier
 *
 *
 * \details   A TroubleshootFile for carrier
 *
 */


#ifndef SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTCARRIERFILE_H_
#define SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTCARRIERFILE_H_

#include "TroubleshootFile.h"

namespace Mplane {

/*!
 * \class  TroubleshootCarrierFile
 * \brief
 * \details
 *
 */
class TroubleshootCarrierFile : public TroubleshootFile {
public:
	TroubleshootCarrierFile() ;
	virtual ~TroubleshootCarrierFile() ;

protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather
	 * function has been registered.
	 */
	virtual std::string dataGather() override ;


} ;

}

#endif /* SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTCARRIERFILE_H_ */
