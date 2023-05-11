/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      mem-monitor.js
 * \brief     Display live memory usage data
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
MemMonitor.prototype = new MonitorApp() ;
MemMonitor.prototype.constructor = MemMonitor ;
function MemMonitor(host, statusCallback)
{
	this._init(host, 49400, statusCallback) ;
}


//=============================================================================================================
// PROTECTED CALLBACK
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
MemMonitor.prototype.showCallback = function()
{
	$('#content').empty() ;
	console.debug('SHOW') ;
	
	var mainDiv$ = $('<div>', {id : 'main'}) ;
	$('#content').append(mainDiv$) ;

	// Memory used
	this._createPlot('Used Memory', 'memory', 'used', mainDiv$, {
		numPoints 	: 180,
		yRange		: 'auto',
		yAutoMargin : 0.0001,
		yShowZero	: false,
		
		area		: [0.15, 0.2, 0.75, 0.9],
		height		: 200,
		width		: 1200,
		margin		: 20,
		
	}) ;
	
}

//=============================================================================================================
// START
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
$(document).ready(function()
{
	var memMon = null ;
	
    var in$ = $('#setHost') ;
    var stat$ = $('#connectionStat') ;
    
	in$.keyup(function(e){

		var inp$ = in$ ;
		var status$ = stat$ ;
		
		$(status$).empty() ;
		
		if (e.keyCode != 13)
			return ;

		memMon = new MemMonitor($(inp$).val(), function(status){

			if (status == 'CLOSED')
			{
				return ;
			}
			
			
			$(status$).empty() ;

			if (status == 'OK')
			{
				$(status$).append('<img src="resources/images/green-ball.png">') ;
				return ;
			}
			
//			if (status == 'CLOSED')
//			{
//				$(status$).append('<img src="resources/images/grey-ball.png">') ;
//				return ;
//			}
			
			if (status.startsWith("ERROR"))
			{
				$(status$).append('<img src="resources/images/red-ball.png">') ;
				var span$ = $('<span>') ;
				$(span$).css('color', 'red') ;
				$(span$).text(status) ;
				$(status$).append(span$) ;
				return ;
			}
		}) ;
		memMon.start() ;
	}) ;
}) ;

