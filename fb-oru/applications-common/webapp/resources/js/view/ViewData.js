/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ViewData.js
 * \brief     Base class of Data view objects
 *
 *
 * \details   Base class of view objects which update their HTML whenever the associated Data class updates it's
 * 				value
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
function ViewData(node$, data, filter)
{
	this._init('ViewData', node$, data, filter) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype.toString = function()
{
	return '[' + this._type + ' : ' + this._data + ' ]' ;
}

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype.update = function()
{
	// base class does nothing
}

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype.onError = function(data, error)
{
	// base class does nothing
	console.debug(this+' onError(): '+error) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype.getValue = function()
{
	return this._data.getValue() ;
}

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype.getName = function()
{
	return this._data.getName() ;
}

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype.getValueStr = function()
{
	return this._data.getValueStr() ;
}

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype.getHtml = function()
{
	var str = this.getValueStr() ;
	if (this._filter)
		str = this._filter(str) ;
	return str ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ViewData.prototype._init = function(type, node$, data, filter)
{
	if (!node$)
		return ;

	if (!data)
		return ;

	// common initialisation
	this._data = data ;
	this._node$ = node$ ;
	this._filter = filter ;
	this._type = type ;

	// register this view
	this._data.registerView(this) ;
}



