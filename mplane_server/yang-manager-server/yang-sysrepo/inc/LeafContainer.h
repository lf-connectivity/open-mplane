/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LeafContainer.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_SYSREPO_INC_LeafContainer_H_
#define YANG_SYSREPO_INC_LeafContainer_H_

#include <string>
#include <vector>

#include "ILeafContainer.h"

namespace Mplane {

/*!
 * \class  LeafContainer
 * \brief
 * \details
 *
 */
class LeafContainer : public virtual ILeafContainer {
public:
 LeafContainer();
 LeafContainer(const std::string& containerName);
 LeafContainer(const std::string& leafName, const std::string& leafValue);
 LeafContainer(const std::string& leafName, ILeafContainer::LeafFunc func);
 virtual ~LeafContainer();

 /**
  * Get name
  */
 virtual std::string name() const override;

 /**
  * Is this element a container?
  */
 virtual bool isContainer() const override;

 /**
  * Get leaf value
  */
 virtual std::string value() const override;

 /**
  * Get the named node from this container. If "recursive" is true then decends
  * any containers looking for the named node. Returns node pointer if found;
  * otherwise returns nullptr
  */
 virtual std::shared_ptr<ILeafContainer> getNamed(
     const std::string& name, bool recursive = true) const override;

 /**
  * Delete the named node from this container. If "recursive" is true then
  * decends any containers looking for the named node.
  */
 virtual void deleteNamed(
     const std::string& name, bool recursive = true) override;

 /**
  * Get container contents
  */
 virtual std::vector<std::shared_ptr<ILeafContainer>> contents() const override;

 /**
  * Remove all elements inside this container
  */
 virtual void clear() override;

 /**
  * Remove one element inside this container
  */
 virtual void removeContainer(
     std::shared_ptr<ILeafContainer> component) override;

 /**
  * Add a container element to this container's contents
  */
 virtual std::shared_ptr<ILeafContainer> addContainer(
     const std::string& name) override;

 /**
  * Add a container (list) element to this container's contents
  */
 virtual std::shared_ptr<ILeafContainer> addContainerList(
     const std::string& name) override;

 /**
  * Add a container (choice) element to this container's contents
  */
 virtual std::shared_ptr<ILeafContainer> addContainerChoice(
     const std::string& name) override;

 /**
  * Add a leaf value to this container's contents. Rather than being static,
  * this value is created by calling the provided function
  */
 virtual void addLeaf(
     const std::string& leafName, ILeafContainer::LeafFunc func) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeaf(
     const std::string& leafName, const std::string& leafValue) override;

 /**
  * Add a leaf unsigned value as hex to this container's contents
  */
 virtual void addLeafHex(
     const std::string& leafName, unsigned leafValue) override;

 /**
  * Add a leaf int value to this container's contents
  */
 virtual void addLeafInt(const std::string& leafName, int leafValue) override;

 /**
  * Add a leaf int value to this container's contents
  */
 virtual void addLeafBool(const std::string& leafName, bool leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafUInt64(
     const std::string& leafName, uint64_t leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafUInt32(
     const std::string& leafName, uint32_t leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafUInt16(
     const std::string& leafName, uint16_t leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafUInt8(
     const std::string& leafName, uint8_t leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafInt64(
     const std::string& leafName, int64_t leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafInt32(
     const std::string& leafName, int32_t leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafInt16(
     const std::string& leafName, int16_t leafValue) override;

 /**
  * Add a leaf value to this container's contents
  */
 virtual void addLeafInt8(
     const std::string& leafName, int8_t leafValue) override;

 /**
  * Add a leaf value to this container's contents. The value is fetched
  * from a given IYangConfig object at a path constructed from the
  * baseConfigPath and the leafName.
  */
 virtual void addLeafFromConfig(
     const std::string& leafName,
     std::shared_ptr<IYangConfig> config,
     const std::string& baseConfigPath) override;

 /**
  * Add multiple leaf values to this container's contents. The values are
  * fetched from a given IYangConfig object. The path for each value is
  * constructed from the same baseConfigPath and each leaf name.
  */
 virtual void addLeavesFromConfig(
     const std::vector<std::string>& leafNames,
     std::shared_ptr<IYangConfig> config,
     const std::string& baseConfigPath) override;

 /**
  * Add a leaf-list value to this container's contents. The value is
  * fetched from a given IYangConfig object at a path constructed from
  * the baseConfigPath and the leafName.
  */
 virtual void addListLeafFromConfig(
     const std::string& leafName,
     std::shared_ptr<IYangConfig> config,
     const std::string& baseConfigPath) override;

 /**
  * Add multiple leaf-list value to this container's contents. The values
  * are fetched from a given IYangConfig object. The path for each value
  * is constructed from the same baseConfigPath and each leaf name.
  */
 virtual void addListLeavesFromConfig(
     const std::vector<std::string>& leafNames,
     std::shared_ptr<IYangConfig> config,
     const std::string& baseConfigPath) override;

 /**
  * For debug
  */
 virtual void dump() const override;

private:
 void dump(std::shared_ptr<ILeafContainer> node, unsigned level) const;

private:
 bool mIsContainer;
 bool mIsFunc;
 std::string mName;
 std::string mValue;
 ILeafContainer::LeafFunc mFunc;
 std::vector<std::shared_ptr<ILeafContainer>> mContents;
} ;

}

#endif /* YANG_SYSREPO_INC_LeafContainer_H_ */
