/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioDatastore.h
 * \brief     Radio datastore base class
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef RADIO_DATASTORE_H_
#define RADIO_DATASTORE_H_

// *****************************************************************************
// Includes
// *****************************************************************************
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <map>

#include "IYangModule.h"
#include "YangTypes.h"
#include "YangParam.h"
#include "Loggable.h"

#include "IRadioDataStore.h"

namespace Mplane {

// typedef struct
//{
//    std::string module;
//} RadDsEvt_t;

// *****************************************************************************
// Radio Datastore
// *****************************************************************************

// -----------------------------------------------------------------------------
// Class:        RadDsEvtMgr
// Description:  Radio Datastore event manager class.
// -----------------------------------------------------------------------------
class RadDsEvtMgr
{
public:
 RadDsEvtMgr();
 ~RadDsEvtMgr();

 bool add(RadDsEvt_t event);
 bool getNext(RadDsEvt_t& event);

protected:

private:
 std::queue<RadDsEvt_t> mEvents;
};

// -----------------------------------------------------------------------------
// Class:        RadioDatastore
// Description:  Radio Datastore base class.
// -----------------------------------------------------------------------------
class RadioDatastore : public virtual IRadioDataStore, public Loggable
{
public:
 RadioDatastore();
 virtual ~RadioDatastore();

 /*
  * Get current state
  */
 virtual IRadioDataStore::State_E getState(void) const override;

 /*
  * Validate current state
  */
 virtual bool isState(IRadioDataStore::State_E state) const override;

 /*
  * Activate datastore
  */
 virtual YangResult_E activate(void) override;

 /*
  * Check if module is installed
  */
 virtual bool isModuleInstalled(const std::string& name) const override;

 /*
  * Get a list of installed modules
  */
 virtual std::vector<std::string> getListOfInstalledModules(
     void) const override;

 /*
  * Get next event
  */
 virtual bool getNextEvent(RadDsEvt_t& event) override;

 /*
  * Debug
  */
 virtual YangResult_E dumpInstalledModules(void) override;

protected:
 /*
  * Sets the current state if state change is valid
  */
 bool setState(IRadioDataStore::State_E state);

 /*
  * Adds a module to the installed list
  */
 bool addInstalledModule(const std::string& name);

 /*
  * List of installed YANG modules
  */
 std::vector<std::string> mModsInstalled;

 /*
  * Event manager
  */
 std::shared_ptr<RadDsEvtMgr> mEvtMgr;

private:
 IRadioDataStore::State_E mState;
};

} /* namespace Mplane */

#endif /* RADIO_DATASTORE_H_ */
