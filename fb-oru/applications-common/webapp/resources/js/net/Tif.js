/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tif.js
 * \brief     Singleton TIF over WebSocket
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

	function _createInstance(host, port)
	{
		const TIF_PROMPT = '->' ;
		const TIF_WEBSOCK_PORT = 49400 ;
		const MAX_BUFFER_LEN = 128 ;

		const STATE_INITIAL 	= 1 ;
		const STATE_CONNECTING 	= 2 ;
		const STATE_CLOSED	 	= 3 ;
		const STATE_RUNNING		= 4 ;
		const STATE_SENDING		= 5 ;

		const STATE_ERROR		= -666 ;

		var tif = {
			_websocket : {},
			_host  : 'localhost',
			_port  : TIF_WEBSOCK_PORT,
			_started : false,
			_state : STATE_INITIAL,
			_queries : [],
			_error : '',
			_debug : false,
			_msgId : 1,
			_reply : '',
			_statusCallback : null,


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
			 *
			 *  In the case where the command is actually a multi-cmd (i.e. multiple commands all together on a single
			 *  line joined by the "MULTICMD separator", then the following additional fields are filled in:
			 *
			 *   	multicmds : [] array of the commands sent, in the order they were sent
			 *   	multivars : {} hash of cmd/vars pairs (each vars entry is of the form described above):
			 *   		{
			 *   			'cmd1' : {}
			 *   			...
			 *   		}
			 *
			 * \return true if query handled; false on any error
			 */
			send : function(query)
			{
				// ensure connection is running
				this._start() ;
				
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:send START state='+this._state+' #queries='+this._queries.length) ;
				if (this._state == STATE_ERROR)
				{
					return false ;
				}
				else if (this._state == STATE_CLOSED)
				{
					this._error += '\nConnection closed' ;
					return false ;
				}

				// add to queue
				this._queries.push(query) ;

				// check for timeout waiting for response
				if ( (this._state == STATE_SENDING) && (this._queries.length >= MAX_BUFFER_LEN) )
				{
					console.log('['+Date.now()+'] ' +'ERROR: Waiting too long for command response, skipping to next...') ;
					this._changeState(STATE_RUNNING) ;
				}

				if (this._state == STATE_RUNNING)
					this._nextQuery() ;

				return true ;
			},

			//--------------------------------------------------------------------------------------------------
			error : function()
			{
				return this._error ;
			},

			//--------------------------------------------------------------------------------------------------
			enableDebug : function()
			{
				this._debug = true ;
			},

			//--------------------------------------------------------------------------------------------------
			setHost : function(host)
			{
				this._host = host ;
				return this._init() ;
			},

			//--------------------------------------------------------------------------------------------------
			setPort : function(port)
			{
				this._port = port ;
				return this._init() ;
			},

			//--------------------------------------------------------------------------------------------------
			start : function()
			{
				return this._start() ;
			},

			//--------------------------------------------------------------------------------------------------
			setStatusCallback : function(statusCallback)
			{
				this._statusCallback = statusCallback ;
				this._changedState() ;
			},

			//==================================================================================================
			// PRIVATE
			//==================================================================================================

			//--------------------------------------------------------------------------------------------------
			// run once on creation
			_init : function(host, port)
			{
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_init') ;
				this._host = window.location.hostname ;
				if (!this._host)
					this._host = 'localhost' ;

				// app can override the host name/ip
				if (host)
					this._host = host ;
				if (port)
					this._port = port ;

				this._state = STATE_INITIAL ;
				this._queries = [] ;
				this._error = '' ;
				this._msgId = 1 ;
				this._reply = '' ;
				this._statusCallback = null ;
				this._started = false ;
			},

			//--------------------------------------------------------------------------------------------------
			// start websocket connection
			_start : function()
			{
				if (this._started)
					return ;
				
				var wsURL = 'ws://' + this._host + ':' + this._port + '/' ;
				if (this._debug) console.log('URL: '+wsURL);
				try {
					this._websocket = new WebSocket(wsURL);
					this._started = true ;
				} catch (e) {
					this._state = STATE_ERROR ;
					this._error = 'Unable to connect' ;
					return ;
				}

				this._websocket.onopen = function(evt) { tif._onOpen(evt) };
				this._websocket.onclose = function(evt) { tif._onClose(evt) };
				this._websocket.onmessage = function(evt) { tif._onFirstPrompt(evt) };
				this._websocket.onerror = function(evt) { tif._onError(evt) };
			},

			//--------------------------------------------------------------------------------------------------
			// Called when WebSocket opens ok
			_onOpen : function(evt)
			{
				this._changeState(STATE_CONNECTING) ;
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_onOpen state='+this._state) ;
			},

			//--------------------------------------------------------------------------------------------------
			// Called when WebSocket closes
			_onClose : function(evt)
			{
				this._changeState(STATE_CLOSED) ;
				this._websocket.onmessage = function(evt) { };
				this._websocket.onerror = function(evt) { };
				this._queries = [] ;
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_onClose state='+this._state) ;
			},

			//--------------------------------------------------------------------------------------------------
			// Called on WebSocket error
			_onError : function(evt)
			{
				this._websocket.onmessage = function(evt) { };
				if (this._state == STATE_INITIAL)
					this._error = 'Unable to connect to WebSocket' ;
				else if (this._state == STATE_CONNECTING)
					this._error = 'No prompt from application' ;
				else
					this._error = evt.data ;

				// If we're processing a query then generate error event
				if (this._state == STATE_SENDING)
				{
					if (this._queries.length > 0)
					{
						var query = this._queries[0] ;
						if (query.onError)
						{
							var response = this._tifResponseError(query, this._error) ;
							query.onError(response) ;
						}
					}
				}

				this._queries = [] ;
				this._changeState(STATE_ERROR) ;
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_onError state='+this._state) ;
			},

			//--------------------------------------------------------------------------------------------------
			// Called with first response from the application - should be the prompt
			_onFirstPrompt : function(evt)
			{
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_onFirstPrompt START state='+this._state+' reply:'+evt.data) ;

				// keep going until got the prompt
				if (!this._gotPrompt(evt.data))
					return ;

				this._changeState(STATE_RUNNING) ;
				this._websocket.onmessage = function(evt) { tif._onMessage(evt) };

				// process first query
				this._nextQuery() ;
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_onFirstPrompt state='+this._state) ;
			},

			//--------------------------------------------------------------------------------------------------
			// Called with response to last query
			_onMessage : function(evt)
			{
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_onMessage START state='+this._state+' reply:'+evt.data+' #queries='+this._queries.length) ;

				this._reply += evt.data ;

				// keep going until got the prompt
				if (!this._gotPrompt(evt.data))
					return ;

				this._changeState(STATE_RUNNING) ;

				// get this query
				var query = this._queries.shift() ;
				var response = this._tifResponse(query, this._reply) ;
				if (response.vars.Status == 'OK')
				{
					if (query.onOk)
						query.onOk(response) ;
				}
				else
				{
					if (query.onError)
						query.onError(response) ;
				}


				// process next query
				this._nextQuery() ;
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_onMessage state='+this._state) ;
			},


			//--------------------------------------------------------------------------------------------------
			// Process the next entry in the list
			_nextQuery : function(evt)
			{
				this._reply = '' ;
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_nextQuery START state='+this._state+' #queries='+this._queries.length) ;
				if (this._queries.length == 0)
					return ;

				// send the command
				this._changeState(STATE_SENDING) ;
				var query = this._queries[0] ;
				var cmd = query.cmd ;
				if (this._debug)
				{
					cmd += ' # ' + this._msgId ;
				}
				++this._msgId ;
				this._websocket.send(cmd + '\n') ;
				if (this._debug) console.debug('['+Date.now()+'] ' +'TIF:_nextQuery END sent="' + cmd + '" state='+this._state) ;
			},

			//--------------------------------------------------------------------------------------------------
			// Create a TIF response object
			_tifResponse : function(query, reply)
			{
				var vars = Tif.processReply(reply) ;

				if (!reply)
					reply = '' ;

				var cmd = "" ;
				if (!query)
					console.debug('['+Date.now()+'] ' +"ERROR: No query when creating response") ;
				else
					cmd = query.cmd ;

				var response = {
					cmd 	: cmd,
					error	: '',
					reply	: reply,
					vars	: vars,

					// Optionally set if this is a multi-cmd response
					multicmds : [],
					multivars : {},
				} ;
				if (this._debug)
				{
					console.debug('['+Date.now()+'] ' +'CMD='+cmd) ;
					console.debug('['+Date.now()+'] ' +'REPLY='+reply) ;
				}


				// If this is a multi-command line
				if (reply.indexOf(Tif.MULTIREPLY_SEP) != -1)
				{
					// for multi-cmds we want to extract as much usable data as possible,
					// so only show error status if ALL replies are error
					response.vars.Status = 'OK' ;
					var okCount = 0 ;

					var cmds = cmd.split(Tif.MULTICMD_SEP) ;
					var replies = reply.split(Tif.MULTIREPLY_SEP) ;
					var len = cmds.length ;

					// should be the same!
					if (replies.length < len)
						len = replies.length ;

					for (var i=0; i <len; ++i)
					{
						var mcmd = cmds[i] ;
						response.multicmds.push(mcmd) ;
						response.multivars[mcmd] = Tif.processReply(replies[i]) ;
						if (response.multivars[mcmd].Status == 'OK')
							++okCount ;

						if (this._debug)
						{
							console.debug('['+Date.now()+'] ' +'MULTICMD='+mcmd) ;
							console.debug('['+Date.now()+'] ' +'MULTIREPLY='+replies[i]) ;
						}
					}

					// only mark all the replies as being in error if *all* of them do have an error. If one is OK then
					// pass the lot back up to be handled elsewhere
					if (okCount == 0)
						response.vars.Status = 'ERROR' ;
				}

				return response ;
			},

			//--------------------------------------------------------------------------------------------------
			// Create a TIF error response object
			_tifResponseError : function(query, error)
			{
				var response = this._tifResponse(query) ;
				response.error = this._error ;
				return response ;
			},

			//--------------------------------------------------------------------------------------------------
			// Does the reply contain the TIF prompt
			_gotPrompt : function(reply)
			{
				if (reply.indexOf(TIF_PROMPT) == -1)
					return false ;
				return true ;
			},

			//--------------------------------------------------------------------------------------------------
			// Change the state (and call callback if needed)
			_changeState : function(state)
			{
				this._state = state ;
				this._changedState() ;
			},

			//--------------------------------------------------------------------------------------------------
			// Change the state (and call callback if needed)
			_changedState : function()
			{
				if (!this._statusCallback)
					return ;

				if (this._state == STATE_ERROR)
					this._statusCallback('ERROR: '+this._error) ;
				if (this._state == STATE_CLOSED)
					this._statusCallback('CLOSED') ;
				if (this._state == STATE_RUNNING)
					this._statusCallback('OK') ;
				if (this._state == STATE_SENDING)
					this._statusCallback('OK') ;
			},

			_end : 0
		} ;

		tif._init(host, port) ;
		return tif ;
	}

	return {
		getInstance : function(host, port) {
			
			console.debug('Tif.getInstance') ;
			
			if (!instance)
			{
				instance = _createInstance(host, port) ;
			}
			return instance ;
		}
	};

})() ;


