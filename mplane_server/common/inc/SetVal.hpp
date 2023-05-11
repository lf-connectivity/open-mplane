/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SetVal.hpp
 * \brief     Settable value which flags whether the value is unset or not
 *
 *
 * \details   Template for a settable value based on any type/class which has a
 * default constructor, an operator==(), and an operator=()
 *
 */

#ifndef SETVAL_HPP_
#define SETVAL_HPP_

#include <ostream>

namespace Mplane {

template <typename T>
class SetVal {
 public:
  using value_type = T;

  /**
   * Default constructor
   */
  SetVal<T>() : mVal(), mSet(false) {}

  /**
   * Construct with a value setting
   */
  explicit SetVal<T>(T val) : mVal(val), mSet(true) {}

  /**
   * Destroy
   */
  virtual ~SetVal<T>() {}

  /**
   * Copy constructor
   */
  explicit SetVal<T>(const SetVal<T>& other)
      : mVal(other.mVal), mSet(other.mSet) {}

  /**
   * Assignment constructor
   * @param rhs
   * @return
   */
  SetVal<T>&
  operator=(const SetVal<T>& rhs) {
    mVal = rhs.mVal;
    mSet = rhs.mSet;
    return *this;
  }

  /**
   * Assignment from value
   * @param val
   * @return
   */
  SetVal<T>&
  operator=(const T& val) {
    set(val);
    return *this;
  }

  /**
   * Compare with value
   * @param val
   * @return
   */
  bool
  operator==(const T& val) {
    if (!mSet)
      return false;

    return mVal == val;
  }

  /**
   * Compare with SetVal<T>
   * @param rhs
   * @return
   */
  bool
  operator==(const SetVal<T>& rhs) {
    if (!rhs.mSet)
      return false;

    return *this == rhs.mVal;
  }

  /**
   * Set the value
   * @param val
   */
  void
  set(T val) {
    mVal = val;
    mSet = true;
  }

  /**
   * Clear out the value
   */
  void
  clear() {
    mSet = false;
    mVal = T();
  }

  /**
   * Accessor
   * @return
   */
  T
  get() const {
    // if not set return default
    if (!mSet)
      return T();

    return mVal;
  }

  /**
   * Determine whether value is set
   * @return
   */
  bool
  isSet() const {
    return mSet;
  }

  /**
   * Provide a swap
   * @param other
   */
  void
  swap(SetVal<T>& other) {
    using std::swap;
    swap(mVal, other.mVal);
    swap(mSet, other.mSet);
  }

  /**
   * Display the value - shows UNSET if the value is not yet set
   * @param os Output stream
   */
  void
  show(std::ostream& os) const {
    if (!mSet)
      os << "UNSET";
    else
      os << mVal;
  }

 private:
  T mVal;
  bool mSet;
};

/**
 * Make swap available as a std::swap overload
 * @param a
 * @param b
 */
template <typename T>
void
swap(SetVal<T>& a, SetVal<T>& b) {
  a.swap(b);
}

} // namespace Mplane

// Make SetVal printable
template <typename T>
inline std::ostream&
operator<<(std::ostream& os, const Mplane::SetVal<T>& val) {
  val.show(os);
  return os;
}

template <>
inline std::ostream&
operator<<(std::ostream& os, const Mplane::SetVal<bool>& val) {
  if (!val.isSet())
    os << "UNSET";
  else
    os << (val.get() ? "true" : "false");
  return os;
}

#endif /* SETVAL_HPP_ */
