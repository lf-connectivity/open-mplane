/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AisgCommand.h
 * \brief     Stores details regarding a particular Aisg command
 *
 *
 * \details
 *
 */


#ifndef AISGCOMMAND_H_
#define AISGCOMMAND_H_

#include <memory>
#include <vector>
#include <map>
#include <functional>

namespace Mplane {

class AisgCommand
{
public:

	typedef std::function<void(std::vector<unsigned char>)> respCallback;

	AisgCommand(unsigned char id, unsigned long timeout, respCallback cb);

	~AisgCommand() {};

	unsigned char getCommndId(void);
	unsigned long getCommandTimeout(void);
	respCallback getResponseCallback(void);

private:

	unsigned char mId;
	unsigned long mTimeout;
	respCallback mRespCb;
};
}

#endif //AISGCOMMAND_H_
