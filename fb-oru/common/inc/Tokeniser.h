#ifndef _TOKENISER_H_
#define _TOKENISER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Tokeniser.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

/**
 * This class provides a string tokenisation capability that allows a standard string
 * to be returned as split into a number of string tokens according to the given delimiters.
 */
class Tokeniser
{
public:
    /**
     * Default delimiters, are space, tab, carriage return and line feed " /t/r/l".
     */
    static const std::string DELIMITERS;
    /**
     * Create a tokenised string using the default delimiters
     * @param str
     */
    explicit Tokeniser(const std::string& str);
    /**
     * Create a tokenised string using the provided delimiter string
     * @param str
     * @param delimiters
     */
    Tokeniser(const std::string& str, const std::string& delimiters);
    /**
     * Go to the next token string in our original string
     * @return true is there was a next token
     */
    bool nextToken();
    /**
     * Go to the next token string using the provided delimiter
     * @param delimiters string contains the delimiter to use
     * @return true if the next token was found.
     */
    bool nextToken(const std::string& delimiters);

    /**
     * Have we got another token available in the string
     * @return true if another token is available
     */
    bool hasNextToken() const ;

    /**
     * Have we got another token available in the string
     * @param delimiters string contains the delimiter to use
     * @return true if another token is available
     */
    bool hasNextToken(const std::string& delimiters) const ;

    /**
     * Returns a string reference to the current token
     * @return the current token
     */
    const std::string getToken() const;

    /**
     * Reset the tokeniser to the start of the original string.
     */
    void reset();

    /**
     * Get the delimiter character
     * @return
     */
    char getDelimiter() const;

    /**
     * Gets all of the remaining tokens and returns then in a list
     * @return list of token strings
     */
    std::vector<std::string> getTokens() ;


protected:
    /**
     * Copy of the original string to be tokenised
     */
    const std::string mString;

    size_t mOffset;
    std::string mToken;
    std::string mDelimiters;
    char mDelimiter;
};



#endif /* _TOKENISER_H_ */
