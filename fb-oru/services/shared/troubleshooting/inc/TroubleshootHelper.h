/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootHelper.h
 * \brief     Static methods for setting up troubleshooting
 *
 *
 * \details   Static methods for setting up troubleshooting
 *
 */


#ifndef SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTHELPER_H_
#define SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTHELPER_H_


namespace Mplane {

/*!
 * \class  TroubleshootHelper
 * \brief
 * \details
 *
 */
class TroubleshootHelper {
public:
	/**
	 * Add the troubleshooting files that all applications will want
	 */
	static void commonSetup() ;
} ;

}

#endif /* SHARED_TROUBLESHOOTING_INC_TROUBLESHOOTHELPER_H_ */
