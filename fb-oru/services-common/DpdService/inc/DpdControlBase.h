/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdControlBase.h
 * \brief     Base class for controlling DPD
 *
 *
 * \details   Provides methods for sending commands and processing replies to/from DPD
 *
 */


#ifndef DPDCONTROLBASE_H_
#define DPDCONTROLBASE_H_

#include <vector>
#include <map>
#include <set>
#include <string>

#include "IFpgaMsg.h"
#include "Loggable.h"
#include "DataVariant.h"

namespace Mplane {

class IFpgaComms ;

class DpdControlBase : public Loggable {
public:
	explicit DpdControlBase(const std::string& name) ;
	virtual ~DpdControlBase() ;

protected:
    /**
     * Send a DPD command with optional arguments
     * @return true if set with acknowledgement from DPD; false otherwise
     */
    virtual bool dpdCmd(const std::string& cmd, const std::vector<DataVariant>& args = {}) ;

    /**
     * Sets one or more DPD parameters and waits for the acknowledge, or timeout
     * @return true if set with acknowledgement from DPD; false otherwise
     */
    virtual bool dpdSet(const std::vector<DataVariant>& args) ;

//    /**
//     * Gets one or more DPD parameters, or timeout
//     * @return true if got values ok from DPD; false otherwise
//     */
//    virtual bool dpdGet(std::map<std::string, DataVariant>& args) ;

    /**
     * Adds an integer value to the vector of DataVariants. Used to create arg list
     * @param list
     * @param name
     * @param value
     * @return true if added ok
     */
    static bool pushInt(std::vector<DataVariant>& list, const std::string& name, int value) ;

    /**
     * Adds a float value to the vector of DataVariants. Used to create arg list
     * @param list
     * @param name
     * @param value
     * @return true if added ok
     */
    static bool pushFloat(std::vector<DataVariant>& list, const std::string& name, float value) ;

    /**
     * Adds an ENUM value to the vector of DataVariants. Used to create arg list
     * @param list
     * @param name
     * @param value
     * @return true if added ok
     */
    static bool pushEnum(std::vector<DataVariant>& list, const std::string& name, const std::string& enums, const std::string& value) ;

    // Get the IFpgaComms object
	std::shared_ptr<IFpgaComms> getFpgaComms() const {
		return mFpgaComms;
	}

private:
    /**
     * Low-level DPD comms - sends a command message and waits for the reply. May time out.
     * @param msg		Command message
     * @param response	Creates a shared pointer to a response message if one is received
     * @param failReason	String set with failure reason on failure
     * @return true if got response; false otherwise (and sets failReason)
     */
    virtual bool commandGetResponse( std::shared_ptr<IFpgaMsg> msg,
    		std::shared_ptr<IFpgaMsg>& response, std::string& failReason ) ;

private:
	std::shared_ptr<IFpgaComms> mFpgaComms ;


} ;

}

#endif /* DPDCONTROLBASE_H_ */
