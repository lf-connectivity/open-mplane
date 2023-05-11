/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataFactory.js
 * \brief     Factory for creating Data objects
 *
 *
 * \details   Creates a DataSrc and all of the associated Data objects
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
function DataFactory()
{
}

//=============================================================================================================
// FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Create a number of DataXX objects that are associated with a DataSrc
//
// cmd - TIF command to generate the data
// interval - Repeat rate in ms (0 means one shot)
// params - Object/hash containing parameter name / data type pairs
//
// A DataXX object is created for each entry in params
//
// Returns an object/hash consisting of param name / DataXX object pairs
//
DataFactory.create = function(cmd, interval, params)
{
	if (params.length == 0)
		return {} ;

	// Now create the list of Data objects
	var dataObjs = {} ;
	for (var name in params)
	{
		dataObjs[name] = DataFactory.createData(name, params[name], interval) ;
	}

	// Create the data source with objects registered to it
	var src = DataSrcFactory.create(cmd, interval, dataObjs) ;

	return dataObjs ;
}

//-------------------------------------------------------------------------------------------------------------
//Create a DataXX object of the specified type
//
//param - parameter name
//type - type string
//
DataFactory.createData = function(param, type, updateRate)
{
	var typeStr = type.toUpperCase() ;

	for (var t in DataFactory._types)
	{
		if (typeStr.startsWith(t))
		{
			return DataFactory._types[t](param, type, updateRate) ;
		}
	}

	return {} ;
}

//-------------------------------------------------------------------------------------------------------------
//Register types - each Data type registers itself
//
//
DataFactory._types = {} ;
DataFactory.registerType = function(type, constructor)
{
	var typeStr = type.toUpperCase() ;
	DataFactory._types[typeStr] = constructor ;
}

