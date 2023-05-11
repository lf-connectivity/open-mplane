#ifndef _COMMON_TXPOWERCONTROL_H_
#define _COMMON_TXPOWERCONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      TxPowerControl.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <atomic>

#include "ITxPcl.h"

#include "Observer.hpp"
#include "ICarrierServer.h"
#include "IRadio.h"
#include "Loggable.h"
#include "fpga/IFpgaAntennaRegs.h"
#include "IFault.h"
#include "FaultOwner.h"
#include "ICommonRadioFaults.h"
#include "MovingAvg.hpp"
#include "Mutex.h"
#include "IDpdControl.h"


namespace Mplane
{

class ITxPort;


/**
 * Defines the return state for the ramp to power function
 */
enum class TxPclRamp
{
    RAMPING, //!< RAMPING
    COMPLETE,//!< COMPLETE
    ERROR    //!< ERROR
};

enum class TxPclOl
{
    SETOL,      //!< SETOL  - initial open loop state
    WAIT_DP,    //!< WAIT_DP - wait for digital power to come in
    CHECK_PM    //!< CHECK_PM - check power measurements
};


/**
 * The TxPowerControl class supports the state machine used to
 * maintain the target power of a transmit path.
 */
class TxPowerControl:   public ITxPcl,
                        public Observer<ITxOn, const ITxEventData&>,
                        public Observer<ITxOff, const ITxEventData&>,
                        public Observer<ITxPower, const ITxEventData&>,
//                        public virtual IDpdInfoClient,
                        public Loggable

{
public:
    friend class TxPowerControlTest;

    class OverPowerOwner: public FaultOwner
    {
    public:
        explicit OverPowerOwner( int path );

        std::shared_ptr<IFault> getFault();

        void set();

        void clear();

    protected:
        std::shared_ptr<IFault> mFault;
    };

    class ConvergenceOwner: public FaultOwner
    {
    public:
        explicit ConvergenceOwner( int path );

        std::shared_ptr<IFault> getFault();

        void set();

        void clear();

    protected:
        std::shared_ptr<IFault> mFault;
    };

    class PowerMeasurementFaultOwner: public FaultOwner
    {
    public:
        explicit PowerMeasurementFaultOwner( int path );

        std::shared_ptr<IFault> getFault();

        void set();

        void clear();

    protected:
        std::shared_ptr<IFault> mFault;
    };


    /**
     * Create an instance of a Tx path control object associated
     * with a given Tx port index.
     * @param portIndex
     */
    explicit TxPowerControl( int portIndex );

    /**
     * Destructor
     */
    virtual ~TxPowerControl();


    /**
     * Handle carrier manager Tx ON update events
     * @param subject ITxOn
     * @param txOnOff associated data
     */
    virtual void update(ITxOn& subject, const ITxEventData& txOnOff);

    /**
     * Handle carrier manager Tx OFF update events
     * @param subject ITxOff
     * @param txOnOff associated data
     */
    virtual void update(ITxOff& subject, const ITxEventData& txOnOff);

    /**
     * Handle DpdService update events containing DPD information
     * @param subject
     * @param data
     */
    //virtual void update(IDpdInfoClient& subject, const IDpdInfo& data) ;

    /**
     * Required by Observer template
     * @return
     */
    virtual const char* name() const
    {
        return "PCL";
    }

    /**
     * Call this method to send TX_ON event to he PCL state machine
     *
     * @return
     */
    virtual bool setTxOn() override;

    /**
     * Call this method to send a TX_OFF event to the PCL state machine
     *
     * @return
     */
    virtual bool setTxOff() override;

    /**
     * Call this method to set the PCL state machine into manual mode
     * @return
     */
    virtual bool setManual() override;

    /**
     * Call this method to set the PCL state machine into testing mode
     * @return
     */
    virtual bool setTesting() override;

    /**
     * Call this method to set the PCL state machine into automatic mode, it
     * will return to its previous state
     * @return
     */
    virtual bool setAuto() override;

    /**
     * Calling this method will force an update to the loop in the current state.
     * This method is called periodically by the parent service of the closed
     * loop power control logic.
     * @return
     */
    virtual bool timerUpdate() override;


    /**
     * Returns the current PCL state
     * @return PCL state
     */
    virtual TxPclState getState() override
    {
        return mState;
    }

    /**
     * Get the current power control loop state, as a string
     * @return
     */
    virtual std::string getStateStr() override ;

    /**
     * Get the power control loop state from the state parameter, as a string
     * @param state the state to get the string for
     * @return the string
     */
    virtual std::string getStateStr(TxPclState state);

    /**
     * Get the power control loop event from the event parameter, as a string
     * @param event the event to get the string for
     * @return the string
     */
    virtual std::string getEventStr(TxPclEvent event);

    /**
     * Method that is called periodically, to run the PCL
     */
    virtual void stateMachine(TxPclEvent);

    /**
     * This method is to show the PCL status.
     */
    virtual void showPcl() override;

    /**
     * This method is to show the PCL status.
     * @param os stream for the output to go into
     */
    virtual void show( std::ostream& os = std::cout );

    /**
     * Method used to return the target out power that the control loop is trying to achieve
     * @return
     */
    virtual Power getTargetPower(void) override
    {
        return mTargetPower;
    }

    /**
     * Get the index into the TxPort to which this instance of PCL is attached
     * @return
     */
    virtual int getIndex() const override
    {
        return mPort;
    }

    /**
     * Method to return the current error between the target power and the actual power.
     *
     * @return
     */
    virtual Power getGainError() override
    {
        return mGainError;
    }


    /**
     * Method to return the last digital input power reading associated with the path
     * @return
     */
    virtual Power getDigitalInputPower()
    {
        return mDigitalInputPower;
    }


    /**
     * Return the set point for the initial open loop radio power value.
     * @return
     */
    virtual Power getOpenLoopTarget()
    {
        return mOpenLoopTarget;
    }

    virtual Power getPaDesignGain()
    {
        return mPADesignGain;
    }

    virtual void setPaDesignGain(const Power& paDesignGain)
    {
        mPADesignGain = paDesignGain;
    }

    /**
     * Method to return the last output power reading associated with the path
     * @return
     */
    virtual Power getRfOutputPower() override
    {
        return mRFOutputPower;
    }

    virtual void setTargetPower(const Power& targetPower)
    {
        mTargetPower = targetPower;
    }

    virtual Power getAttenuation()
    {
        return mAttenuation;
    }

    virtual Power getPABandBackoff()
    {
        return mPABandBackoff;
    }

    /**
     * Method to return the maximum digital input power for the path
     * @return
     */
    virtual Power getMaxInputPower()
    {
        return mMaxInputPower;
    }

    /**
     * Method to return the reference level, the difference between the maximum expected
     * digital input power and the measured digital input power.
     * @return
     */
    virtual Power geInputRefPower()
    {
        return mRefInput;
    }



protected:

    /**
     * Process the initial state for the PCL state machine and transition to the initial
     * TX OFF state. This is normally triggered the a timer tick event from the TX service.
     *
     * @param event
     * @return
     */
    TxPclState initialise( TxPclEvent event );

    /**
     * Process the TX path ON state event , set up open radio power and proceed to WAIT_DPD state.
     *
     * @param event TX_ON - next state WAIT_DPD, MANUAL - next state MANUAL, TESTING - next state TESTING
     * @return  next state of state machine
     */
    TxPclState txOff(TxPclEvent event);

    /**
     * Process the TX path ON state event , set up open radio power and proceed to WAIT_DPD state.
     *
     * @param event TX_ON - next state WAIT_DPD, MANUAL - next state MANUAL, TESTING - next state TESTING
     * @return  next state of state machine
     */
    TxPclState openLoop(TxPclEvent event);


    /**
     * Process the quick ramp to  target power state event and transition through return state
     *
     * @param event
     * @return next state of state machine
     */
    TxPclState ramp(TxPclEvent event);

    /**
     * Keep track of DPD info, waiting for the DPD to complete it's Q=1 iterations
     * which may cause a jump in PA gain. Transition through return state
     *
     * @param event
     * @return next state of state machine
     */
    TxPclState converge(TxPclEvent event);

    /**
     * Process the tracking to target power for fine adjustment state event and transition through return state
     *
     * @param event
     * @return next state of state machine
     */
    TxPclState track(TxPclEvent event);

    /**
     * Process the manual operation state event and transition through return state
     *
     * @param event
     * @return next state of state machine
     */
    TxPclState manual(TxPclEvent event);

    /**
     * Process the testing operation state event and transition through return state
     *
     * @param event
     * @return next state of state machine
     */
    TxPclState testing(TxPclEvent event);

    /**
     * This method will turn off the associated TX path and restore all necessary variables
     * for the off condition.
     *
     * @return true if shutdown successful
     */
    bool shutdown();


    /**
     * Process the wait for DPD estimation on good DPD we can proceed to RAMP state, otherwise
     * go to SHUTDOWN state.
     *
     * @return true if DPD OK
     */
    bool waitDPD();


    /**
     * Method called when state machine is in RAMP state, the intention is to bring the output
     * power to within 0.5dB of the target power as quickly as possible.
     *
     * @return RAMPING, when increasing power, COMPLETE when reached ramp target, ERROR when ramp fails
     */
    virtual TxPclRamp rampToPower();

    /**
     * Method called when state machine is in TRACK state, this method monitors gain error
     * an attempts t0 track any drift in the overall system gain.
     *
     * @return
     */
    bool trackMode();

    TxPclOl    mOlState;
    TxPclState mState;
    TxPclState mPrevState;
    int mPort;
    std::shared_ptr<ITxPort> mTxPort;
    std::shared_ptr<ICarrierServer> mCarrierMgr;
    Power mPABandBackoff;
    Power mBackoff;
    Power mTargetPower;
    Power mPADesignGain;
    Power mGainError;
    Power mOpenLoopTarget;
    Power mRFOutputPower;
    Power mLastRFOutputPower;
    Power mMinMeasRfPower;
    Power mDigitalInputPower;
    Power mMinDigitalPower;
    Power mAttenuation;
    Power mPrevAttenuation;
    Power mMaxInputPower;
    Power mRefInput;
    int   mRampCount;
    int   mGainErrorCount;
    int   mRampAvgCount;
    int   mTrackAvgCount;
    int   mSlowTrackCount;      // use in track mode slow update
    bool  mSlowTrack;           // when this is set in track mode it slows down the update track mode update rate
    int   mWaitDPCount;
    int   mWaitGoodRfCount;
    bool  mDpdRunning;
    int   mRampFailCount ;
    float mRampGainErrorLimit ;
    bool  mInfiniteWaitDP ;		//<! Don't timeout waiting for valid digital power - just wait indefinitely
    int   mGainErrorLimitCount;
    std::atomic<bool>  mDpdTrackOn;

    std::shared_ptr<IFpgaAntennaRegs> mFpga;
    std::shared_ptr<IRadio> mRadio;

    static const int RAMP_FAIL_COUNT = 10;			// Ramping should take less than 3 secs to converge
    static const int CONVERGE_RAMP_FAIL_COUNT = 33;	// Allow ~10 secs for DPD to iterate
    static const int GAIN_ERROR_LIMIT = 20; // changed from 3 to give DPD another chance to normalise the gain

    std::shared_ptr<ICommonRadioFaults> mFaults;
    std::shared_ptr<OverPowerOwner> mOverPowerOwner;
    std::shared_ptr<ConvergenceOwner> mConvergenceOwner;
    std::shared_ptr<PowerMeasurementFaultOwner> mPowerMeasurementFaultOwner;

    MovingAvg<float>    mAvgDigitalInputPower;
    MovingAvg<float>    mAvgRFOutputPower;

    std::shared_ptr<IDpdControl> mDpdControl;

    static const int RAMP_AVG = 3;
    static const int TRACK_AVG = 5;
    static const int SLOW_TRACK = 3;

    static const float RAMP_MODE_ERROR_FACTOR;
    static const float RAMP_MODE_GAIN_ERROR_LIMIT;
    static const float RAMP_MODE_LOWPOWER_GAIN_ERROR_LIMIT;
    static const float RAMP_MODE_LOWPOWER_THRESHOLD;

    static const float TRACK_MODE_GAIN_ERROR;
    static const float TRACK_MODE_SLOW_UPDATE_LIMIT;
    static const float TRACK_MODE_LOW_DIG_POWER_LIMIT;
    static const float TRACK_MODE_ERROR_FACTOR;
    static const float TRACK_MODE_RF_ATTEN_LOW_LIMIT;
    static const float TRACK_MODE_RF_ATTEN_HIGH_LIMIT;

    Mutex mMutex;
};



}

#endif /* _COMMON_TXPOWERCONTROL_H_ */
