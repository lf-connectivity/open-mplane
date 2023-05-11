/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RegModelMgr.h
 * \brief     Manages IRegModels
 *
 *
 * \details   Manages IRegModels
 *
 */


#ifndef COMMON_REGMODEL_REGMODELMGR_H_
#define COMMON_REGMODEL_REGMODELMGR_H_

#include <map>
#include "IRegModel.h"

namespace Mplane {

/*!
 * \class  RegModelMgr
 * \brief
 * \details
 *
 */
class RegModelMgr : public virtual IRegModelMgr {
public:
	virtual ~RegModelMgr() ;

	/**
	 * Add a new IRegModel to the list
	 */
	virtual void addModel(IRegModel* regModel) override ;

	/**
	 * Remove a IRegModel from the list
	 */
	virtual void delModel(IRegModel* regModel) override ;

	/**
	 * Get the list of names of the models
	 */
	virtual std::vector<std::string> names() const override ;

	/**
	 * Get the named IRegModel
	 */
	virtual IRegModel* regModel(const std::string& name) const override ;

protected:
	RegModelMgr() ;

private:
	std::map<std::string, IRegModel*> mRegModels ;
} ;

}

#endif /* COMMON_REGMODEL_REGMODELMGR_H_ */
