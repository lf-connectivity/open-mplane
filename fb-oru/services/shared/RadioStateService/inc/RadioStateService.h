/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioStateService.h
 * \brief
 *
 *
 * \details
 *
 */

#ifndef RADIO_STATE_SERVICE_H_
#define RADIO_STATE_SERVICE_H_

#include "ILed.h"
#include "IRadioState.h"
#include "IRadio.h"
#include "IDevices.h"
#include "IImageManagement.h"
#include "ICarrierServer.h"
#include "ITxPcl.h"
#include "IAlarm.h"
#include "IVswr.h"
#include "IFaultsList.h"

#include "Service.h"
#include "Observer.hpp"

#include "RrhAlarms.h"

namespace Mplane
{

class RadioStateService : public IRadioState,
						  public Service,
						  public Observer<ITxOn,  const ITxEventData&>,
						  public Observer<ITxOff, const ITxEventData&>
{
public:

	friend class RadioStateServiceTestCases;

	RadioStateService() ;
	virtual ~RadioStateService() ;

    /**
     * Returns the current Radio state
     * @return Radio state
     */
    virtual RadioStatesType getState() const ;

    /**
     * This method is to show the Radio State status.
     */
    virtual void showRadioState() ;

    /**
     * Handle carrier manager Tx OFF update events
     * @param subject ITxOff
     * @param txOnOff associated data
     */
    virtual void update(ITxOff& subject, const ITxEventData& txOnOff);

    /**
     * Handle carrier manager Tx ON update events
     * @param subject ITxOn
     * @param txOnOff associated data
     */
    virtual void update(ITxOn& subject, const ITxEventData& txOnOff);

    /**
     * Handle IAlarmMonitor update events
     * @param alarm associated data
     */
    virtual void update(const IAlarm& alarm);

    /**
     * Required by Observer template
     * @return
     */
    virtual const char* name() const
    {
        return "RADIO_STATE_SERVICE";
    }

private:
    /*!
     *
     * \brief Method to update the LED status indication based on the current radio state
     *
     * \param  radioState The radio state on which to update the indication from
     * \return None
     */
    virtual void updateLedStatusIndication(IRadioState::RadioStatesType radioState);

    /*!
     *
     * \brief Method to update the radio state based on the alarms. This will also
     *        perform any actions required.
     *
     * \param  None
     * \return The new updated radio state
     */
    virtual IRadioState::RadioStatesType updateRadioStateFromAlarms( void );

    /*!
     *
     * \brief Method to update the alarm flags from the alarm list
     *
     * \param  The alarm name to find in the list
     * \return The updated alarm flag condition
     */
    virtual bool getAlarm(std::shared_ptr<IAlarm> alarmToRetrieve);

    /*!
     *
     * \brief Method to reset an alarm in the list
     *
     * \param  The alarm name to find in the list
     * \return Operation successful
     */
    virtual bool resetAlarm(std::shared_ptr<IAlarm> alarmToReset);

    time_t heartBeatAlarmStartTime; //!> Heartbeat timer start time
    bool   heartBeatTimeOutRunning; //!> Boolean to indicate that the heartbeat timer is running

    std::shared_ptr<ICarrierServer> mCarrierMgr; //!> Carrier Manager instance

    std::vector<bool> mIsTxOn; //!> Local store of current state of Tx Carrier
    bool mTxOnUpdated;      //!> Local flag to indicated that TxOn has been updated.

    std::vector<bool> mSetPclPathToOff;  //!> Local flag to indicate shut down path
    std::vector<bool> mSetPclPathToOffCache;  //!> Cache copy of local flag to indicate shut down path

	static const unsigned int NORMAL_STANDBY_FLASH_RATE     = 5; //!! Normal standby flash rate for the LED
	static const unsigned int NORMAL_SW_DOWNLOAD_FLASH_RATE = 5; //!! Software download flash rate for the LED
	static const unsigned int DEGRADED_FLASH_RATE           = 5; //!! Degraded flash rate for the LED

	static const unsigned int HEARTBEAT_TIME_OUT_PERIOD     = (15 * 60); //! Heartbeat time out in seconds

	unsigned int numberOfTxPorts;
	unsigned int numberOfRxPorts;

protected:
    /**
     * Method that MUST be implemented by the inheriting service. The work done
     * by the service, is implemented by this method.
     */
    virtual void show();

    /**
     * Method that MUST be implemented by the inheriting service. The work done
     * by the service, is implemented by this method.
     * @return
     */
    virtual int service();

    /**
     * Method called by the service start() method, to register this service with
     * any particular Observer/Notify interface implementation.
     *
     * @note This method must be implemented by the inheriting service in order
     * for it to register as an observer of other objects.
     *
     * @return true if registration successful.
     */
    virtual bool registerObservers();

    /**
     * Method called as a result of the radio control process calling reset
     * in the service. By default the base class implementation does nothing.
     */
    virtual void doReset();

    mutable Mutex mMutex ; //!> Mutex control to prevent methods from being called from within and outside of the task.

	IRadioState::RadioStatesType mCurrentRadioState; //!> Current radio state.

	// TODO std::shared_ptr<Mplane::ILed>             mSysLedInstance;  //!> Instance of the LED interface.
	std::shared_ptr<Mplane::IRadio>           mRadio;		     //!> Instance of the Radio interface.
	std::shared_ptr<Mplane::IImageManagement> mImageManagement; //!> Instance of the Image Manager.
	// TODO std::shared_ptr<Mplane::ITxPcl>           mPclPath0;        //!> Instance of the PCL path 0.
	// TODO std::shared_ptr<Mplane::ITxPcl>           mPclPath1;        //!> Instance of the PCL path 1.
	// TODO std::shared_ptr<Mplane::IVswr> 		   mVswr;			 //!> Instance of the VSWR monitor.
	std::shared_ptr<Mplane::RrhAlarms>	       mRrhAlarms;	     //!> Instance of the Rrh Alarms.
	std::shared_ptr<Mplane::IFaultsList>      mFaultsList;      //!> Instance of the Faults List.
};

}
#endif /* RADIO_STATE_SERVICE_H_ */