//=============================================================================================================
//PUBLIC STATIC
//=============================================================================================================
Tif.MULTICMD_SEP = ';' ;
Tif.MULTIREPLY_SEP = '%~%' ;

//--------------------------------------------------------------------------------------------------
// Process the response string into var/value pairs
Tif.processReply = function(reply)
{
	if (!reply)
		return {} ;

	var vars = {} ;
	var lines = reply.split(/[\r\n]+/) ;
	for (var l=0; l < lines.length; ++l)
	{
		// process line by line
		var line = lines[l] ;

		// Need to pre-process to convert strings (which may contain spaces) into a single
		// word to make var/value pairs easier to extract.
		// Run the line through a string pre-processor
		line = Tif._stringPreProcess(line) ;

		// Can now split line into fields
		var fields = line.split(' ') ;

		for (var f=0; f < fields.length; ++f)
		{
			var field = fields[f] ;
			var pos = field.indexOf('=') ;
			if (pos == -1)
				continue ;

			var v = field.substr(0, pos) ;
			var val = Tif._stringPostProcess(field.substr(pos+1)) ;
			vars[v] = val ;
		}
	}
	return vars ;
}



//-------------------------------------------------------------------------------------------------------------
// Get the response string for the specified varName; or null if doesn't exist
Tif.getResponseVar = function(response, varName)
{
	if (!response.vars.hasOwnProperty(varName))
		return null ;

	return response.vars[varName] ;
}

