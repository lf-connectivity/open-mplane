/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangMgrORanProcessingElement.h
 * \brief     Virtual interface to manager object for YANG ORAN Processing Element model
 *
 *
 * \details   Virtual interface to manager object for YANG ORAN Processing Element model
 *
 */


#ifndef YANG_HANDLERS_INC_IYANGMGRORANPROCESSINGELEMENT_H_
#define YANG_HANDLERS_INC_IYANGMGRORANPROCESSINGELEMENT_H_

#include <memory>
#include <utility>

#include "GlobalTypeDefs.h"

#include "ILeafContainer.h"

namespace Mplane
{

/*!
 * \class  IYangMgrORanProcessingElement
 * \brief
 * \details
 *
 */
class IYangMgrORanProcessingElement
{
public:
	/**
	 * Singleton
	 */
	static std::shared_ptr<IYangMgrORanProcessingElement> singleton();

	IYangMgrORanProcessingElement() {}
	virtual ~IYangMgrORanProcessingElement() {}

	/**
	 * Initialise the object
	 */
	virtual bool initialise() = 0;

	/**
	 * Assign the leaf container
	 */
	virtual void setLeafContainer(std::shared_ptr<ILeafContainer> leafContainer) = 0;

	/**
	 * Get the leaf container
	 */
	virtual std::shared_ptr<ILeafContainer> leafContainer() = 0;

	/**
	 * Number of processing elements
	 */
	virtual UINT32 numElements() const = 0;

	/**
	 * Create a processing element
	 */
	virtual bool createElement() = 0;

};

}

#endif /* YANG_HANDLERS_INC_IYANGMGRORANPROCESSINGELEMENT_H_ */
