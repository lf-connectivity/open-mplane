#ifndef _COMM_POWER_H_
#define _COMM_POWER_H_

#include <string>
#include <iostream>
#include "ComparisonOperators.hpp"

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Power.h
 * \brief     A file to contain general purpose radio power wrapper
 *
 *
 * \details   This file defines general purpose radio power wrapper data
 *
 */



namespace Mplane
{

/*! \brief A general purpose radio power class.
 *
 * The Power class acts as a simple data type wrapper class for radio
 * power data.
 *
 * Radio power is in base units of dBm.
 *
 * To ensure no data loss, the power needs to be held internal as a float.
 *
 * The class provides a number of getter and setter functions that allow
 * the internal power data to be represented in other unit types, as defined
 * by the Power::Unit enumeration. eg. tenths of dBm, hundredths of dBm.
 *
 * All the basic arithmetic and comparative operators have also been implemented
 * to allow the Power objects to be used in general maths and logic testing.
 */
class Power : public ComparisonOperators<Power>
{
    friend class PowerTestCase;

public:

    /**
     * Enumeration of power units supported by the Power data type
     * getter and setter interface. The variable is self documenting.
     */
    enum Unit
    {
        dBm,          //!< dBm raw value
        dB,          //!< dB value
        dBFS,          //!< dB full scale
        TdBm,         //!< TdBm 1/10s of dBm
        HdBm,        //!< HdBm 1/100s of dBm
        KdBm,       //!< KdBm 1/1000s of dBm

        mW,			//!< milli Watts
        W,			//!< Watts
    };

    /**
     * @ brief Method to convert Power::Unit type to a string.
     *
     * This Method can be used to convert the power unit type to a
     * simple string constant so that it can be used in debug trace.
     *
     * @code
     * Power p1(20.0);
     * logDebugNormal("Power is %f %s", p1.get(Power::dBm), p1.unit2Str(Power::dBm) );
     * @endcode
     *
     * @param unit enumerated unit value.
     * @return a string representing the enumeration value
     */
    static const char* unit2Str(Power::Unit unit);

    /**
     * @ brief Method to convert a string into a Power::Unit type
     *
     * @param a string representing the enumeration value
     * @return value enumerated unit value.
     */
    static Power::Unit str2unit(const std::string& units) ;

    /**
     * Simple power object constructor.
     */
    Power();

    /**
     * Power object constructor that allows the initial power value to be
     * set using a floating point value with a given units scale
     *
     * @code
     * Power pdbm1(21.0, Power::dBm);
     * Power pdbm2(22.0, Power::TdBm);   // = 2.2dBm
     * Power pdbm3(25.0, Power::HdBm);   // = 0.25dBm
     * Power pdbm4(1234.0, Power::KdBm); // = 1.234dBm
     * @endcode
     *
     * @param power assigned to the object
     * @param unit default to dBm but can be overridden to any Power::Unit type
     */
    Power(float power, Power::Unit unit = Power::dBm);

    /**
     * Method that allows the power of the object to be set using a floating
     * point value.
     * (the equals = operator would normally be used where no unit scaling is required).
     *
     * @code
     * Power p1;
     * p1.set( 100.2, Power::dBm );
     * @endcode
     *
     * @param power
     * @param unit default to dBm but can be overridden to any Power::Unit type
     */
    void set(float power, Power::Unit unit);

    /***
     * Method for setting the power in dBm. This method has been optimised as the fastest means of setting a Power object
     * for dB use (lazily implements the Watts power value setting)
     * @param power
     */
    void set(float power);

    /**
     * Method used to set the power value using a string, useful when setting powers
     * from parsed data.
     * @param power
     * @param unit
     */
    void set(const std::string& power, Power::Unit unit = Power::dBm);


    /**
     * Method that allows the power of the object to be set using a floating
     * point value in Watts.
     *
     * @code
     * Power p1;
     * p1.setWatts( 40.0 );
     * @endcode
     *
     * @param power in Watts
     */
    void setWatts(float power);

    /**
     * Method used to get the power value as a floating point value, by
     * default in dBm.
     * The unit parameter may be used to change the unit type returned.
     *
     * @code
     * Power p1(34.5);
     * float power_in_dBm = p1.get(); // = 34.5
     * float power_in_HdBm = p1.get(Power::HdBm); // = 3450.0
     * @endcode
     *
     * @param power
     * @param unit default to dBm but can be overridden to any Power::Unit type
     */
    float get(Power::Unit unit = Power::dBm) const ;

    /**
     * Method used to get the power value as a floating point value, in Watts
     *
     * @code
     * Power p1(34.5);
     * float power_in_watts = p1.getWatts();
     * @endcode
     *
     */
    float getWatts() const ;

