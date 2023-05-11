/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataFloat.js
 * \brief     Data class for FLOAT values
 *
 *
 * \details   Provides the base class for FLOAT Data objects
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
DataFloat.TYPE = 'FLOAT' ;

//-------------------------------------------------------------------------------------------------------------
DataFactory.registerType(DataFloat.TYPE, function(param, type, updateRate){
	return new DataFloat(param, updateRate) ;
}) ;


//-------------------------------------------------------------------------------------------------------------
DataFloat.prototype = new DataNum() ;
DataFloat.prototype.constructor = DataFloat ;
function DataFloat(param, updateRate)
{
	this._init(DataFloat.TYPE, param, updateRate) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Hook - provided by derived object
DataFloat.prototype._extractNumber = function(str)
{
	return this._toFloat(str) ;
}