//-------------------------------------------------------------------------------------------------------------
// If varName response string exists, convert it to integer and set the varName attribute on the target object
Tif.setResponseVarInt = function(response, varName, target)
{
	var varStr = Tif.getResponseVar(response, varName) ;
	if (varStr === null)
		return ;

	target[varName] = parseInt(varStr) ;
}

//=============================================================================================================
//PRIVATE STATIC
//=============================================================================================================
Tif._SPACE_REPLACEMENT = '@@@' ;
//--------------------------------------------------------------------------------------------------
Tif._stringPreProcess = function(str)
{
	// start by counting the number of " - if they are not even then we can't attempt this
	var numQuotes = (str.split('"').length - 1) ;
	if (numQuotes == 0)
		return str ;
	if (numQuotes % 2 == 1)
		return str ;

	// build up a new string that removes the quotes and replaces any space inside the quoted portion with
	// the marker text
	var pstr = '' ;
	var strlen = str.length ;
	var endPos = -1 ;
	var startPos = str.indexOf('"') ;
	while (startPos >= 0)
	{
		pstr += str.substr(endPos+1, startPos - endPos - 1) ;

		endPos = str.indexOf('"', startPos+1) ;
		var substr = str.substr(startPos+1, endPos - startPos - 1) ;
		pstr += substr.replace(/ /g, Tif._SPACE_REPLACEMENT) ;

		startPos = str.indexOf('"', endPos+1) ;
	}

	return pstr ;
}

//--------------------------------------------------------------------------------------------------
Tif._stringPostProcess = function(str)
{
	return str.replace(new RegExp(Tif._SPACE_REPLACEMENT, 'g'), ' ') ;
}