    /**
     * Method used to retrieve the current power value as a signed integer,
     * by default in dBm.
     * The unit parameter may be used to change the unit type returned.
     *
     * @code
     * Power pconst(12.36);   // = 12.36dBm
     * Power pconst2(-43.46); // = -43.46dBm
     * int power_TdBm = pconst.getUint(Power::TdBm); // = 124
     * int power_HdBm = pconst.getUint(Power::HdBm); // = 1236
     * int power_TdBm2 = pconst2.getUint(Power::TdBm); // = -435
     * int power_HdBm2 = pconst2.getUint(Power::HdBm); // = -4346
     * @endcode
     *
     * @param unit default to dBm but can be overridden to any Power::Unit type
     *
     * @return power in the selected units
     */
    int getInt(Power::Unit unit = Power::dBm) const;

    /**
     * Assignment operator to allow the value of a Power object to be set by another.
     *
     * @code
     * Power p1;
     * Power p2 = p1;
     * @endcode
     *
     * @param rhs Power object reference
     *
     * @return modified Power object
     */
    Power& operator=(const Power& rhs);

    /**
     * Assignment operator to allow the value of a Power object to be set by a
     * floating point value.
     *
     * @code
     * Power p1;
     * p1 = 50.2;
     * p1 = -8.7;
     * @endcode
     *
     * @param power in dBm
     *
     * @return modified Power object
     */
    Power operator=(const float power);

    /**
     * Assignment operator to allow the value of a Power object to be set by a
     * signed integer.
     *
     * @code
     * Power p1;
     * p1 = 50;
     * p1 = -8;
     * @endcode
     *
     * @param power in dBm
     *
     * @return modified Power object
     */
    Power operator=(const int power);

    /**
     * Operator overload to allow Power objects to be added together.
     *
     * @code
     * Power p1=20.0;
     * Power p2=10.0;
     * Power p3 = p1 + p2; // result 30.0
     * @endcode
     *
     * @param rhs an existing Power object reference.
     *
     * @return the modified left hand side reference
     */
    Power operator+(const Power& rhs) const;

    /**
     * Operator overload to allow a floating point value to be added to a Power object.
     *
     * @code
     * Power p1;
     * Power p2=10.0;
     * p1 = p2 + 20.1; // result 30.1
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator+(const float power) const;

    /**
     * Operator overload to allow a signed integer to be added to a Power object.
     *
     * @code
     * Power p1;
     * Power p2=10.0;
     * p1 = p2 + 20; // result 30.0
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator+(const int power) const;

    /**
     * Operator overload to allow a Power object to be added to an existing power.
     *
     * @code
     * Power p1=20;
     * Power p2=33;
     * p1 += p2; // result 53.0
     * @endcode
     *
     * @param rhs
     *
     * @return reference to the modified Power object
     */
    Power operator+=(const Power& rhs);

    /**
     * Operator overload to allow a floating point value to be added to an
     * existing Power object.
     *
     * @code
     * Power p1=20;
     * p1 += 22.5; // result 42.5
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator+=(const float power);

    /**
     * Operator overload to allow a signed int to be added to an existing Power object.
     *
     * @code
     * Power p1=21;
     * p1 += 22; // result 43.0
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator+=(const int power);

    /**
     * Operator overload to allow Power objects to be multiplied together.
     *
     * @code
     * Power p1=20;
     * Power p2=10;
     * Power p3 = p1 * p2; // result 200
     * @endcode
     *
     * @param rhs an existing Power object reference.
     *
     * @return the modified left hand side reference
     */
    Power operator*(const Power& rhs) const;

    /**
     * Operator overload to allow a floating point value to be multiplied by a
     * Power object.
     *
     * @code
     * Power p1;
     * Power p2=100;
     * p1 = p2 * 10.0; // result 1000
     * @endcode
     *
     * @param power power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator*(const float power) const;

    /**
     * Operator overload to allow a signed integer to be multiplied by a Power object.
     *
     * @code
     * Power p1;
     * Power p2=100;
     * p1 = p2 * 3; // result 300
     * @endcode
     *
     * @param power power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator*(const int power) const;

    /**
     * Operator overload to allow a Power object to be multiplied by an existing power.
     *
     * @code
     * Power p1=20;
     * Power p2=10;
     * p1 *= p2; // result 200
     * @endcode
     *
     * @param rhs
     *
     * @return reference to the modified Power object
     */
    Power operator*=(const Power& rhs);

    /**
     * Operator overload to allow a floating point value to be multiplied by an
     * existing Power object.
     *
     * @code
     * Power p1=20;
     * p1 *= 10.1; // result 202
     * @endcode
     *
     * @param power in dBm
     *
     * @return the modified left hand side reference
     */
    Power operator*=(const float power);

    /**
     * Operator overload to allow a signed int to be multiplied by an existing Power object.
     *
     * @code
     * Power p1=20;
     * p1 *= 11; // result 220
     * @endcode
     *
     * @param power in dBm
     *
     * @return the modified left hand side reference
     */
    Power operator*=(const int power);

    /**
     * Operator overload to allow Power objects to be divided together.
     *
     * @code
     * Power p1=20;
     * Power p2=10;
     * Power p3 = p1 / p2; // result 2
     * @endcode
     *
     * @param rhs an existing Power object reference.
     *
     * @return the modified left hand side reference
     */
    Power operator/(const Power& rhs) const;

