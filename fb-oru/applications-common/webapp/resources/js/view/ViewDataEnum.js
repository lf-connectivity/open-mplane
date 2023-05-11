/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ViewDataEnum.js
 * \brief     View an ENUM Data object
 *
 *
 * \details   Uses the fixed set of enumeration codings 0..N of the enum in order to select
 * 				from a specified set of values.
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// Constructor needs the type-specific 'settings' object, If not specified then this just reverts to showing
// the enumeration value string
//
// When specified, settings object is of the form:
// {
//		html: string/function/array - created html node
//		className: string/function/array - sets the class of the created html node
//      attr : { sets the attribute of the created html node
//		...
//			e.g. src: string/function/array - sets the 'src' attribute of the created html node
//		},
//		css : { sets the css of the created html node
//			...
//			e.g. color: string/function/array - sets the 'color' style of the created html node
//		},
// }
//
// string/function/array means:
// * string - use the fixed string
// * function - call the function with the enumeration coding value
// * array - index the array with the enumeration coding value to get the string
//
ViewDataEnum.prototype = new ViewData() ;
ViewDataEnum.prototype.constructor = ViewDataEnum ;
function ViewDataEnum(node$, data, settings)
{
	this._init('ViewDataEnum', node$, data) ;
	this._saveSettings(settings) ;
}

//-------------------------------------------------------------------------------------------------------------
ViewDataEnum.prototype.update = function()
{
	$(this._node$).empty() ;

	if (!this._settings || !this._settings.html)
	{
		$(this._node$).html(this.getHtml()) ;
		return ;
	}

	var index = this.getValue() ;
	var htmlStr = this._evalSetting(this._settings.html, index) ;
	var html$ = $(htmlStr) ;
	$(this._node$).append(html$) ;

	if (this._settings.className)
	{
		var classStr = this._evalSetting(this._settings.className, index) ;
		html$.addClass(classStr) ;
	}

	// attributes
	if (this._settings.attr)
	{
		for (var attr in this._settings.attr)
		{
			if (!attr)
				continue ;
			var attrStr = this._evalSetting(this._settings.attr[attr], index) ;
			if (!attrStr)
				continue ;
			html$.attr(attr, attrStr) ;
		}
	}

	// style
	if (this._settings.css)
	{
		for (var css in this._settings.css)
		{
			if (!css)
				continue ;
			var cssStr = this._evalSetting(this._settings.css[css], index) ;
			if (!cssStr)
				continue ;
			html$.css(css, cssStr) ;
		}
	}
}


//=============================================================================================================
// PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
ViewDataEnum.prototype._saveSettings = function(settings)
{
	this._settings = settings ;
}

//-------------------------------------------------------------------------------------------------------------
ViewDataEnum.prototype._evalSetting = function(setting, index)
{
	// Setting entry will either be: string, function, or array
	if (typeof setting === 'string')
		return setting ;

	if (typeof setting === 'function')
		return setting(this, index) ;

	if (typeof setting === 'object')
	{
		if (index >= setting.length)
			return '' ;
		return setting[index] ;
	}

	return '' ;
}

