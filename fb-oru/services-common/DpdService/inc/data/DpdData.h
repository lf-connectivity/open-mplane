/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DpdData.h
 * \brief     Base IDpdData class that provides some utility functions
 *
 *
 * \details
 *
 */


#ifndef DPDDATA_H_
#define DPDDATA_H_

#include <string>
#include <vector>
#include <map>

#include "DataVariant.h"
#include "data/IDpdData.h"

namespace Mplane {

class DpdData : public virtual IDpdData
{
public:
	DpdData() ;
	virtual ~DpdData() ;

	/**
	 * Predicate used to determine whether this data will be used. Base class defaults to always being true
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if data is to be used
	 */
	virtual bool predicate(const std::map<std::string, DataVariant>& attributes) override ;

protected:
	/**
	 * Checks that all of the specified names (of variables) exist in the map
	 * @param variableNames	List of names to check
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if all names are present
	 */
	bool checkVariables(const std::vector<std::string>& variableNames,
			const std::map<std::string, DataVariant>& attributes) const ;

	/**
	 * Checks that the specified variable name exists in the map
	 * @param variableName	name to check
	 * @param attributes	Map of variable/value pairs contained in the DPD message
	 * @return true if name is present
	 */
	bool variablePresent(const std::string& variableName,
			const std::map<std::string, DataVariant>& attributes) const ;
} ;

}

#endif /* DPDDATA_H_ */
