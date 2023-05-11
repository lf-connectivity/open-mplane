/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ViewDataEnumImgImg.js
 * \brief     View an ENUM Data object as a selected image
 *
 *
 * \details   Selects an image from a list depedning on the value of the ENUM Data
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
// images is a list of image locations, one for each enum coding
ViewDataEnumImg.prototype = new ViewDataEnum() ;
ViewDataEnumImg.prototype.constructor = ViewDataEnumImg ;
function ViewDataEnumImg(node$, data, images)
{
	this._init('ViewDataEnumImg', node$, data) ;

	var settings = {
		html : '<img src="">',
		attr : {
			'src' : images
		}
	} ;
	this._saveSettings(settings) ;
}

