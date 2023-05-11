/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tif.js
 * \brief     MOCK Singleton TIF over WebSocket
 *
 *
 * \details   Connects to the board (serving this content) via it's WebSocket port and provides an interface
 * 				for sending commands
 *
 */
"user strict" ;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
var Tif = (function() {
	var instance ;

	function _createInstance()
	{
		var tif = {
			_error : '',
			_debug : false,
			_msgId : 1,
			_reply : '',

			_data  : {},


			//==================================================================================================
			// PUBLIC
			//==================================================================================================

			//--------------------------------------------------------------------------------------------------
			/**
			 * send a new query.
			 * \param query Query object which must have the following fields:
			 * 	{
			 * 		cmd 	: the tif command to send
			 * 		onOk	: callback to call when the response is OK
			 * 		onError	: Callback for any error
			 * 	}
			 * Callbacks are called with a response object that contains the following:
			 *  {
			 *  	cmd		: copy of command sent
			 *  	error	: set to error string on error
			 *  	reply	: set to raw reply string (if received)
			 *  	vars	: object set to the reply var/value pairs (if received)
			 *  }
			 * \return true if query handled; false on any error
			 */
			send : function(query)
			{
				// immediate pseudo reply
				var reply = {
					cmd : query.cmd,
					error : '',
					reply : query.cmd,
					vars : {}
				} ;

				if (this._data[query.cmd])
				{
					for (var varName in this._data[query.cmd])
					{
						reply.vars[varName] = this._data[query.cmd][varName].next() ;
					}
				}

				if (query.onOk)
					query.onOk(reply) ;

				return true ;
			},

			//--------------------------------------------------------------------------------------------------
			error : function()
			{
				return this._error ;
			},

			//==================================================================================================
			// TEST INTERFACE
			//==================================================================================================

			//--------------------------------------------------------------------------------------------------
			// Set up test data for a command
			// data object is of the form:
			// {
			//	cmd : command string
			//	vars : {
			//		varname : [] array of data points
			//		..
			//	}
			// }
			setData : function(data)
			{
				this._data[data.cmd] = {} ;

				for (var varName in data.vars)
				{
					var buffer = new CircularBuffer(data.vars[varName].length) ;
					this._data[data.cmd][varName] = buffer ;

					for (var i=0; i < data.vars[varName].length; ++i)
					{
						buffer.push(data.vars[varName][i]) ;
					}
				}
			},

			//==================================================================================================
			// PRIVATE
			//==================================================================================================

			//--------------------------------------------------------------------------------------------------
			// run once on creation
			_init : function()
			{
			},

			_end : 0
		} ;

		tif._init() ;
		return tif ;
	}

	return {
		getInstance : function() {
			if (!instance)
			{
				instance = _createInstance() ;
			}
			return instance ;
		}
	};

})() ;
