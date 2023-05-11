/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegModelMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <algorithm>
#include "RegModelMgr.h"

using namespace Mplane;

//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class RegModelMgrInst : public RegModelMgr {
public:
	RegModelMgrInst() : RegModelMgr() {}
	virtual ~RegModelMgrInst() {}
};
std::shared_ptr<IRegModelMgr> IRegModelMgr::singleton()
{
	static std::shared_ptr<IRegModelMgr> instance(std::make_shared<RegModelMgrInst>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::RegModelMgr::~RegModelMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RegModelMgr::addModel(IRegModel* regModel)
{
	mRegModels[regModel->name()] = regModel ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::RegModelMgr::delModel(IRegModel *regModel)
{
	auto it(mRegModels.find(regModel->name())) ;
	if (it != mRegModels.end())
	{
		mRegModels.erase(it) ;
		return ;
	}

	it = std::find_if(mRegModels.begin(), mRegModels.end(),
		[regModel](const auto& entry) { return entry.second == regModel;}
			) ;

	if (it != mRegModels.end())
	{
		mRegModels.erase(it) ;
		return ;
	}
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> Mplane::RegModelMgr::names() const
{
	std::vector<std::string> modelNames ;
	for (auto& entry : mRegModels)
		modelNames.push_back(entry.first) ;
	return modelNames ;
}

//-------------------------------------------------------------------------------------------------------------
IRegModel* Mplane::RegModelMgr::regModel(const std::string &name) const
{
	if (mRegModels.find(name) == mRegModels.end())
		return nullptr ;

	return mRegModels.at(name) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::RegModelMgr::RegModelMgr() :
	mRegModels()
{
}
