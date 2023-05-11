/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      board-monitor.js
 * \brief     Display live radio data
 *
 *
 * \details   Use the Tif WebSocket interface to poll various radio values and display them
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
BoardMonitor.prototype = new MonitorApp() ;
BoardMonitor.prototype.constructor = BoardMonitor ;
function BoardMonitor()
{
	this._init() ;
}


//=============================================================================================================
// PROTECTED CALLBACK
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
BoardMonitor.prototype.showCallback = function()
{
	$('#content').empty() ;
	console.debug('SHOW') ;
	
	var mainDiv$ = $('<div>', {id : 'main'}) ;
	$('#content').append(mainDiv$) ;

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
}

//=============================================================================================================
// START
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
$(document).ready(function()
{
	var boardMon = new BoardMonitor() ;
	boardMon.start() ;
}) ;

