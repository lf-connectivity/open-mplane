/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootCarrierhwFile.h
 * \brief     A TroubleshootFile for carrier hardware
 *
 *
 * \details   A TroubleshootFile for carrier hardware
 *
 */


#ifndef SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTCARRIERHWFILE_H_
#define SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTCARRIERHWFILE_H_

#include "TroubleshootFile.h"

namespace Mplane {

/*!
 * \class  TroubleshootCarrierhwFile
 * \brief
 * \details
 *
 */
class TroubleshootCarrierhwFile : public TroubleshootFile {
public:
	TroubleshootCarrierhwFile() ;
	virtual ~TroubleshootCarrierhwFile() ;

protected:
	/**
	 * Data gather hook that can be overridden by derived classes. This default uses whatever data gather
	 * function has been registered.
	 */
	virtual std::string dataGather() override ;

} ;

}

#endif /* SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTCARRIERHWFILE_H_ */
