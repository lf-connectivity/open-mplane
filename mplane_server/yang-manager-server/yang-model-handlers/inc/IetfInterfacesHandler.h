/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IetfInterfacesHandler.h
 * \brief     IETF interfaces module handler
 *
 *
 * \details   IETF interfaces module handler
 *
 */

#ifndef INC_IETFINTERFACES_HANDLER_H_
#define INC_IETFINTERFACES_HANDLER_H_

#include <ctime>
#include <map>
#include <memory>
#include <string>

#include "SysrepoGetitemsCallback.h"
#include "YangHandlerSysrepo.h"
#include "YangMgrServer.h"

#include <MplaneInterfaces.h>

namespace Mplane {

/*!
 * \class  IetfInterfacesHandler
 * \brief
 * \details
 *
 */
class IetfInterfacesHandler : public YangHandlerSysrepo {
 public:
  IetfInterfacesHandler(std::shared_ptr<IYangModuleMgr> moduleMgr);
  virtual ~IetfInterfacesHandler();

  /*
   * Run the initialisation of the handler (can only be done once the rest of
   * the YANG framework is up)
   */
  virtual bool initialise() override;

 protected:
  /**
   * Module change hook - called by module_change() method with filtered events
   */
  virtual void valueChange(
      const std::string& xpath,
      std::shared_ptr<YangParam> oldValue,
      std::shared_ptr<YangParam> newValue);

 private:
  //=========================================================================================================
  // State data
  //=========================================================================================================
  /*
   * Create an interface list entry in the sysrepo
   */
  void createInterfaceListEntry(
      std::shared_ptr<ILeafContainer> dataSte, int idx);

  //=========================================================================================================
  // Configuration data
  //=========================================================================================================
  /*
   * Add an interface entry
   */
  bool addInterface(int idx);

  /*
   * Add class of service container to interface entry
   */
  void addClassOfService(
      std::map<std::string, std::string>& dataCfg,
      int idx,
      std::shared_ptr<interface_t> interface);

  //=========================================================================================================
  // Helper Functions
  //=========================================================================================================

  //=========================================================================================================
  // Parameters
  //=========================================================================================================
  /*
   * Callbacks
   */
  std::shared_ptr<SysrepoGetitemsCallback> mCallback;

  std::map<std::string, std::shared_ptr<interface_t>> mInterfaces;

  /*
   * Parent path
   */
  YangPath mPathParent;

  /*
   * Number of interfaces
   */
  static UINT32 mNumInterfaces;

  /*
   * YANG config loaded from file
   */
  std::shared_ptr<IYangConfig> mConfig;
};

} // namespace Mplane

#endif /* INC_IETFINTERFACES_HANDLER_H_ */
