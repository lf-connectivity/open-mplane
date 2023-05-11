/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CircularBuffer.js
 * \brief     Circular fixed length buffer
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
function CircularBuffer(numPoints)
{
	this._numPoints = numPoints ;
	this.clear() ;
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.clear = function()
{
	this._buffer = [] ;
	this._pointer = this._numPoints-1 ;
	this.reset() ;
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.empty = function()
{
	return this._buffer.length == 0 ;
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.push = function(val)
{
	this._pointer = (this._pointer + 1) % this._numPoints ;
	this._buffer[this._pointer] = val ;
	
	// Auto-fill the buffer with this value (mainly to keep plots happy!)
	while (this._buffer.length < this._numPoints)
	{
		this._pointer = (this._pointer + 1) % this._numPoints ;
		this._buffer[this._pointer] = val ;
	}
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.capacity = function()
{
	return this._numPoints ;
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.size = function()
{
	return this._buffer.length ;
}

//-------------------------------------------------------------------------------------------------------------
//Gets the index-th item from the start of the circular buffer (wherever that may currently be
CircularBuffer.prototype.get = function(index)
{
	// exceeds bounds
	if (index >= this._buffer.length)
		return null ;

	// buffer not wrapped yet
	if (this._buffer.length < this._numPoints)
		return this._buffer[index] ;

	// wrapped - calc start
	var start = (this._pointer + 1) % this._numPoints ;
	var buffIndex = (start + index) % this._numPoints ;
	return this._buffer[buffIndex] ;
}

//-------------------------------------------------------------------------------------------------------------
//Gets the next item from the buffer
CircularBuffer.prototype.next = function()
{
	var index = this._next ;
	this._next = (this._next + 1) % this._numPoints ;

	return this.get(index) ;
}

//-------------------------------------------------------------------------------------------------------------
// Reset the next pointer
CircularBuffer.prototype.reset = function()
{
	this._next = 0 ;
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.max = function()
{
	if (this._buffer.length == 0)
		return 0 ;
	return Math.max.apply(Math, this._buffer) ;
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.min = function()
{
	if (this._buffer.length == 0)
		return 0 ;
	return Math.min.apply(Math, this._buffer) ;
}

//-------------------------------------------------------------------------------------------------------------
CircularBuffer.prototype.sum = function()
{
	if (this._buffer.length == 0)
		return 0 ;
	return this._buffer.reduce(function(a, b) {return a+b;} ) ;
}


