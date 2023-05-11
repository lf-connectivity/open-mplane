/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IIpPortMgr.h
 * \brief     Manages a non-volatile list of IP / port pairs
 *
 *
 * \details   This singleton maintains a list of IP/port pairs which the
 * application can then use
 *
 */

#ifndef VCOMMONI_INC_IIPPORTMGR_H_
#define VCOMMONI_INC_IIPPORTMGR_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Mplane {

/*!
 * \class  IIpPortMgr
 * \brief  IP / port manager
 * \details   Read-only access to IP/port list
 *
 */
class IIpPortMgr {
 public:
  /**
   * Singleton
   */
  static std::shared_ptr<IIpPortMgr> singleton();

  IIpPortMgr() {}
  virtual ~IIpPortMgr() {}

  /**
   * Get the list
   */
  virtual std::vector<std::pair<std::string, unsigned>> list() const = 0;

  /**
   * Get (and clear) any errors
   */
  virtual std::string error() = 0;
};

/*!
 * \class  IIpPortMgr
 * \brief  IP / port manager
 * \details   Writable access to IP/port list
 *
 */
class IIpPortMgrWriter : public virtual IIpPortMgr {
 public:
  /**
   * Singleton
   */
  static std::shared_ptr<IIpPortMgrWriter> singleton();

  IIpPortMgrWriter() {}
  virtual ~IIpPortMgrWriter() {}

  /**
   * Set the current list contents
   * NOTE: This does not apply the new list to the non-volatile store, it just
   * updates the current list
   */
  virtual void setList(
      const std::vector<std::pair<std::string, unsigned>>& list) = 0;

  /**
   * Add a single entry to the current list
   * NOTE: This does not apply the new list to the non-volatile store, it just
   * updates the current list
   */
  virtual void addEntry(const std::string& ip, unsigned port) = 0;

  /**
   * Clear the current list
   * NOTE: This does not apply the new list to the non-volatile store, it just
   * updates the current list
   */
  virtual void clear() = 0;

  /**
   * Save the current list to non-volatile storage
   */
  virtual bool save() = 0;

  /**
   * Restore current list from non-volatile storage
   */
  virtual bool restore() = 0;
};

} // namespace Mplane

#endif /* VCOMMONI_INC_IIPPORTMGR_H_ */
