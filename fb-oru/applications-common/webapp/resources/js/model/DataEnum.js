/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataEnum.js
 * \brief     Data class for ENUM values
 *
 *
 * \details   Provides the base class for ENUM Data objects. This is a DataNum class in that the enumartion is
 * 				converted to an int 0 .. (N-1)
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
DataEnum.TYPE = 'ENUM' ;
DataEnum.ENUM = DataEnum.TYPE+'(' ;

//-------------------------------------------------------------------------------------------------------------
DataFactory.registerType(DataEnum.TYPE, function(param, type, updateRate){
	return new DataEnum(param, type, updateRate) ;
}) ;

//-------------------------------------------------------------------------------------------------------------
// Enumeration is either an array of enumeration strings, or a string specification
// String specification can be either 'ENUM(xx:yy:zz..)' or just 'xx:yy:zz..'
//
DataEnum.prototype = new DataNum() ;
DataEnum.prototype.constructor = DataEnum ;
function DataEnum(param, enumSpec, updateRate)
{
	this._init(DataEnum.TYPE, param, updateRate) ;
	this._setEnum(enumSpec) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataEnum.prototype._setEnum = function(enumSpec)
{
	var enumArray = enumSpec ;
	if (typeof enumSpec === 'string')
	{
		// Is it of the form ENUM(....) ?
		if (enumSpec.startsWith(DataEnum.ENUM))
		{
			var prefixLen = DataEnum.ENUM.length ;
			var len = enumSpec.length - prefixLen - 1 ;
			enumSpec = enumSpec.substr(prefixLen, len) ;
		}

		enumArray = enumSpec.split(':') ;
	}

	this._setEnumArray(enumArray) ;
}

//-------------------------------------------------------------------------------------------------------------
DataEnum.prototype._setEnumArray = function(enumArray)
{
	this._enums = enumArray ;
	this._enumMax = this._enums.length - 1 ;

//console.debug('ENUM '+this._enums+' value: 0..'+this._enumMax) ;
}


//=============================================================================================================
//PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataEnum.prototype._updated = function()
{
	var str = this._valueStr ;
	this._value = this._extractNumber(str) ;
	this._units = '' ;
}

//-------------------------------------------------------------------------------------------------------------
//Hook - provided by derived object
DataEnum.prototype._extractNumber = function(str)
{
//	console.debug('ENUM _extractNumber:'+str+' #enums='+this._enums.length+' => '+this._enums) ;

	// find the string in the list of valid values
	for (var val=0; val < this._enums.length; ++val)
	{
		if (str == this._enums[val])
			return val ;
	}

	console.debug('ENUM _extractNumber:NOT FOUND') ;
	return 0 ;
}

