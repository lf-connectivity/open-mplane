/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfigDownload.h
 * \brief     YANG Config file download
 *
 *
 * \details
 *
 */


#ifndef YANG_CONFIG_DOWNLOAD
#define YANG_CONFIG_DOWNLOAD

#include "ConfigDownload.h"

namespace Mplane
{

class YangConfigDownload : public ConfigDownload
{
public:
	using super = ConfigDownload ;

	YangConfigDownload() ;
	virtual ~YangConfigDownload() ;

	/**
	 * Called after object creation in order to perform any other initialisation tasks that can't be done
	 * during initialisation (i.e. ensures all virtual methods get called correctly)
	 *
	 * @param failReason string containing failure reason if fails
	 * @return status. Will be true if initialised ok, false otherwise
	 */
	virtual bool initialise(std::string& failReason) override ;

} ;

}

#endif /* YANG_CONFIG_DOWNLOAD */
