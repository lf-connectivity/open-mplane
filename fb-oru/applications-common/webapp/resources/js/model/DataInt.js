/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataInt.js
 * \brief     Data class for INT values
 *
 *
 * \details   Provides the base class for INT Data objects
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
DataInt.TYPE = 'INT' ;

//-------------------------------------------------------------------------------------------------------------
DataFactory.registerType(DataInt.TYPE, function(param, type, updateRate){
	return new DataInt(param, updateRate) ;
}) ;


//-------------------------------------------------------------------------------------------------------------
DataInt.prototype = new DataNum() ;
DataInt.prototype.constructor = DataInt ;
function DataInt(param, updateRate)
{
	this._init(DataInt.TYPE, param, updateRate) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Hook - provided by derived object
DataInt.prototype._extractNumber = function(str)
{
	return this._toInt(str) ;
}

