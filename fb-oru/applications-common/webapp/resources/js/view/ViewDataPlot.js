/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ViewDataPlot.js
 * \brief     Plot data
 *
 *
 * \details   Attaches to a Data object that fills a DataHistory buffer. This object then plots the
 * 				data in the DataHistory buffer
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ViewDataPlot.prototype = new ViewData() ;
ViewDataPlot.prototype.constructor = ViewDataPlot ;
function ViewDataPlot(node$, data, plotOptions)
{
	// gather plot options and set defaults
	this._setOptions(plotOptions, data, node$) ;

	this._buffer = new DataHistory(data, this._options.numPoints+1) ;
	this._init('ViewDataPlot', node$, this._buffer) ;
	
}

//-------------------------------------------------------------------------------------------------------------
ViewDataPlot.prototype.update = function()
{
	$(this._node$).empty() ;
	var div$ = $('<div>', {
		id: this._options.id,
		height: this._options.height,
		width: this._options.width,
	}) ;
	$(this._node$).append(div$) ;

	var vdp = this ;
	$('#'+this._options.id).svg(function(svg) {vdp._plot(svg, vdp);});
}

//-------------------------------------------------------------------------------------------------------------
ViewDataPlot.prototype.onError = function(data, error)
{
	$(this._node$).empty() ;
	var div$ = $('<div class="plot-error error">').append(error) ;
	$(this._node$).append(div$) ;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ViewDataPlot.prototype._setOptions = function(options, data, node$)
{
	this._options = {
		id			: 'vdp-'+data.getName(),
		area		: [0.15, 0.2, 0.75, 0.9],
		numPoints 	: 30,	// show 30s
		height		: 200,
		width		: 400,
		margin		: 20,
		colour		: 'blue',
		yRange		: 'auto',
		yShowZero	: true,
		yAutoMargin	: 0.1,
		showGrid	: true,
		showAve		: true,
		aveColour	: 'green',
		showMin		: true,
		minColour	: 'cyan',
		showMax		: true,
		maxColour	: 'red',
		showLegend	: false,
		
		resizeContainer : null ,
	} ;
	$.extend(this._options, options) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewDataPlot.prototype._plot = function(svg, vdp)
{
//console.debug('PLOT: '+vdp._buffer.getName()+' rate='+vdp._buffer.getUpdateRate()+' ms') ;
//	console.debug('PLOT: #points='+vdp._buffer.numPoints()+' capacity='+vdp._buffer.capacity()) ;
	var numPoints = vdp._buffer.numPoints() ;
	var totalPoints = vdp._options.numPoints ;
	
	var plotPoints = totalPoints ;
	
	// get units
	var units = vdp._buffer.getUnits() ;

	var tickLen = 10 ;

	// Preload with min/max/ave
	var maxVal = vdp._buffer.getMax();
	var minVal = vdp._buffer.getMin();
	var aveVal = vdp._buffer.getAve();
	
//	console.debug('max='+maxVal+' min='+minVal+' ave='+aveVal) ;
	
	// Set up plot
    svg.plot.noDraw().
    	area(vdp._options.area).
    	equalXY(false).			// *really* need to set this otherwise you get very squashed graphs!
        addFunction(vdp._buffer.getName(),
    		function(x) {
        		var y = vdp._buffer.getValue(x);
//        		console.debug('PLOT('+x+')='+y) ;
        		return y;
        	},
    		[0, totalPoints],
    		plotPoints,
    		vdp._options.colour,
    		1) ;
    
    // average
    if (vdp._options.showAve)
    	svg.plot.addFunction('ave', 
        	function(x) {
	    		return aveVal;
	    	},
			[0, totalPoints],
			plotPoints,
			vdp._options.aveColour,
			1) ;
    
    // min
    if (vdp._options.showMin)
    	svg.plot.addFunction('min',
        	function(x) {
	    		return minVal;
	    	},
			[0, totalPoints],
			plotPoints,
			vdp._options.minColour,
			1) ;
    
    // max
    if (vdp._options.showMax)
    	svg.plot.addFunction('max',
        	function(x) {
	    		return maxVal;
	    	},
			[0, totalPoints],
			plotPoints,
			vdp._options.maxColour,
			1) ;
    
    // grid
    if (vdp._options.showGrid)
    	svg.plot.gridlines({stroke: 'gray', strokeDashArray: '2,2'}, 'gray');
    
    
    var xticks = 1 ;
    if (totalPoints > 10)
    	xticks = 10 ;
    
    svg.plot.xAxis.scale(0, totalPoints).ticks(xticks, 0, tickLen, 'se').title('s');
    
    var yMin = 0 ;
    var yMax = 1 ;
    if ($.isArray(vdp._options.yRange) && (vdp._options.yRange.length == 2))
    {
    	yMin = vdp._options.yRange[0] ;
    	yMax = vdp._options.yRange[1] ;
    }
    else
    {
    	yMin = vdp._buffer.getMin() ;
    	yMax = vdp._buffer.getMax() ;
    	
    	// 3 cases: 
    	// a. ymax > ymin > 0 - if show zero then make ymin=0
    	// b. 0 > ymax > ymin - if show zero then make ymax=0
    	// c. ymax > 0 > ymin - if show zero do nothing
    	
    	if (vdp._options.yShowZero)
    	{
    		if (yMin > 0)
    			yMin = 0 ;
    		
    		if (yMax < 0)
    			yMax = 0 ;
    	}
    	
    	if (yMin > 0)
    		yMin -= yMin*vdp._options.yAutoMargin ;
    	else if (yMin < 0)
    		yMin += yMin*vdp._options.yAutoMargin ;
    	
    	// We assume the units normalise the values so ensure max y is at least 1
    	if ((yMax > 0) && (yMax < 1))
    		yMax = 1 ;

    	if (yMax > 0)
    		yMax += yMax*vdp._options.yAutoMargin ;
    	else if (yMax < 0)
    		yMax -= yMax*vdp._options.yAutoMargin ;
    }
    
    // if currently getting all 0's then fudge the graph to plot 0
    if ((yMin == 0) && (yMax == 0))
    	yMax = 1 ;
    
    var yRange = yMax - yMin ;
    var numTens = Math.floor(Math.log(yRange) / Math.log(10)) ;
    var yTicks = Math.pow(10, numTens) ;
    var yTicksMinor = yTicks * 0.2 ;

//console.debug('ymin='+yMin+' yMax='+yMax+' : yTicks='+yTicks) ;

    
    svg.plot.yAxis.scale(yMin, yMax).ticks(yTicks, yTicksMinor, tickLen, 'nw').title(units);
   	svg.plot.legend.show(vdp._options.showLegend);
    
    // Draw
    svg.plot.redraw();

    // Expand the clip area so we can actually see everything!
    var clip$ = $('clipPath', svg.root()) ;
    var rect$ = $('rect', clip$) ;
    var x = parseInt(rect$.attr('x')) ;
    var y = parseInt(rect$.attr('y')) ;
    var height = parseInt(rect$.attr('height')) ;
    var width = parseInt(rect$.attr('width')) ;
    var plotArea = [x, y, width, height] ;
//    console.debug('plot area: '+plotArea) ;
//    console.debug('area: '+svg.plot.area()) ;
    rect$.attr({
    	x : 0,
    	y : 0,
    	height : vdp._options.height,
    	width : vdp._options.width
    }) ;
    
    // move x labels
	var yLabelY = plotArea[1] + plotArea[3] ;
	var xLabelY = yLabelY + 2*tickLen ;
    var xLabels$ = $('.xAxisLabels', svg.root()) ;
    $('text', xLabels$).each(function(){
    	$(this).attr('y', xLabelY) ;
    }) ;
    
    // scale x-axis to show in seconds
    var updateRate = vdp._buffer.getUpdateRate() ;
    var xscaling = 1000.0 / updateRate ;
    $('text', xLabels$).each(function(){
    	var val = parseInt($(this).text()) ;
    	val /= xscaling ;
    	$(this).text(val.toString()) ;
    }) ;

    
    
    // Move the units display - if we have units
	$('text', svg.root()).each(function(){
		
	    if (units)
	    {
    		if ($(this).text() === units)
    		{
    			// move the display to the top of the graph
    			$(this).attr({
    				x: plotArea[0]-tickLen,
    				y: plotArea[1]-tickLen
    			})
    			return ;
    		}
	    }
	    
		if ($(this).text() === 's')
		{
			// move the X axis units (seconds) down below x axis
			$(this).attr({
				x: plotArea[0]+plotArea[2]+tickLen,
				y: xLabelY,
				'text-anchor' : 'start'
			})
			return ;
		}
	}) ;
    
    // show x&y origin
    svg.text(plotArea[0], xLabelY, '0', { 'text-anchor' : 'middle'}) ;
    svg.text(plotArea[0]-tickLen, yLabelY, yMin.toString(), { 'text-anchor' : 'end'}) ;
    
    
    
    
    // Show min/max/ave as necessary
    var mmaX = plotArea[0]+plotArea[2] ;
    var mmaYmin = yLabelY ;
    var mmaYmax = plotArea[1]+22.72 ;
    var mmaYave = (mmaYmax+mmaYmin) / 2.0 ;
    
    if (vdp._options.showAve)
        svg.text(mmaX, mmaYave, 'Ave:'+aveVal.toFixed(2), { 'text-anchor' : 'start'}) ;
    
    if (vdp._options.showMin)
        svg.text(mmaX, mmaYmin, 'Min:'+minVal.toFixed(2), { 'text-anchor' : 'start'}) ;
    
    if (vdp._options.showMax)
        svg.text(mmaX, mmaYmax, 'Max:'+maxVal.toFixed(2), { 'text-anchor' : 'start'}) ;
    
    
    // If we have control of the parent container then resize it
    if (vdp._options.resizeContainer)
    	$(vdp._options.resizeContainer).css({
    		height : vdp._options.height+vdp._options.margin,
        	width : vdp._options.width+vdp._options.margin
    	}) ;
}
