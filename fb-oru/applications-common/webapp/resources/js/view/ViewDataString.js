/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ViewDataString.js
 * \brief     View a STRING Data object
 *
 *
 * \details   Simple view which sets the node contents based on the Data string
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ViewDataString.prototype = new ViewData() ;
ViewDataString.prototype.constructor = ViewDataString ;
function ViewDataString(node$, data, filter)
{
	this._init('ViewDataString', node$, data, filter) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewDataString.prototype.update = function()
{
	$(this._node$).empty() ;
	$(this._node$).html(this.getHtml()) ;
}



