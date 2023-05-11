#ifndef _DATAVARIANTLIST_H_
#define _DATAVARIANTLIST_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantList.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <string>
#include <vector>

#include "DataVariantClass.h"

namespace Mplane
{

//----------------------------------------------------------------------------------------------------------------------
/**
 * The Mplane::DataVariantList class is used to manage lists of Mplane::DataVariant objects
 */
class DataVariantList
{
public:

    DataVariantList();
    explicit DataVariantList( const char *fieldList );

    ~DataVariantList();

    /**
     * Add any variables from the fieldList that aren't already in the list
     * @param fieldList
     */
    void addFields( const char *fieldList );

    /**
     * Add the DataVariant to the list
     * @param variant
     * @return true if not already in list
     */
    bool add( DataVariant* variant );

    /**
     * Find the DataVariant with matching name
     * @param name
     * @return pointer to the DataVariant or NULL
     */
    DataVariant* find( const std::string& name);

    /**
     * Print out the list
     */
    void show();

    /**
     * Convert list of variable to string. Any optional variables will be skipped if they are empty strings
     * @param separator Optional separator string used between pairs
     * @return string representation of the list of variables
     */
    std::string toString(const std::string& separator=" ");

    /**
     * Convert list of variable to string. Shows all variables including empty optionals
     * @param separator Optional separator string used between pairs
     * @return string representation of the list of variables
     */
    std::string toStringFull(const std::string& separator=" ");

    /**
     * Convert list of variable to a list of strings. Any optional variables will be skipped if they are empty strings
     * @return list of variable strings
     */
    std::vector<std::string> toStrings();

    /**
     * Convert list of variable to a list of strings. Shows all variables including empty optionals
     * @return list of variable strings
     */
    std::vector<std::string> toStringsFull();

    /**
     * Convert list of variable to a list of variable/value pairs. Any optional variables will be skipped if they are empty strings
     * @return list of variable/value pairs
     */
    typedef std::pair<std::string, std::string> VarVarPair ;
    std::vector< VarVarPair > toVarVals();
    typedef std::vector< VarVarPair >::const_iterator VarValListConstIter ;

    /**
     * Get list of variables and their types
     * @param separator Optional separator string used between pairs
     * @param showValue Optional flag - if set also shows the current variable value
     * @return string containing variable/type pairs
     */
    std::string varlist(const std::string& separator=",", bool showValue = false);

    /**
     * Create a new DataVariant and add it to the list
     * @param name 	variable name
     * @param type	type of DataVariant
     * @return true if added ok (no duplicates)
     */
    bool add( const std::string& name, const DataVariantType::Type& type);

    /**
     * Create the variables in the list parsing the string to determine the variable name, type, and any default value
     * @param valuePairs	String containing variable=value pairs
     * @return true if processed with no errors
     */
    bool set( std::string valuePairs);

    /**
     * Checks to see if all the variables in the list have been set to some value. Sets an error message otherwise
     * @return true if all variables set
     */
    bool allSet() ;

    /**
     * Get any error as a string
     * @return error string if error
     */
    std::string getError();

    /**
     * Is the list empty
     * @return true if empty list
     */
    bool empty() const ;

    /**
     * Uses the string fieldList as if it were specified in the constructor, and checks to see if this list contains a
     * superset of the list contained in the fieldList
     * @param fieldList
     * @return true if this is a superset
     */
    bool superset(const std::string& fieldList) const ;

    /**
     *
     * Checks to see if this list contains a superset of the list contained in the other DataVariantList
     * @param other
     * @return true if this is a superset
     */
    bool superset(const DataVariantList& other) const ;

    /**
     * Uses the string fieldList as if it were specified in the constructor, and checks to see if this list contains a
     * subset of the list contained in the fieldList
     * @param fieldList
     * @return true if this is a subset
     */
    bool subset(const std::string& fieldList) const ;

    /**
     * Checks to see if this list contains a subset of the list contained in the other DataVariantList
     * @param other
     * @return true if this is a subset
     */
    bool subset(const DataVariantList& other) const ;

    /**
     * Reset the entries in the list. For scalar DataVariants this clears the value; for vector DataVariants this empties
     * the contents
     */
    void clearValues() ;

    /**
     * Check the INT/FLOAT type current value against any set limits. For vectors ensures *ALL* entries are within limits
     * @return false if INT/FLOAT value does not match limits; true otherwise
     */
    bool checkLimits(std::string& error) ;
    bool checkLimits() ;

    /**
     * Get a list copying the current DataVariants
     * @return vector of DataVariant values
     */
    std::vector<DataVariant> getList() const ;


private:
    std::vector< DataVariant* >::iterator findIter(const std::string &name);
    std::vector< DataVariant*>::const_iterator findIter(const std::string &name) const ;

protected:
    std::string errorVar;
    DataVariant mNullData ;		//<! Used as a sentinel when data of a particular name is not found
    std::vector< DataVariant* > list;
};


}

#endif /* _DATAVARIANTLIST_H_ */
