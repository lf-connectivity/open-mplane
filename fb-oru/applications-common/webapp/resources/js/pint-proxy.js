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
PintProxy.prototype = new MonitorApp() ;
PintProxy.prototype.constructor = PintProxy ;
function PintProxy()
{
	console.debug('NEW PintProxy: %s', window.location.hostname) ;
	this._init(window.location.hostname, 49401) ;
}


//=============================================================================================================
// PROTECTED CALLBACK
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
PintProxy.prototype.showCallback = function()
{
	$('#content').empty() ;
	console.debug('SHOW') ;
	
	var mainDiv$ = $('<div>', {id : 'main'}) ;
	$('#content').append(mainDiv$) ;

	this._createMultiPlot('', 'get', [ 'pimReplica', 'ulTotal' ], mainDiv$, {
		height		: 300,
		width		: 900,
		yRange 		: [-120.0, -50.0],
		showMin		: false,
		showMax		: false,
		showAve		: false,
		colours 	: ['red', 'blue'],
		showLegend	: true,
	}) ;

	this._createDataNum('PIM Level', 'get', 'pimLevel', mainDiv$) ;
	
}

//=============================================================================================================
// START
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
$(document).ready(function()
{
	var jtagProxy = new PintProxy() ;
	jtagProxy.start() ;
}) ;

