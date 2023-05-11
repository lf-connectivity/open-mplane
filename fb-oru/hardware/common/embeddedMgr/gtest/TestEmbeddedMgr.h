/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TestEmbeddedMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef COMMON_EMBEDDEDMGR_GTEST_TESTEMBEDDEDMGR_H_
#define COMMON_EMBEDDEDMGR_GTEST_TESTEMBEDDEDMGR_H_

#include "EmbeddedMgr.h"

namespace Mplane {

/*!
 * \class  TestEmbeddedMgr
 * \brief
 * \details
 *
 */
class TestEmbeddedMgr : public EmbeddedMgr {
public:
	TestEmbeddedMgr() ;
	virtual ~TestEmbeddedMgr() ;

	// TEST API
	void changeState(unsigned index, IEmbeddedMgr::ProcState state) ;
	static std::string testFirmwarePath() ;

protected:
	// HOOKS to be overridden by derived objects

	/**
	 * Start/stop the processor
	 */
	virtual bool doSetState(unsigned index, bool start) override ;

	/**
	 * Cause the processor to load it's firmware
	 */
	virtual bool doSetFirmware(unsigned index) override ;

	/**
	 * Get the current processor status
	 */
	virtual IEmbeddedMgr::ProcState doStatus(unsigned index) override ;

private:
	std::vector<IEmbeddedMgr::ProcState> mStates ;
} ;

}

#endif /* COMMON_EMBEDDEDMGR_GTEST_TESTEMBEDDEDMGR_H_ */
