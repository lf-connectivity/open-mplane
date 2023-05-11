/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataHistory.js
 * \brief     Stores a history of numeric values
 *
 *
 * \details   Provides a fixed length rolling buffer for numeric values
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype = new ViewData() ;
DataHistory.prototype.constructor = DataHistory ;
function DataHistory(data, numPoints)
{
	this._data = data ;

//console.debug('DataHistory <-> '+data) ;

	if (!numPoints)
		numPoints = 512 ;

	this._buffer = new CircularBuffer(numPoints) ;
	this._views = [] ;
	this._units = '' ;

	// register this view
	this._data.registerView(this) ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.update = function()
{
	// get numeric value
	var num = this._data.getValue() ;
	this._units = this._data.getUnits() ;
//console.debug('DataHistory.update value='+num) ;

	// Add to buffer
	this._buffer.push(num) ;

	// notify views
	for (var i=0; i < this._views.length; ++i)
	{
		this._views[i].update(this) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.onError = function(data, error)
{
	// notify views
	for (var i=0; i < this._views.length; ++i)
	{
		if (this._views[i].onError(this, error))
			this._views[i].update(this) ;
	}
}



//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.capacity = function()
{
	return this._buffer.capacity() ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.numPoints = function()
{
	return this._buffer.size() ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.empty = function()
{
	return this._buffer.empty() ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getValue = function(index)
{
	if (index === null)
		return this._data.getValue() ;
	return this._buffer.get(index) ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getUpdateRate = function()
{
	// rate (ms) at which this Data value will update
	return this._data.getUpdateRate() ;
}


//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getName = function()
{
	return this._data.getName() ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getUnits = function()
{
	return this._units ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.registerView = function(view)
{
	this._views.push(view) ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getMax = function()
{
	return this._buffer.max() ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getMin = function()
{
	return this._buffer.min() ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getSum = function()
{
	return this._buffer.sum() ;
}

//-------------------------------------------------------------------------------------------------------------
DataHistory.prototype.getAve = function()
{
	return this.getSum() / this._buffer.size() ;
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------


