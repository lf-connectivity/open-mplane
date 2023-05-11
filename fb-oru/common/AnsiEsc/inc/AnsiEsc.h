/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AnsiEsc.h
 * \brief     ANSI escape sequences
 *
 *
 * \details   Creates correct ANSI escape sequences
 *
 */


#ifndef ANSIESC_H_
#define ANSIESC_H_

#include <string>

namespace Mplane {

/*!
 * \class AnsiEsc
 */
class AnsiEsc {
public:
	enum class Colour {
		NONE,
		BLACK,
		DARK_GREY,
		DARK_RED,
		RED,
		DARK_GREEN,
		GREEN,
		DARK_YELLOW,
		YELLOW,
		DARK_BLUE,
		BLUE,
		DARK_MAGENTA,
		MAGENTA,
		DARK_CYAN,
		CYAN,
		LIGHT_GREY,
		WHITE,
	};

	/**
	 * Convert colour to a colour name string
	 * @param colour
	 * @return string name of colour
	 */
	static std::string colourName(Colour colour) ;

	/**
	 * Convert colour name string into a colour
	 * @param colourName
	 * @return colour (or NONE if not found)
	 */
	static Colour colour(const std::string& colourName) ;

	/**
	 * Create the ANSI escape sequence to set the foreground (and optionally background) colours
	 * @param foreground
	 * @param background
	 * @return ANSI escape sequence string
	 */
	static std::string setColour(Colour foreground, Colour background) ;

	/**
	 * Create the ANSI escape sequence to set the foreground colour
	 * @param foregroundName
	 * @return ANSI escape sequence string
	 */
	static std::string setColour(Colour foreground) ;

	/**
	 * Create the ANSI escape sequence to set the foreground (and optionally background) colours
	 * @param foregroundName
	 * @param backgroundName
	 * @return ANSI escape sequence string
	 */
	static std::string setColour(const std::string& foregroundName, const std::string& backgroundName) ;

	/**
	 * Create the ANSI escape sequence to set the foreground colour
	 * @param foreground
	 * @return ANSI escape sequence string
	 */
	static std::string setColour(const std::string& foregroundName) ;

	/**
	 * Create the ANSI escape sequence to reset the colours
	 * @return ANSI escape sequence string
	 */
	static std::string resetColour() ;

} ;

}

#endif /* ANSIESC_H_ */
