/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataSrcFactoryFactory.js
 * \brief     Factory for creating Data source object
 *
 *
 * \details   Creates a DataSrcFactory or DataSrcFactoryMulti object as needed
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
function DataSrcFactory()
{
}

//=============================================================================================================
//FACTORY
//=============================================================================================================
DataSrcFactory._intervals = {} ;

//-------------------------------------------------------------------------------------------------------------
DataSrcFactory.create = function(cmd, intervalMs, objects)
{
	// For immediate commands, return a new object
	if (intervalMs == 0)
		return new DataSrc(cmd, intervalMs, objects) ;
	
	// For timed commands, create a single instance per interval. This single instance then combines all of the
	// commands in that interval into a single multi-cmd line
	if (!DataSrcFactory._intervals[intervalMs])
	{
		// new entry
		DataSrcFactory._intervals[intervalMs] = new DataSrcMulti(intervalMs) ;
	}
	
	// create/appends command/objects pair
	DataSrcFactory._intervals[intervalMs].registerObjects(cmd, objects) ;
	return DataSrcFactory._intervals[intervalMs] ;
	
}