    /**
     * Operator overload to allow a floating point value to be divided by a
     * Power object.
     *
     * @code
     * Power p1;
     * Power p2=120
     * p1 = p2 / 1.5; // result 80
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator/(const float power) const;

    /**
     * Operator overload to allow a signed integer to be divided by a Power object.
     *
     * @code
     * Power p1;
     * Power p2=100
     * p1 = p2 / 10; // result 10
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator/(const int power) const;

    /**
     * Operator overload to allow a Power object to be divided by an existing power.
     *
     * @code
     * Power p1=200;
     * Power p2=10;
     * p1 /= p2; // result 20
     * @endcode
     *
     * @param rhs
     *
     * @return reference to the modified Power object
     */
    Power operator/=(const Power& rhs);

    /**
     * Operator overload to allow a floating point value to divided by an
     * existing Power object.
     *
     * @code
     * Power p1=200;
     * p1 /= 2.5; // result 80
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator/=(const float power);

    /**
     * Operator overload to allow a signed int to divided by an existing Power object.
     *
     * @code
     * Power p1=200;
     * p1 /= 10; // result 20
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator/=(const int power);

    /**
     * Operator overload to allow a Power object to be subtracted from another Power object.
     *
     * @code
     * Power p1=20.0;
     * Power p2=10.0;
     * Power p3 = p1 - p2; // result 10.0
     * @endcode
     *
     * @param rhs Power object
     *
     * @return modified Power object
     */
    Power operator-(const Power& rhs) const;

    /**
     * Operator overload to allow a floating point value to be subtracted from
     * another Power object.
     *
     * @code
     * Power p1;
     * Power p2=10.0;
     * p1 = 20.1 - p2; // result 10.1
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator-(const float power) const;

    /**
     * Operator overload to allow a signed integer to be subtracted from another Power object.
     *
     * @code
     * Power p1;
     * Power p2=10.0;
     * p1 = 20 - p2; // result 10.0
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator-(const int power) const;

    /**
     * Operator overload to allow a Power object to be subtracted from an existing Power.
     *
     * @code
     * Power f1=220;
     * Power f2=100;
     * f1 -= f2; // result 120
     * @endcode
     *
     * @param rhs
     *
     * @return modified Power object
     */
    Power operator-=(const Power& rhs);

    /**
     * Operator overload to allow a floating point value to be subtracted from an existing Power.
     *
     * @code
     * Power f1=210;
     * f1 -= 100; // result 110
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator-=(const float power);

    /**
     * Operator overload to allow a signed integer to be subtracted from an existing Power.
     *
     * @code
     * Power f1=210;
     * f1 -= 100; // result 110
     * @endcode
     *
     * @param power in dBm
     *
     * @return reference to the modified Power object
     */
    Power operator-=(const int power);


    /**
     * Equality operator - provided for ComparisonOperators<>
     * @param rhs
     * @return return true if frequencies equal
     */
    virtual bool operator==(const Power& rhs) const ;

    /**
     * Less than operator - provided for ComparisonOperators<>
     * @param rhs
     * @return return true if this < rhs frequency
     */
    virtual bool operator<(const Power& rhs) const ;


protected:

    /**
     * Converts power from dBm into Watts, returning the result as a floating
     * point value.
     *
     * The basic power equation is:
     *   dBm = 10 log10(mW)
     *
     * Therefore, for a given power in dBm (D) the conversion equation is:
     *   W = exp10(D/10) / 1000
     *
     * @param powerdBm in dBm
     *
     * @return power in Watts, as a floating point value
     */
    float convertdBmToWatts(float powerdBm) const;

    /**
     * Converts power from Watts into dBm, returning the result as a floating
     * point value.
     *
     * The basic power equation is:
     *   dBm = 10 log10(mW)
     *
     * Therefore, for a given power in Watts (W) the conversion equation is:
     *   dBm = 10 log10(1000*W)
     *
     * @param powerWatts in Watts
     *
     * @return power in dBm, as a floating point value
     */
    float convertWattsTodBm(float powerWatts) const;

private:
    /**
     * Internal utility that updates the power in watts based on the current dB power (and also sets the flag)
     * NOTE: Although this is flagged as const it DOES change the object. It actually sets the power in watts + the corresponding
     * flag. Having these data members mutable and this method as const means that the public interface is logically const for getting
     * the values, while internally the watts power is lazily evaluated because most of the time we don't need it
     */
    void setPowerWatts() const ;

protected:
    float mPower_dBm;
    mutable float mPower_watts;
    mutable bool mWattsSet ;
};

} /* namespace Mplane */

/**
 * @brief Make Power a printable object for debug
 * @param out ostream
 * @param power Object to print
 * @return ostream
 */
inline std::ostream& operator<<(std::ostream& out, const Mplane::Power& power)
{
	out << power.get() << "dB" ;
	return out ;
}

#endif /* _COMM_POWER_H_ */
