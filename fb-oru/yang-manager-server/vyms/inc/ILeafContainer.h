/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILeafContainer.h
 * \brief     Virtual interface to a class that can be a container or a leaf
 *
 *
 * \details   Virtual interface to a class that can be a container or a leaf
 *
 */


#ifndef YANG_HANDLERS_INC_ILEAFCONTAINER_H_
#define YANG_HANDLERS_INC_ILEAFCONTAINER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace Mplane {

/*!
 * \class  ILeafContainer
 * \brief
 * \details
 *
 */
class ILeafContainer {
public:
	ILeafContainer() {}
	virtual ~ILeafContainer() {}

	/**
	 * Get name
	 */
	virtual std::string name() const =0 ;

	/**
	 * Is this element a container?
	 */
	virtual bool isContainer() const =0 ;

	/**
	 * Get leaf value
	 */
	virtual std::string value() const =0 ;


	/**
	 * Get container contents
	 */
	virtual std::vector<std::shared_ptr<ILeafContainer>> contents() const =0 ;


	/**
	 * Remove all elements inside this container
	 */
	virtual void clear() =0 ;

	/**
	 * Remove one element inside this container
	 */
	virtual void removeContainer(std::shared_ptr<ILeafContainer> component) = 0;

	/**
	 * Add a container element to this container's contents
	 */
	virtual std::shared_ptr<ILeafContainer> addContainer(const std::string& name) =0 ;

	/**
	 * Add a container (list) element to this container's contents
	 */
	virtual std::shared_ptr<ILeafContainer> addContainerList(const std::string& name) =0 ;

	/**
	 * Add a container (choice) element to this container's contents
	 */
	virtual std::shared_ptr<ILeafContainer> addContainerChoice(const std::string& name) =0 ;

	/**
	 * Get the named node from this container. If "recursive" is true then decends any containers looking for the named node.
	 * Returns node pointer if found; otherwise returns nullptr
	 */
	virtual std::shared_ptr<ILeafContainer> getNamed(const std::string& name, bool recursive = true) const =0 ;

	/**
	 * Delete the named node from this container. If "recursive" is true then decends any containers looking for the named node.
	 */
	virtual void deleteNamed(const std::string& name, bool recursive = true) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeaf(const std::string& leafName, const std::string& leafValue) =0 ;

	/**
	 * A function called to provide a leaf value
	 */
	using LeafFunc = std::function<std::string(const std::string& leafName)> ;

	/**
	 * Add a leaf value to this container's contents. Rather than being static, this value is created by calling the provided function
	 */
	virtual void addLeaf(const std::string& leafName, LeafFunc func) =0 ;

	/**
	 * Add a leaf unsigned value as hex to this container's contents
	 */
	virtual void addLeafHex(const std::string& leafName, unsigned leafValue) =0 ;

	/**
	 * Add a leaf int value to this container's contents
	 */
	virtual void addLeafInt(const std::string& leafName, int leafValue) =0 ;

	/**
	 * Add a leaf int value to this container's contents
	 */
	virtual void addLeafBool(const std::string& leafName, bool leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafUInt64(const std::string& leafName, uint64_t leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafUInt32(const std::string& leafName, uint32_t leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafUInt16(const std::string& leafName, uint16_t leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafUInt8(const std::string& leafName, uint8_t leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafInt64(const std::string& leafName, int64_t leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafInt32(const std::string& leafName, int32_t leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafInt16(const std::string& leafName, int16_t leafValue) =0 ;

	/**
	 * Add a leaf value to this container's contents
	 */
	virtual void addLeafInt8(const std::string& leafName, int8_t leafValue) =0 ;


	/**
	 * For debug
	 */
	virtual void dump() const =0 ;

} ;

}

#endif /* YANG_HANDLERS_INC_ILEAFCONTAINER_H_ */
