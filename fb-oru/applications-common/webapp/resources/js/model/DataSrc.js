/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataSrc.js
 * \brief     Data source object - single command
 *
 *
 * \details   Sources data by running and processing a TIF command at a regular interval. Data objects register
 * 				themselves to this object on a particular TIF response variable. The Data object then gets
 * 				notified every time the value is updated
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
function DataSrc(cmd, intervalMs, objects)
{
	this._tif = Tif.getInstance() ;
	this._cmd = cmd ;
	this._interval = intervalMs ;
	this._dataObjs = {} ;

	if (objects)
		this.registerObjects(objects) ;

	var dataSrc = this ;

	// Do immediate update
	this._update() ;

	// Set periodic update
	if (intervalMs)
		setInterval(function() { dataSrc._update(); }, intervalMs) ;
}

//-------------------------------------------------------------------------------------------------------------
DataSrc.prototype.toString = function()
{
	return '[DataSrc "' + this._cmd + '" every ' + this._interval + ' ms : ' + Object.keys(this._dataObjs).length + ' registered]' ;
}

//-------------------------------------------------------------------------------------------------------------
DataSrc.prototype.registerObjects = function(objects)
{
	for (var param in objects)
	{
		this._dataObjs[param] = objects[param] ;
	}

	// Do immediate update
	this._update() ;
}

//=============================================================================================================
//FACTORY
//=============================================================================================================
DataSrc._intervals = {} ;

//-------------------------------------------------------------------------------------------------------------
DataSrc.factory = function(cmd, intervalMs, objects)
{
	// For immediate commands, return a new object
	if (intervalMs == 0)
		return new DataSrc(cmd, intervalMs, objects) ;
	
	// For timed commands, create a single instance per interval. This single instance then combines all of the
	// commands in that interval into a single multi-cmd line
	if (!DataSrc._intervals[intervalMs])
	{
		// new entry
		DataSrc._intervals[intervalMs] = {
			obj : null,
			cmds: {}
		}
	}
	
}


//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataSrc.prototype._update = function()
{
//	console.log("update "+this) ;
	if (Object.keys(this._dataObjs).length == 0)
		return ;

	// send command
	var dataSrc = this ;
	this._tif.send({
		cmd : this._cmd,
		onOk : function(resp) { dataSrc._onOk(resp); },
		onError : function(resp) { dataSrc._onError(resp); },
	}) ;
}

//-------------------------------------------------------------------------------------------------------------
DataSrc.prototype._onOk = function(response)
{
//	console.log("onOk %o", this) ;
//	console.log("onOk " + this + "response=%o", response) ;

	for (var param in this._dataObjs)
	{
//		console.log(" + check "+param+' : '+response.vars[param]) ;

		if (!response.vars.hasOwnProperty(param))
		{
			// if the response doesn't contain the expected variable, then something is wrong
			// Tell the Data object if we can
			if (this._dataObjs[param].onError)
				this._dataObjs[param].onError('Error: variable "'+param+'" is not present in TIF response') ;
			
			continue ;
		}
		
		this._dataObjs[param].update(response.vars[param]) ;
	}

}

//-------------------------------------------------------------------------------------------------------------
DataSrc.prototype._onError = function(response)
{
//	console.log("onError %o", this) ;
//	console.log("onError " + this + "response=%o", response) ;
	
	// get the error string and pass that back
	var error = reponse.error ;
	if (!error)
		error = "Error: unexpected error" ;

	// pass error up to Data objects if they have a method to handle it
	for (var param in this._dataObjs)
	{
		if (this._dataObjs[param].onError)
			this._dataObjs[param].onError(error) ;
	}
}

