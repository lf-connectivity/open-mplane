/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      MonitorApp.js
 * \brief     Generic monitor application
 *
 *
 * \details   Base monitor application. Actual applications are derived from this. Provides all the common
 * 				helper methods 
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
function MonitorApp()
{
	console.debug('NEW MonitorApp') ;
	this._init() ;
}

//-------------------------------------------------------------------------------------------------------------
// Application start point - called when window opened
MonitorApp.prototype.start = function()
{
	this._initLimits() ;
	this._tif.start() ;
}


//=============================================================================================================
//PROTECTED CALLBACK
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Derived class implements this method to display the data
MonitorApp.prototype.showCallback = function()
{
/** EXAMPLE
	
	$('#content').empty() ;
	
	var mainDiv$ = $('<div>', {id : 'main'}) ;
	$('#content').append(mainDiv$) ;

	// Memory used
	this._createPlot('Used Memory', '.memory', 'used', mainDiv$) ;
	
	// FPGA temperature
	this._createPlot('FPGA temp', '.fpga.getTemperature', 'temperature', mainDiv$) ;
	
	// TX 
	var txDivs$ = this._columnDiv('TX', mainDiv$, this.numTx) ;
	for (var tx=1; tx <= this.numTx; ++tx)
	{
		this._createDataNum('TX'+tx+' freq: ', '.tx.getFreq '+tx, 'value', txDivs$[tx-1]) ;
		this._createPlot('TX'+tx+' temp', '.tx.getTemp '+tx, 'result', txDivs$[tx-1]) ;
		this._createPlot('TSSI'+tx, '.srx.getFwdTssi 1 '+tx, 'tssiResult', txDivs$[tx-1]) ;
	}
	
	// RX 
	var rxDivs$ = this._columnDiv('RX', mainDiv$, this.numRx) ;
	for (var rx=1; rx <= this.numRx; ++rx)
	{
		this._createDataNum('RX'+rx+' freq: ', '.rx.getFreq '+rx, 'value', rxDivs$[rx-1]) ;
		this._createPlot('RSSI'+rx, '.rx.getRssi '+rx, 'rssiResult', rxDivs$[rx-1]) ;
		this._createPlot('ADC'+rx, '.rx.getAdcRms '+rx, 'result', rxDivs$[rx-1]) ;
	}
	
	// SRX 
	var srxDivs$ = this._columnDiv('SRX', mainDiv$, 1) ;
	var srx=1; 
	this._createDataNum('SRX'+srx+' freq: ', '.srx.getFreq '+srx, 'value', srxDivs$[srx-1]);
	this._createPlot('ADC'+srx, '.srx.getAdcRms '+srx, 'value', srxDivs$[srx-1]) ;

	// Fibres 
	var fibreDivs$ = this._columnDiv('FIBRE', mainDiv$, this.numFibres) ;
	for (var fibre=0; fibre < this.numFibres; ++fibre)
	{
		this._createPlot('SFP'+fibre+' rx power', '.cpri.get '+fibre, 'sfpRxPower', fibreDivs$[fibre]) ;
	}
	
*/
}



