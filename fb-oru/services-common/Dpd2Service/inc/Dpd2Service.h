/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Dpd2Service.h
 * \brief     Service DPD messages
 *
 *
 * \details   Creates a framework for the DPD services
 *
 */


#ifndef DPD2SERVICE_H_
#define DPD2SERVICE_H_

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <vector>
#include <map>
#include <string>

#include "Observer.hpp"
#include "DataVariant.h"
#include "TaskEvent.h"

#include "IDpdControl.h"
#include "IEmbeddedMgr.h"
#include "IRemoteMsgHandler.h"

namespace Mplane {


class Dpd2Service : public TaskEvent, public virtual IDpdControl
{
public:
	Dpd2Service() ;
	virtual ~Dpd2Service() ;

	static const unsigned TIMEOUT_MS;

    // IDpdControl interface

    /**
     * This method will reset the DPD on the specified channel to
     * unity gain
     * \param tx - tx path [0..MAX-1] to be reset
     * \return true if all ok; false on failure
     */
    virtual bool resetDpd(unsigned tx) override;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel (does not wait for successful iteration).
     * \param tx - tx path to enable
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx) override;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel
     * \param tx - tx path to enable
     * \param timeoutMs - timeout time in millisecs
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx, unsigned timeoutMs) override;

    /**
     * This method will stop the DPD on the specified channel
     * \param tx - tx path [0..MAX-1] to be stopped
     * \return true if all ok; false on failure
     */
    virtual bool stopDpd(unsigned tx) override;

    /**
     * This method will send the latest PAPR target to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setPapr(unsigned tx, const Power& papr) override;

    /**
     * This method will send the latest SRx attenuation value to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setSRxAtten(unsigned tx, const Power& atten) override;

    /**
     * This method will send a new set of parameters to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setParams(unsigned tx, const std::vector<DataVariant>& params) override ;


    /**
     * Create a named monitor which will wait until an event occurs and then call the provided callback function.
     * Optionally can add additional variable values which must also be a match before the callback function
     * is called
     */
    virtual void addEventMonitor(const std::string& name, unsigned tx, const std::string& event, IDpdControl::MonitorFunc func,
    			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) override ;

    /**
     * Create a named monitor which will wait until any event occurs (on any tx) and then call the provided callback function.
     * Optionally can add additional variable values which must also be a match before the callback function
     * is called
     */
    virtual void addEventMonitor(const std::string& name, IDpdControl::MonitorFunc func,
    			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) override ;

    /**
     * Delete the named monitor
     */
    virtual void delEventMonitor(const std::string& name) override ;

    /**
     * Create a named monitor which will wait until an alarm occurs and then call the provided callback function.
     * Optionally can add additional variable values which must also be a match before the callback function
     * is called
     */
    virtual void addAlarmMonitor(const std::string& name, IDpdControl::MonitorFunc func,
    			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) override ;

    /**
     * Delete the named monitor
     */
    virtual void delAlarmMonitor(const std::string& name) override ;

protected:
	// TaskEvent run task
	virtual bool runEvent() ;

	bool sendCommand(std::string command, unsigned tx,
			const std::vector<DataVariant>& params = std::vector<DataVariant>{},
			unsigned timeout = TIMEOUT_MS);

private:
	void eventCallback(const std::string& payloadStr, const std::map<std::string, DataVariant>& attributes) ;
	void alarmCallback(const std::string& payloadStr, const std::map<std::string, DataVariant>& attributes) ;

private:
    std::shared_ptr<IRemoteMsgHandler> mMsgHandler;

    std::mutex mCmdMutex ;
    std::mutex mMutex ;
    std::queue< std::map<std::string, DataVariant> > mEvents ;
    std::queue< std::map<std::string, DataVariant> > mAlarms ;

    class Monitor ;
    std::map<std::string, std::shared_ptr<Monitor>> mEventMonitors ;
    std::map<std::string, std::shared_ptr<Monitor>> mAlarmMonitors ;

} ;

}

#endif /* DPD2SERVICE_H_ */
