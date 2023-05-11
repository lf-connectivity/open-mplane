/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataSrcMultiMulti.js
 * \brief     Data source object - (possibly) multiple commands
 *
 *
 * \details   Like the DataSrcMulti but manages one to many commands, each command associated with their own set of objects.
 * 				The commands are collected together into a single "multi" command sent to the TIF interface
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
function DataSrcMulti(intervalMs)
{
	this._interval = intervalMs ;
	this._tif = Tif.getInstance() ;
	
	/*
	 * _cmds hash ends up looking like:
	 * _cmds = {
	 * 
	 * 		'cmd1' : {
	 * 			'param1' : Data obj
	 * 			...
	 * 		}
	 * 		...
	 * }
	 */
	this._cmds = {} ;
	
	// output commands in the order set
	this._cmdsOrder = [] ;	
	

	var dataSrcMulti = this ;

//	// Do immediate update
//	this._update() ;

	// Set periodic update
	if (intervalMs)
		setInterval(function() { dataSrcMulti._update(); }, intervalMs) ;
}

//-------------------------------------------------------------------------------------------------------------
DataSrcMulti.prototype.toString = function()
{
	return '[DataSrcMulti every ' + this._interval + ' ms : ' + Object.keys(this._cmds).length + ' registered cmds]' ;
}

//-------------------------------------------------------------------------------------------------------------
DataSrcMulti.prototype.registerObjects = function(cmd, objects)
{
	// see if new entry
	if (!this._cmds[cmd])
	{
		this._cmds[cmd] = {} ;
		this._cmdsOrder.push(cmd) ;
	}
	
	// Set/update the parameter/object pairs for this command
	for (var param in objects)
	{
		this._cmds[cmd][param] = objects[param] ;
	}

//	// Do immediate update
//	this._update() ;
}

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
DataSrcMulti.prototype._update = function()
{
//	console.log("update "+this) ;
	if (this._cmdsOrder.length == 0)
		return ;

	// Create multi command
	var multicmd = '' ;
	for (var i=0; i < this._cmdsOrder.length; ++i)
	{
		if (i > 0)
			multicmd += Tif.MULTICMD_SEP ; 
		multicmd += this._cmdsOrder[i] ;
	}
	
	// send command
	var dataSrcMulti = this ;
	
	(function(_cmds, _multicmd){
		var cmds = [] ;
		for (var i=0; i < _cmds.length; ++i)
		{
			cmds.push(_cmds[i]) ;
		}
		
		dataSrcMulti._tif.send({
			cmd : _multicmd,
			onOk : function(resp) { dataSrcMulti._onOk(resp, cmds); },
			onError : function(resp) { dataSrcMulti._onError(resp.error, cmds); },
		}) ;
		
	})(this._cmdsOrder, multicmd) ;
}

//-------------------------------------------------------------------------------------------------------------
DataSrcMulti.prototype._onOk = function(response, cmds)
{
//	console.log("onOk %o", this) ;
//	console.log("onOk " + this + "response=%o", response) ;

	// may only have 1 command
	if (response.multicmds.length == 0)
	{
		var cmd = response.cmd ;
		var dataObjs = this._cmds[cmd] ;

		// process single command
		for (var param in dataObjs)
		{
			if (!response.vars.hasOwnProperty(param))
				continue ;

			dataObjs[param].update(response.vars[param]) ;
		}
		return ;
	}
	
	// process the multiple commands/replies
	for (var i=0; i < response.multicmds.length; ++i)
	{
		var cmd = response.multicmds[i] ;
		var dataObjs = this._cmds[cmd] ;
		
		// Need to check each response for an error status
		var status = response.multivars[cmd].Status ;
		if (status != 'OK')
		{
			// Error - pass error back up
			this._onError(response.multivars[cmd].Message, [cmd]) ;
			continue ;
		}

		// OK to process the parameters
		for (var param in dataObjs)
		{
			if (!response.multivars[cmd].hasOwnProperty(param))
			{
				// if the response doesn't contain the expected variable, then something is wrong
				// Tell the Data object if we can
				if (dataObjs[param].onError)
					dataObjs[param].onError('Error: variable "'+param+'" is not present in TIF response') ;
				
				continue ;
			}

			dataObjs[param].update(response.multivars[cmd][param]) ;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
DataSrcMulti.prototype._onError = function(error, cmds)
{
//	console.log("onError %o", this) ;
//	console.log("onError " + this + "response=%o", response) ;
	
	if (!error)
		error = "Error: unexpected error" ;

	for (var i=0; i < cmds.length; ++i)
	{
		var cmd = cmds[i] ;
		var dataObjs = this._cmds[cmd] ;
		
		for (var param in dataObjs)
		{
			if (dataObjs[param].onError)
				dataObjs[param].onError(error) ;
		}
	}
}