//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._init = function(host, port, statusCallback)
{
	console.debug('MonitorApp.prototype._init') ;

	this._rate = 1000 ;
	
	// Get connection
	this._tif = Tif.getInstance() ;
	if (host)
		this._tif.setHost(host) ;
	if (port)
		this._tif.setPort(port) ;
	if (statusCallback)
		this._tif.setStatusCallback(statusCallback) ;
	
	// id
	this.dataId = 1 ;
	
	// limits
	this.numTx = 1 ;
	this.numRx = 1 ;
	this.numCarriers = 1 ;
	this.numFibres = 1 ;
	
	// Grab the page url and see if there are any options
	var href = window.location.href ;
	var queryPos = href.indexOf('?') ;
	if (queryPos == -1)
		return ;
	
	var queries = href.substr(queryPos+1).split('&') ;
	for (var i=0; i < queries.length; ++i)
	{
		var fields = queries[i].split('=') ;
		if (fields.length != 2)
			continue ;

		if (fields[0].toLowerCase() == 'tifdebug')
		{
			this._tif.enableDebug() ;
			console.debug('TIF DEBUG=ON') ;
			continue ;
		}
		
		if (fields[0].toLowerCase() == 'rate')
		{
			this._rate = parseInt(fields[1]) ;
			console.debug('RATE='+this._rate) ;
			continue ;
		}
	}

};

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._initLimits = function()
{
	var monitor = this ;
	
	this._tif.send({
		cmd : '.system.getLimits',
		onOk : function(response) { monitor._getLimits(response); },
		onError : function(error) { monitor._onError(error); }
	}) ;

};

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._getLimits = function(response)
{
	var monitor = this ;
	
	// Get the values
	Tif.setResponseVarInt(response, 'numTx', this) ; 
	Tif.setResponseVarInt(response, 'numRx', this) ; 
	Tif.setResponseVarInt(response, 'numCarriers', this) ; 
	Tif.setResponseVarInt(response, 'numFibres', this) ; 
	console.debug('LIMITS: Tx='+this.numTx+' Rx='+this.numRx+' Carriers='+this.numCarriers+' Fibres='+this.numFibres) ;
	
	// Can now display
	window.setTimeout(function() {monitor.showCallback();}, 100) ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._onError = function(error)
{
	console.debug('ERROR: '+error) ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._labelled = function(labelType, label, node$, id)
{
	var containerId = labelType + '-' + id ;
	
	var div$ = $('<div class="labelled-'+labelType+'">') ;
	node$.append(div$) ;
	var label$ = $('<label>', {id : 'label'+containerId}) ;
	label$.append(label) ;
	div$.append(label$) ;
	var divCont$ = $('<div>', {id : containerId}).append('&nbsp;') ;
	div$.append(divCont$) ;
	
	return containerId ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._columnDiv = function(label, node$, numCols)
{
	var div$ = $('<div class="columns">') ;
	node$.append(div$) ;
	var label$ = $('<label>') ;
	label$.append(label) ;
	div$.append(label$) ;
	
	var cont$ = $('<div class="column-container">') ;
	div$.append(cont$) ;
	
	var divs$ = [] ;
	for (var col=0; col < numCols; ++col)
	{
		var cd$ = $('<div class="column">') ;
		cont$.append(cd$) ;
		divs$.push(cd$) ;
	}
	cont$.append('<br style="clear: both;" />') ;
	return divs$ ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._labelledLeft = function(label, node$, id)
{
	return this._labelled('left', label, node$, id) ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._labelledPlot = function(label, node$, id)
{
	return this._labelled('plot', label, node$, id) ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._plot = function(label, data, node$, options)
{
	var containerId = this._labelledPlot(label, node$, this.dataId++) ;

	if (!options)
		options = {} ;
	options.id = 'plot-'+containerId ;
	options.resizeContainer = $('#'+containerId).parent() ;
	var plotView = new ViewDataPlot('#'+containerId, data, options) ;

	return 'label'+containerId ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._multiplot = function(label, dataList, node$, options)
{
	var containerId = this._labelledPlot(label, node$, this.dataId++) ;

	if (!options)
		options = {} ;
	options.id = 'plot-'+containerId ;
	options.resizeContainer = $('#'+containerId).parent() ;
	var plotView = new ViewMultiDataPlot('#'+containerId, dataList, options) ;

	return 'label'+containerId ;
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._dataNum = function(label, data, node$)
{
	var containerId = this._labelledLeft(label, node$, this.dataId++) ;
	var intView = new ViewDataNum('#'+containerId, data) ;
}


//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._createPlot = function(label, cmd, varname, node$, options)
{
	var params = {} ;
	params[varname] = 'FLOAT' ;
	var objs = DataFactory.create(cmd, this._rate, params) ;
	
	var labelId = this._plot(label, objs[varname], node$, options) ;
	
	var intView = new ViewDataNum('#'+labelId, objs[varname], function(str) {
		return label + ': ' + str ;
	}) ;
	
}

//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._createMultiPlot = function(label, cmd, varnames, node$, options)
{
	var dataList = [] ;
	
	for (var i=0; i < varnames.length; ++i)
	{
		var params = {} ;
		params[varnames[i]] = 'FLOAT' ;
		var objs = DataFactory.create(cmd, this._rate, params) ;
		dataList.push(objs[varnames[i]]) ;
	}
	var labelId = this._multiplot(label, dataList, node$, options) ;
	
//	var intView = new ViewDataNum('#'+labelId, objs[varname], function(str) {
//		return label + ': ' + str ;
//	}) ;
	
}


//-------------------------------------------------------------------------------------------------------------
MonitorApp.prototype._createDataNum = function(label, cmd, varname, node$)
{
	var params = {} ;
	params[varname] = 'FLOAT' ;
	var objs = DataFactory.create(cmd, this._rate, params) ;
	this._dataNum(label, objs[varname], node$);
}



