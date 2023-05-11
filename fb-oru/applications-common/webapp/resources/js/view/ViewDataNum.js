/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ViewDataNum.js
 * \brief     View an INT or FLOAT Data object
 *
 *
 * \details   Simple view which sets the node contents based on the Data numeric value
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ViewDataNum.prototype = new ViewData() ;
ViewDataNum.prototype.constructor = ViewDataNum ;
function ViewDataNum(node$, data, filter)
{
	this._init('ViewDataNum', node$, data, filter) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewDataNum.prototype.update = function()
{
	$(this._node$).empty() ;
	var html = this.getHtml() ;
	$(this._node$).html(html) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewDataNum.prototype.getValueStr = function()
{
	var fval = this._data.getValue() ;
	return fval.toFixed(2) + this._data.getUnits() ;
}


//-------------------------------------------------------------------------------------------------------------
ViewDataNum.prototype.onError = function(data, error)
{
	$(this._node$).empty() ;
	
	var span$ = $('<span class="error">').append(error) ;
	$(this._node$).append(span$) ;
}



