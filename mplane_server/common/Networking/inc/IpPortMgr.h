/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IpPortMgr.h
 * \brief     Manages a non-volatile list of IP / port pairs
 *
 *
 * \details   This singleton maintains a list of IP/port pairs which the
 * application can then use
 *
 */

#ifndef NETWORKING_INC_IPPORTMGR_H_
#define NETWORKING_INC_IPPORTMGR_H_

#include "FileConfigWriter.h"
#include "IIpPortMgr.h"

namespace Mplane {

/*!
 * \class  IpPortMgr
 * \brief
 * \details
 *
 */
class IpPortMgr : public virtual IIpPortMgrWriter {
 public:
  IpPortMgr();
  virtual ~IpPortMgr();

  /**
   * Get the list
   */
  virtual std::vector<std::pair<std::string, unsigned>> list() const override;

  /**
   * Get (and clear) any errors
   */
  virtual std::string error() override;

  /**
   * Set the current list contents
   * NOTE: This does not apply the new list to the non-volatile store, it just
   * updates the current list
   */
  virtual void setList(
      const std::vector<std::pair<std::string, unsigned>>& list) override;

  /**
   * Add a single entry to the current list
   * NOTE: This does not apply the new list to the non-volatile store, it just
   * updates the current list
   */
  virtual void addEntry(const std::string& ip, unsigned port) override;

  /**
   * Clear the current list
   * NOTE: This does not apply the new list to the non-volatile store, it just
   * updates the current list
   */
  virtual void clear() override;

  /**
   * Save the current list to non-volatile storage
   */
  virtual bool save() override;

  /**
   * Restore current list from non-volatile storage
   */
  virtual bool restore() override;

 private:
  bool setError(const std::string& error);

 private:
  std::string mError;
  FileConfigWriter mCurrent; //<! Current (live) list
  FileConfigWriter mSaved; //<! The list actually stored to file
};

} // namespace Mplane

#endif /* NETWORKING_INC_IPPORTMGR_H_ */
