/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ViewMultiData.js
 * \brief     Base class of Data view objects - supports multiple data streams in the one view
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
function ViewMultiData(node$, dataList, filter)
{
	this._init('ViewMultiData', node$, dataList, filter) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewMultiData.prototype.toString = function()
{
	return '[' + this._type + ' : ' + this._data + ' ]' ;
}

//-------------------------------------------------------------------------------------------------------------
ViewMultiData.prototype.update = function()
{
	// base class does nothing
}

//-------------------------------------------------------------------------------------------------------------
ViewMultiData.prototype.onError = function(dataList, error)
{
	// base class does nothing
	console.debug(this+' onError(): '+error) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewMultiData.prototype.getValue = function()
{
	return this._data.getValue() ;
}

//-------------------------------------------------------------------------------------------------------------
ViewMultiData.prototype.getName = function()
{
	return this._data.getName() ;
}

//-------------------------------------------------------------------------------------------------------------
ViewMultiData.prototype.getValueStr = function()
{
	return this._data.getValueStr() ;
}

//-------------------------------------------------------------------------------------------------------------
ViewMultiData.prototype.getHtml = function()
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
ViewMultiData.prototype._init = function(type, node$, dataList, filter)
{
	if (!node$)
		return ;

	if (!dataList)
		return ;

	// common initialisation
	this._dataList = dataList ;
	this._node$ = node$ ;
	this._filter = filter ;
	this._type = type ;

	// register this view
	for (var i=0; i < dataList.length; ++i)
	{
		this._dataList[i].registerView(this) ;
	}
}



