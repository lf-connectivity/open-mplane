#ifndef _VRS_IDPDCONTROL_H_
#define _VRS_IDPDCONTROL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IDpdControl.h
 * \brief     The class definition to control and monitor the DPD
 *
 *
 * \details   Interface class defining a subject for DPD control
 *
 */


#include <memory>
#include <string>
#include <map>
#include <set>
#include <functional>

#include "Power.h"
#include "DataVariant.h"

namespace Mplane
{

// forward declare classes here

/**
 * This class provides a facility to control and monitor the DPD.
 *
 * There is one instance of this class for all Tx paths.
 *
 * This class provides a Subject for observers to attach to if they want to be informed when
 * DPD changes state.
 */
class IDpdControl
{
public:
	IDpdControl() {} ;
    virtual ~IDpdControl() {} ;

    /**
     * Method defines a static method used to get the single instance of
     * the DPD controller module.
     *
     * \return a reference to the DPD control interface class
     */
    static std::shared_ptr<IDpdControl> getInterface();

    /**
     * This method will reset the DPD on the specified channel to
     * unity gain
     * \param tx - tx path [0..MAX-1] to be reset
     * \return true if all ok; false on failure
     */
    virtual bool resetDpd(unsigned tx) = 0;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel (does not wait for successful iteration).
     * \param tx - tx path to enable
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx) = 0;

    /**
     * This method will enable adaption of the DPD on the specified
     * channel. Note that this also waits for at least one successful
     * DPD iteration before returning, or times out.
     * \param tx - tx path to enable
     * \param timeoutMs - timeout time in millisecs
     * \return true if all ok; false on failure
     */
    virtual bool startDpd(unsigned tx, unsigned timeoutMs) = 0;

    /**
     * This method will stop the DPD on the specified channel
     * \param tx - tx path [0..MAX-1] to be stopped
     * \return true if all ok; false on failure
     */
    virtual bool stopDpd(unsigned tx) = 0;

    /**
     * This method will send a new set of parameters to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setParams(unsigned tx, const std::vector<DataVariant>& params) = 0;

    /**
     * Helper method for setParams()
     * Adds an integer value to the vector of DataVariants. Used to create arg list
     * @param list
     * @param name
     * @param value
     * @return true if added ok
     */
    static bool pushInt(std::vector<DataVariant>& list, const std::string& name, int value) ;

    /**
     * Helper method for setParams()
     * Adds a float value to the vector of DataVariants. Used to create arg list
     * @param list
     * @param name
     * @param value
     * @return true if added ok
     */
    static bool pushFloat(std::vector<DataVariant>& list, const std::string& name, float value) ;

    /**
     * Helper method for setParams()
     * Adds a boolean (as an ENUM) value to the vector of DataVariants. Used to create arg list
     * @param list
     * @param name
     * @param value
     * @param enumValues
     * @return true if added ok
     */
    static bool pushBool(std::vector<DataVariant>& list, const std::string& name, bool value,
    		const std::map<bool, std::string>& enumValues) ;

    /**
     * Helper method for setParams()
     * Adds an ENUM value to the vector of DataVariants. Used to create arg list
     * @param list
     * @param name
     * @param value
     * @param enumValues
     * @return true if added ok
     */
    static bool pushEnum(std::vector<DataVariant>& list, const std::string& name, const std::string& value,
    		const std::string& enumValues) ;

    /**
     * This method will send the latest PAPR target to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setPapr(unsigned tx, const Power& papr) = 0;

    /**
     * This method will send the latest SRx attenuation value to the DPD for this tx path
     * \param tx - tx path [0..MAX-1]
     * \return true if all ok; false on failure
     */
    virtual bool setSRxAtten(unsigned tx, const Power& atten) = 0;


    /**
     * Callback function for event or alarm monitor. When conditions match, this callback will be called with the complete
     * set of event/alarm values
     */
    using MonitorFunc = std::function<void(const std::map<std::string, DataVariant>& attributeValues)> ;

    /**
     * Create a named monitor which will wait until an event occurs on a particular tx port and then call the provided callback function.
     * Optionally can add additional variable values which must also be a match before the callback function
     * is called
     */
    virtual void addEventMonitor(const std::string& name, unsigned tx, const std::string& event, MonitorFunc func,
    			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) =0 ;

    /**
     * Create a named monitor which will wait until any event occurs (on any tx) and then call the provided callback function.
     * Optionally can add additional variable values which must also be a match before the callback function
     * is called
     */
    virtual void addEventMonitor(const std::string& name, MonitorFunc func,
    			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) =0 ;

    /**
     * Delete the named monitor
     */
    virtual void delEventMonitor(const std::string& name) =0 ;

    /**
     * Create a named monitor which will wait until an alarm occurs and then call the provided callback function.
     * Optionally can add additional variable values which must also be a match before the callback function
     * is called
     */
    virtual void addAlarmMonitor(const std::string& name, MonitorFunc func,
    			const std::vector<DataVariant>& attributeValues = std::vector<DataVariant>{}) =0 ;

    /**
     * Delete the named monitor
     */
    virtual void delAlarmMonitor(const std::string& name) =0 ;


};

} /* namespace Mplane */

#endif /* _VRS_IDPDCONTROL_H_ */
