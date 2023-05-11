/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Data.js
 * \brief     Data object
 *
 *
 * \details   Registered to a single DataSrc (which provides the data string with regular updates), this object
 * 				represents a single value read via the TIF command
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================
Data.TYPE = '' ;

//-------------------------------------------------------------------------------------------------------------
function Data(param)
{
	this._init(Data.TYPE, param) ;
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.toString = function()
{
	return '[Data' + this._type + ' "' + this._param + '" = "' + this._value + '" ]' ;
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.update = function(value)
{
//	console.log('notify ' + this + ' new value=' + value) ;
	this._valueStr = value ;

	// call hook
	this._updated() ;

	// notify views
	for (var i=0; i < this._views.length; ++i)
	{
		this._views[i].update(this) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.onError = function(error)
{
	// call hook
	this._onError(error) ;

	// notify views
	for (var i=0; i < this._views.length; ++i)
	{
		if (this._views[i].onError)
			this._views[i].onError(this, error) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.registerView = function(view)
{
	this._views.push(view) ;
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.getValue = function()
{
	return this._value ;
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.getType = function()
{
	return this._type ;
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.getName = function()
{
	return this._param ;
}


//-------------------------------------------------------------------------------------------------------------
Data.prototype.getValueStr = function()
{
	return this._valueStr ;
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype.getUpdateRate = function()
{
	// rate (ms) at which this Data value will update
	return this._updateRate ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Data.prototype._init = function(type, param, updateRate)
{
	if (!param)
		return ;

	// common initialisation
	this._param = param ;
	this._value = 0 ;
	this._updateRate = updateRate ;
	
	this._valueStr = "" ;
	this._views = [] ;
	this._type = type ;
}

//-------------------------------------------------------------------------------------------------------------
Data.prototype._updated = function()
{
	// base class does nothing
}


//-------------------------------------------------------------------------------------------------------------
Data.prototype._onError = function(error)
{
	// base class does nothing
}


