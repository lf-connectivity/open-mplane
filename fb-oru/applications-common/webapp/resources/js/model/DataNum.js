/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataNum.js
 * \brief     Data base class for numeric values
 *
 *
 * \details   Provides the base class for numeric (INT or FLOAT) Data objects
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
DataNum.TYPE = 'NUMERIC' ;

//-------------------------------------------------------------------------------------------------------------
DataNum.prototype = new Data() ;
DataNum.prototype.constructor = DataNum ;
function DataNum(param, updateRate)
{
	this._init(DataNum.TYPE, param, updateRate) ;
	this._units = '' ;
	this._prefix = '' ;
}

//-------------------------------------------------------------------------------------------------------------
DataNum.prototype.getUnits = function()
{
	return this._units ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataNum.prototype._updated = function()
{
	// this string is a scratchpad that is adjusted as the units and number of extracted
	var str = this._valueStr ;

	var numStart = str.search(/[\d\.\-]+/) ;
	if (numStart < 0)
		return ;

	this._prefix = str.substr(0, numStart) ;
	var numStr = str.substr(numStart) ;
	this._value = this._extractNumber(numStr) ;

	// process the number & extract any units
	var unitsStart = numStr.search(/[^\-\+\d\.]+/) ;
	if (unitsStart < 0)
		return ;

	this._units = numStr.substr(unitsStart) ;
}

//-------------------------------------------------------------------------------------------------------------
// Hook - provided by derived object
DataNum.prototype._extractNumber = function(str)
{
	// base class does nothing
	return 0 ;
}

//=============================================================================================================
// PROTECTED UTILS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataNum.prototype._toFloat = function(str)
{
	return parseFloat(str) ;
}

//-------------------------------------------------------------------------------------------------------------
DataNum.prototype._toInt = function(str)
{
	return parseInt(str) ;
}

