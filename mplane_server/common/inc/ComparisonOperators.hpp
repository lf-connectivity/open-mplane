#ifndef _COMM_COMPOP_HPP_
#define _COMM_COMPOP_HPP_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ComparisonOperators.hpp
 * \brief     Template comparison operators provider
 *
 *
 * \details   Decorates a class with all the usual comparison operators.
 *
 * The inheriting class just needs to provide the pure virtual methods
 * operator== and operator< in order to have this template provide all of the
 * other operators.
 *
 * As an example:
 *
 * @code
 * Class Myclass : public ComparisonOperators<Myclass> {
 *
 *         Myclass(unsigned data) : mData(data) {}
 *
 *         // provide the equality operator
 *         virtual bool operator==(const Myclass& rhs) { return mData ==
 * rhs.mData; }
 *
 *         // provide the less than operator
 *         virtual bool operator<(const Myclass& rhs) { return mData <
 * rhs.mData; }
 *
 *         // ComparisonOperators provides !=, <=, >=, >
 *
 * private:
 *         unsigned mData ;
 * };
 * @endcode
 */

namespace Mplane {

template <typename TClass>
class ComparisonOperators {
 public:
  virtual ~ComparisonOperators<TClass>() {}

  /**
   * Comparison operator to allow an object value to be compared equivalent to
   * another object. Must be overridden by derived object
   *
   * @param rhs object reference
   * @return true if equal, otherwise false;
   */
  virtual bool operator==(const TClass& rhs) const = 0;

  /**
   * Comparison operator to allow an object value to be compared to see if it is
   * less than the value of another object. Must be overridden by derived object
   *
   * @param  rhs object reference
   * @return true if less, otherwise false
   */
  virtual bool operator<(const TClass& rhs) const = 0;

  /**
   * Comparison operator to allow an object value to be compared not equivalent
   * to another object.
   *
   * @code
   * Object f1=1000;
   * const Object f2=2000;
   * if( f1 != f2 )
   * {
   *     // frequency are not equal
   * }
   * @endcode
   *
   * @param rhs object reference
   * @return true if not equal, otherwise false
   */
  bool
  operator!=(const TClass& rhs) const {
    return !operator==(rhs);
  }

  /**
   * Comparison operator to allow an object value to be compared to see if it is
   * greater than the value of another object.
   *
   * @code
   * Object f1=1000;
   * const Object f2=2000;
   * if( f1 > f2 )
   * {
   *     // frequency f2 is higher
   * }
   * @endcode
   * @param rhs object reference
   * @return true if greater, otherwise false
   */
  bool
  operator>(const TClass& rhs) const {
    // Use equivalence: a > b == b < a
    return rhs.operator<(*dynamic_cast<const TClass*>(this));
  }

  /**
   * Comparison operator to allow an object value to be compared to see if it is
   * greater than or equal to the value of another object.
   *
   * @code
   * Object f1=1000;
   * const Object f2=2000;
   * if( f1 >= f2 )
   * {
   *     // frequency f2 is higher
   * }
   * @endcode
   * @param rhs object reference
   * @return true if greater, otherwise false
   */
  bool
  operator>=(const TClass& rhs) const {
    // Use equivalence: a >= b == !(a < b)
    return !operator<(rhs);
  }

  /**
   * Comparison operator to allow an object value to be compared to see if it is
   * less than or equal to the value of another object.
   *
   * @code
   * Object f1=1000;
   * const Object f2=2000;
   * if( f1 <= f2 )
   * {
   *     // frequency f1 is lower
   * }
   * @endcode
   *
   * @param  rhs object reference
   * @return true if less, otherwise false
   */
  bool
  operator<=(const TClass& rhs) const {
    // use equivalence: a <= b == !(b < a)
    return !rhs.operator<(*dynamic_cast<const TClass*>(this));
  }
};

} /* namespace Mplane */

#endif /* _COMM_COMPOP_HPP_ */
