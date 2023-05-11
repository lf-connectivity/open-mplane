/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdPapr.h
 * \brief
 *
 *
 * \details
 *
 */


#ifndef DPDPAPR_H_
#define DPDPAPR_H_

#include <queue>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "IDpdControl.h"
#include "IPaprChange.h"
#include "Mutex.h"
#include "TaskEvent.h"
#include "Observer.hpp"

namespace Mplane {

class DpdPapr : public TaskEvent,

	// PAPR change
	public Observer<IPaprSubject, const IPaprData&>, public virtual IPaprObserver
{
public:
	DpdPapr() ;
	virtual ~DpdPapr() ;


	// PAPR Observer interface

    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data.
     *
     * @param subject
     */
    virtual void update(IPaprSubject& subject) {};
    virtual void update(IPaprSubject& subject, const IPaprData& data) override ;
    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const override;

protected:
	/**
	 * This is the TaskEvent run method that must be provided by inherited objects
	 *
	 * @return true if ok; false if operation failed and task should exit
	 */
	virtual bool runEvent() override ;

private:
	class PaprData : public virtual IPaprData {
	public:
		PaprData() : mTxPort(0), mPapr(0.0) {}
		PaprData(unsigned txPort, const Power& papr) : mTxPort(txPort), mPapr(papr) {}

		virtual unsigned getTxPort() const override {
			return mTxPort;
		}

		virtual Power getPapr() const override {
			return mPapr;
		}

	private:
		unsigned mTxPort ;
		Power mPapr ;
	};

	std::vector< std::shared_ptr<IPaprSubject> > mPaprSubjects ;
	Mutex mMutex ;
	std::queue<PaprData> mData ;
} ;

}

#endif /* DPDPAPR_H_ */
