#ifndef _DATAVARIANTCLASS_H_
#define _DATAVARIANTCLASS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DataVariantClass.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#include <string>
#include <vector>
#include <memory>

#include "DataVariantType.h"
#include "DataVariantBase.h"

namespace Mplane
{

//----------------------------------------------------------------------------------------------------------------------
/**
 * The Mplane::DataVariant class is derived from Mplane::DataVariantBase and adds support for vectors of Mplane::DataVariant
 * objects
 */
class DataVariant : public DataVariantBase
{
public:
	typedef DataVariantBase super ;

    // used in unit testing
    friend class DataVariantTestCase;

	virtual ~DataVariant() ;

    /**
     * Is this a vector value?
     * @return true if vector
     */
    bool isVector() const ;

    /**
     * Returns number of entries in the vector (0 if not a vector type or empty)
     */
    unsigned size() const ;

    /**
     * Has the value been initialised
     * @return true if the value has been initialised
     */
    virtual bool isSet() const override ;


    /**
     * Returns a list of name / DataVariant pairs (even if DataVariant is not a vector)
     */
    std::vector< std::pair<std::string, DataVariant> > getList() const ;

    /**
     * Set the value of a variant from another
     * @param rhs
     */
    virtual void set(const DataVariant & rhs) ;

    /**
     * Set the value of a variant from another
     * @param rhs
     */
    virtual void set(const DataVariant* rhs);

    /**
     * Set the value of a variant from another
     * @param rhs
     */
    virtual void set(const std::shared_ptr<DataVariant>& rhs);

    /**
     * Set vector entry value using string
     * @param index	Index into vector
     * @param value
     * @param name	Optional name string. Sets the displayed name of this vector element.
     */
    virtual void set(unsigned index, const std::string& value, const std::string& name = "");

    /**
     * Set the vector entry value of the the variant to the integer value. If the variant
     * is type Float, the value is cast to a float internally.
     *
     * @param index	Index into vector
     * @param value
     * @param name	Optional name string. Sets the displayed name of this vector element.
     */
    virtual void set( unsigned index, int value, const std::string& name = "" );
    /**
     * Set the vector entry value of the variant to the float value. If the variant is
     * type Int, the value is cast to an integer internally.
     *
     * @param index	Index into vector
     * @param value
     * @param name	Optional name string. Sets the displayed name of this vector element.
     */
    virtual void set( unsigned index, float value, const std::string& name = "" );
    /**
     * Set the value of the variant to the complex value. If the variant is
     * type Int or Float, then just the real part is used.
     *
     * @param value
     */
    virtual void set( unsigned index, const std::complex<float>& value, const std::string& name = "" );

    /**
     * Set the name of the vector entry indexed by the specified index.
     *
     * @param index	Index into vector
     * @param name	Sets the displayed name of this vector element.
     */
    virtual void setName( unsigned index, const std::string& name );

    /**
     * Convert list of variable to a list of strings. Any optional variables will be skipped if they are empty strings
     * @return list of variable strings
     */
    std::vector<std::string> toStrings() const ;

    /**
     * Convert list of variable to a list of strings. Shows all variables including empty optionals
     * @return list of variable strings
     */
    std::vector<std::string> toStringsFull() const ;



    // DataVariantBase Interface

    /**
     * Create an unnamed empty data variant object with no type or valid data, this type
     * is usually used to make copies of data variants.
     */
    DataVariant();
    /**
     * Create a named data variant.
     *
     * If the name contains an equals sign then the string on the right hand side will be
     * used to set the value and type of the variant. See the set method for details of the value.
     *
     * @param name
     */
    explicit DataVariant(const std::string& name );
    /**
     * Create a named data variant using a named typed, eg, INT, FLOAT, STRING or ENUM.
     *
     * If the type is not valid the type will default to type INT.
     *
     * @param name
     * @param type
     */
    DataVariant(const std::string& name, const std::string& type );
    /**
     * Create a named data variant using a named typed
     *
     * If the type is not valid the type will default to type INT.
     *
     * @param type
     * @param name
     * @param value	Optional default value
     */
    DataVariant(const DataVariantType::Type& type, const std::string& name, const std::string& value = "" );

    /**
     * Copy constructor used to create an instance of a data variant based upon an existing
     * variant.
     *
     * @param value variant to copy
     */
    DataVariant(const DataVariant &value );
    /**
     * Copy constructor used to create an instance of a data variant based upon an existing
     * base variant.
     *
     * @param value variant to copy
     */
    explicit DataVariant(const DataVariantBase &value );

