/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootTxFile.h
 * \brief     TroubleshootingFile for Tx ports
 *
 *
 * \details   TroubleshootingFile for Tx ports
 *
 */


#ifndef SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTTXFILE_H_
#define SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTTXFILE_H_

#include "TroubleshootFile.h"

namespace Mplane {

/*!
 * \class  TroubleshootTxFile
 * \brief
 * \details
 *
 */
class TroubleshootTxFile : public TroubleshootFile {
public:
	TroubleshootTxFile() ;
	virtual ~TroubleshootTxFile() ;

protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather
	 * function has been registered.
	 */
	virtual std::string dataGather() override ;

} ;

}

#endif /* SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTTXFILE_H_ */
