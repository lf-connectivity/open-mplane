/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ErrorStr.hpp
 * \brief     Base class which handles setting/getting an error string
 *
 *
 * \details
 *
 */


#ifndef ERRORSTR_HPP_
#define ERRORSTR_HPP_

#include <string>

namespace Mplane {

/*!
 * \class  ErrorStr
 * \brief  Base class which handles setting/getting an error string
 */
class ErrorStr {
public:
	ErrorStr() : _mError("") {}
	virtual ~ErrorStr() {}

	/**
	 * Get the current error string (and clear it if clear flag set)
	 * @return error string
	 */
	virtual std::string getError(bool clear = true)
	{
		if (!clear)
			return checkError() ;

		return clearError() ;
	}

	/**
	 * Get the current error string (and clear it)
	 * @return error string
	 */
	virtual std::string clearError()
	{
		using std::swap ;
		std::string error ;
		swap(error, _mError) ;
		return error ;
	}

	/**
	 * Get the current error string (without clearing it)
	 * @return error string
	 */
	virtual std::string checkError()
	{
		return _mError ;
	}


protected:
	/**
	 * Add a string to the stored error string. If stored error string is not empty then a separator is first appended
	 * before adding this new string
	 * @param error
	 * @return always false - this allows you to set the error and return in one line
	 */
	virtual bool setError(const std::string& error, const std::string& separator = "\n")
	{
		if (!_mError.empty())
			_mError += separator ;
		_mError += error ;

		// return an error flag
		return false ;
	}

	/**
	 * Add a string to the stored error string. If stored error string is not empty then a newline is first appended
	 * before adding this new string.
	 * @param error	New error string
	 * @param returnError	String to return the error in
	 * @return always false - this allows you to set the error and return in one line
	 */
	virtual bool setError(const std::string& error, std::string& returnError, const std::string& separator = "\n")
	{
		// add to error string
		setError(error, separator) ;

		// Now set the return error with the full string
		returnError = getError() ;

		// return an error flag
		return false ;
	}

private:
	std::string _mError ;
} ;

}

#endif /* ERRORSTR_HPP_ */