    /**
     * Equals operator used to assign the value of a variant from another
     * @param rhs
     * @return a reference to the obect.
     */
    virtual DataVariant& operator=(const DataVariant & rhs);

    /**
     * Set value using string
     * @param value
     */
    virtual void set(const std::string& value);

    /**
     * Set the value of the the variant to the integer value. If the variant
     * is type Float, the value is cast to a float internally.
     *
     *
     * @param value
     */
    virtual void set( int value );
    /**
     * Set the value of the variant to the float value. If the variant is
     * type Int, the value is cast to an integer internally.
     *
     * @param value
     */
    virtual void set( float value );
    /**
     * Set the value of the variant to the complex value. If the variant is
     * type Int or Float, then just the real part is used.
     *
     * @param value
     */
    virtual void set( const std::complex<float>& value );


    /**
     * Method used to return the data variant name and its value as a pair, separated with
     * an equals sign.
     *
     * @return string in the form "name=value"
     */
    virtual std::string getNameValuePair() const;

    /**
     * Method used to return the data variant name and its value as a pair, separated with
     * an equals sign. If the variable is optional and an empty string then returns an empty string
     *
     * @return string in the form "name=value"; or "" for empty optional variable
     */
    virtual std::string getNameValuePairOptional() const;

    /**
     * Get the DataVariant type as a string, ie, INT, FLOAT, HEXINT, STRING, ENUM
     * @return variant type as a string
     */
    virtual const std::string getTypeStr() const;

    /**
     * For scalars clears the value; for vectors clears out the vector
     */
    virtual void clear() ;

    /**
     * Clears out the vector contents
     */
    virtual void clearVector() ;

    /**
     * Set the units string
     * @param units string representing the value units (e.g. "dB", "W", "kHz" etc)
     */
    void setUnits(const std::string& units) ;


    /**
     * Sets limits for either an INT or FLOAT type; does nothing for any other type
     * @param limitsStr	String in the format "min..max/step"
     * @return true if set ok (or type not INT/FLOAT); false on error
     */
    virtual bool setLimits(const std::string& limitsStr) ;

    /**
     * Set limits from min/max/step strings
     * @param minStr
     * @param maxStr
     * @param stepStr
     * @return true if set ok (or type not INT/FLOAT); false on error
     */
    virtual bool setLimits(const std::string& minStr, const std::string& maxStr, const std::string& stepStr) ;

    /**
     * Check the INT/FLOAT type current value against any set limits. For vectors ensures *ALL* entries are within limits
     * @return false if INT/FLOAT value does not match limits; true otherwise
     */
    virtual bool checkLimits(std::string& error) ;
    virtual bool checkLimits() ;


public:
    /**
     * Looks at a string to see if it's of the form:
     * 	name[XX]
     * If so it sets the index to the XX value, and sets the base string to the 'name' part
     *
     * @param indexedStr	String containing the indexed expression
     * @param index			Set to index value if indexed
     * @param baseStr		Set to the base name of the indexed expression if indexed
     * @return true if this is an indexed expression
     */
    static bool getIndex(const std::string& indexedStr, unsigned& index, std::string& baseStr) ;


private:
    /**
     * Use the vector index to get the DataVariant from the vector. If index is larger than current vector
     * size then the vector is expanded. If this DataVariant is not a vector then returns this
     * @param index
     * @return DataVariant at this index
     */
    DataVariantBase& getIndexedValue(unsigned index) ;

    /**
     * Use the vector index to get the name from the vector. If index is larger than current vector
     * size then the vector is expanded. If this DataVariant is not a vector then returns this name
     * @param index
     * @return name at this index
     */
    std::string& getIndexedName(unsigned index) ;

private:
    bool mSet ;

	/**
	 * Is this a vector
	 */
	bool mIsVector ;

	/**
	 * Store the values and names
	 */

	std::vector<DataVariantBase*> 	mValues ;
	std::vector<std::string> 		mNames ;

	typedef std::vector<DataVariantBase*>::iterator ValuesIter ;
	typedef std::vector<DataVariantBase*>::const_iterator ValuesConstIter ;
	typedef std::vector<std::string>::iterator NamesIter ;
	typedef std::vector<std::string>::const_iterator NamesConstIter ;
};



}

#endif /* _DATAVARIANTCLASS_H_ */
