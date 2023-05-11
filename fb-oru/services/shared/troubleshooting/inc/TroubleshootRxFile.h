/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootRxFile.h
 * \brief     TroubleshootingFile for Rx ports
 *
 *
 * \details   TroubleshootingFile for Rx ports
 *
 */


#ifndef SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTRXFILE_H_
#define SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTRXFILE_H_

#include "TroubleshootFile.h"

namespace Mplane {

/*!
 * \class  TroubleshootRxFile
 * \brief
 * \details
 *
 */
class TroubleshootRxFile : public TroubleshootFile {
public:
	TroubleshootRxFile() ;
	virtual ~TroubleshootRxFile() ;

protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather
	 * function has been registered.
	 */
	virtual std::string dataGather() override ;

} ;

}

#endif /* SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTRXFILE_H_ */
