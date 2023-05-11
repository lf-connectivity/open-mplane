/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      LeafContainer.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <iostream>

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "LeafContainer.h"

using namespace Mplane;
using namespace std;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
LeafContainer::LeafContainer() :
	mIsContainer(true),
	mIsFunc(false),
	mName(""),
	mValue(""),
	mFunc(),
	mContents()
{
}

//-------------------------------------------------------------------------------------------------------------
LeafContainer::LeafContainer(const std::string &containerName) :
	mIsContainer(true),
	mIsFunc(false),
	mName(containerName),
	mValue(""),
	mFunc(),
	mContents()
{
}

//-------------------------------------------------------------------------------------------------------------
LeafContainer::LeafContainer(const std::string &leafName, const std::string &leafValue) :
	mIsContainer(false),
	mIsFunc(false),
	mName(leafName),
	mValue(leafValue),
	mFunc(),
	mContents()
{
}

//-------------------------------------------------------------------------------------------------------------
LeafContainer::LeafContainer(const std::string &leafName, ILeafContainer::LeafFunc func) :
	mIsContainer(false),
	mIsFunc(true),
	mName(leafName),
	mValue(""),
	mFunc(func),
	mContents()
{
}


//-------------------------------------------------------------------------------------------------------------
LeafContainer::~LeafContainer()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string LeafContainer::name() const
{
	return mName ;
}

//-------------------------------------------------------------------------------------------------------------
bool LeafContainer::isContainer() const
{
	return mIsContainer ;
}

//-------------------------------------------------------------------------------------------------------------
std::string LeafContainer::value() const
{
	if (!mIsFunc)
		return mValue ;

	return mFunc(mName) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILeafContainer> LeafContainer::getNamed(const std::string &name, bool recursive) const
{
	for (auto entry : mContents)
	{
		if (entry->name() == name)
			return entry ;
	}

	if (recursive)
	{
		for (auto entry : mContents)
		{
			if (!entry->isContainer())
				continue ;

			std::shared_ptr<ILeafContainer> ptr(entry->getNamed(name, true)) ;
			if (ptr)
				return ptr ;
		}
	}

	return nullptr ;
}

void LeafContainer::clear()
{
	mContents.clear();
}

/**
 * Remove one element inside this container
 */
void LeafContainer::removeContainer(std::shared_ptr<ILeafContainer> component)
{
	auto foundPos = find(mContents.begin(), mContents.end(), component);
	if ( foundPos != mContents.end())
		mContents.erase(foundPos);
}


//-------------------------------------------------------------------------------------------------------------
void LeafContainer::deleteNamed(const std::string& name, bool recursive)
{
	size_t numChildren = mContents.size();

	if (numChildren == 0)
	{
		return;
	}

	// Delete any node with the given name from the chilren
	mContents.erase(std::remove_if(mContents.begin(),
								   mContents.end(),
								   [name](std::shared_ptr<ILeafContainer> node){
								       return (name == node->name());
								   }), mContents.end());

	if (recursive)
	{
		// Loop through all the children
		for (auto & node : mContents)
		{
			if (!node->isContainer())
				continue ;

			// Delete any nodes with the given name from the children
			node->deleteNamed(name, recursive);
		}
	}

	return;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::shared_ptr<ILeafContainer>> LeafContainer::contents() const
{
	return mContents ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<ILeafContainer> LeafContainer::addContainer(const std::string &name)
{
	if (!mIsContainer)
		throw std::runtime_error("Attempting to add container to leaf element") ;

	std::shared_ptr<ILeafContainer> container(std::make_shared<LeafContainer>(name)) ;
	mContents.push_back(container) ;
	return container ;
}

//-------------------------------------------------------------------------------------------------------------
inline std::shared_ptr<ILeafContainer> LeafContainer::addContainerList(const std::string& name)
{
	return addContainer(name);
}

//-------------------------------------------------------------------------------------------------------------
inline std::shared_ptr<ILeafContainer> LeafContainer::addContainerChoice(const std::string& name)
{
	return addContainer(name);
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeaf(const std::string &leafName, ILeafContainer::LeafFunc func)
{
	if (!mIsContainer)
		throw std::runtime_error("Attempting to add leaf to leaf element") ;

	std::shared_ptr<ILeafContainer> leaf(std::make_shared<LeafContainer>(leafName, func)) ;
	mContents.push_back(leaf) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeaf(const std::string &leafName, const std::string &leafValue)
{
	if (!mIsContainer)
		throw std::runtime_error("Attempting to add leaf to leaf element") ;

	std::shared_ptr<ILeafContainer> leaf(std::make_shared<LeafContainer>(leafName, leafValue)) ;
	mContents.push_back(leaf) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafHex(const std::string &leafName, unsigned leafValue)
{
	std::stringstream ss ;
	ss << "0x" << std::hex << leafValue ;
	addLeaf(leafName, ss.str()) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafInt(const std::string &leafName, int leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}


//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafBool(const std::string &leafName, bool leafValue)
{
	addLeaf(leafName, (leafValue ? "true" : "false")) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafUInt64(const std::string &leafName, uint64_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafUInt32(const std::string &leafName, uint32_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafUInt16(const std::string &leafName, uint16_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafUInt8(const std::string &leafName, uint8_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafInt64(const std::string &leafName, int64_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafInt32(const std::string &leafName, int32_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafInt16(const std::string &leafName, int16_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::addLeafInt8(const std::string &leafName, int8_t leafValue)
{
	addLeaf(leafName, std::to_string(leafValue)) ;
}

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::dump() const
{
	for (auto entry : mContents)
	{
		dump(entry, 0) ;
	}
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void LeafContainer::dump(std::shared_ptr<ILeafContainer> node, unsigned level) const
{
	if (!node->isContainer())
	{
		std::cout << std::string(level+1, '+') << " " << node->name() << " = " << node->value() << std::endl ;
	}
	else
	{
		std::cout << std::string(level+1, '+') << " " << node->name() << "/" << std::endl ;
		for (auto entry : node->contents())
		{
			dump(entry, level+1) ;
		}
	}
}
