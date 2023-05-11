/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataString.js
 * \brief     String Data object
 *
 *
 * \details   Registered to a single DataStringSrc (which provides the data string with regular updates), this object
 * 				represents a single value read via the TIF command
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
DataString.TYPE = 'STRING' ;

//-------------------------------------------------------------------------------------------------------------
DataFactory.registerType(DataString.TYPE, function(param, type, updateRate){
	return new DataString(param, updateRate) ;
}) ;


//-------------------------------------------------------------------------------------------------------------
DataString.prototype = new Data() ;
DataString.prototype.constructor = DataString ;
function DataString(param, updateRate)
{
	this._init(DataString.TYPE, param, updateRate) ;
}

