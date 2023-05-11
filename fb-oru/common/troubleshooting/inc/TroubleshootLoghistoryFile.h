/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootLoghistoryFile.h
 * \brief     An IORanLogFile for logging troubleshooting history
 *
 *
 * \details   Creates a troubleshooting file which contains the rolling history of previous logs
 *
 */


#ifndef TROUBLESHOOTING_INC_TROUBLESHOOTLOGHISTORYFILE_H_
#define TROUBLESHOOTING_INC_TROUBLESHOOTLOGHISTORYFILE_H_

#include "TroubleshootFile.h"

namespace Mplane {

/*!
 * \class  TroubleshootLoghistoryFile
 * \brief
 * \details
 *
 */
class TroubleshootLoghistoryFile : public TroubleshootFile {
public:
	TroubleshootLoghistoryFile(const std::string& filename = "history_troubleshoot.log") ;
	virtual ~TroubleshootLoghistoryFile() ;

protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather function has been registered
	 */
	virtual std::string dataGather() override ;

} ;

}

#endif /* TROUBLESHOOTING_INC_TROUBLESHOOTLOGHISTORYFILE_H_ */
