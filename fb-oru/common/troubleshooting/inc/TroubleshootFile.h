/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TroubleshootFile.h
 * \brief     Base class implementing a troubleshoot log file
 *
 *
 * \details   Base class implementing a troubleshoot log file. This base class needs a data gather function to be defined. Otherwise
 *            derived classes can override the dataGather() method
 *
 */


#ifndef TROUBLESHOOTING_INC_TROUBLESHOOTFILE_H_
#define TROUBLESHOOTING_INC_TROUBLESHOOTFILE_H_

#include "ORanLogFile.h"

namespace Mplane
{

/*!
 * \class  TroubleshootFile
 * \brief
 * \details
 *
 */
class TroubleshootFile : public ORanLogFile
{
	public:
		TroubleshootFile(const std::string & filename);
		virtual ~TroubleshootFile();

	protected:

	private:

};

}

#endif /* TROUBLESHOOTING_INC_TROUBLESHOOTFILE_H_ */
