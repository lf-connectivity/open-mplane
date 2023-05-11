/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      OranProcessingElementHandler.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef INC_ORANPROCESSINGELEMENT_HANDLER_H_
#define INC_ORANPROCESSINGELEMENT_HANDLER_H_

#include <memory>
#include <string>

#include "SysrepoGetitemsCallback.h"
#include "YangHandlerSysrepo.h"
#include "YangMgrServer.h"

#include <MplaneProcessingElements.h>

namespace Mplane {

/*!
 * \class  OranProcessingElementHandler
 * \brief
 * \details
 *
 */
class OranProcessingElementHandler : public YangHandlerSysrepo {
 public:
  OranProcessingElementHandler(std::shared_ptr<IYangModuleMgr> moduleMgr);
  virtual ~OranProcessingElementHandler();

  /*
   * Run the initialisation of the handler (can only be done once the rest of
   * the YANG framework is up)
   */
  virtual bool initialise() override;

 protected:
  /*
   * Module change hook - called by module_change() method with filtered events
   */
  virtual void valueChange(
      const std::string& xpath,
      std::shared_ptr<YangParam> oldValue,
      std::shared_ptr<YangParam> newValue);

 private:
  void updateRuElement(
      const std::string& name,
      const std::string& interfaceName,
      const std::string& ruMac,
      const std::string& vlanId,
      const std::string& oduMac);

  void addRuProcessingElementConfig(
      int idx, const std::string& transportSessionType);

  /*
   * Callbacks
   */
  std::shared_ptr<SysrepoGetitemsCallback> mCallback;

  std::map<std::string, std::shared_ptr<ru_elements_t>> mRuElements;

  YangPath mPathParent;

  std::shared_ptr<IYangConfig> mConfig;
};

} // namespace Mplane

#endif /* INC_ORANPROCESSINGELEMENT_HANDLER_H_ */
