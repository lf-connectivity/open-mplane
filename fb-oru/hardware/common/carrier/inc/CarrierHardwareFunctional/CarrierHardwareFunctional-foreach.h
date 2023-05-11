#ifndef _MPLANE_CommonCarrierHardwareFunctionalForeach_H_
#define _MPLANE_CommonCarrierHardwareFunctionalForeach_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierHardwareFunctional-foreach.h
 * \brief     Template funtions for CarrierHardware
 *
 *
 * \details   Binder functions for ICarrierHardware use with CarrierHardwareList for_each STL
 *
 */

#include "ICarrierHardware.h"
#include <numeric>
#include <functional>
#include <algorithm>
#include <vector>

namespace Mplane
{

using namespace Mplane;


//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Converts an ICarrierHardware member function into a function suitable for running in std::for_each
 *
 * @param fn The member function
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _TFunRet>
class ch_foreach_bind_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit ch_foreach_bind_t(_TFunRet (_TCarrierHardware::*fn)())
  : mFn(fn)
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  (a.*mFn)();
	  return a ;
  }

private:
  _TFunRet (_TCarrierHardware::*mFn)() ;
};

template <typename _TCarrierHardware, typename _TFunRet>
	inline ch_foreach_bind_t<_TCarrierHardware, _TFunRet>
	carrier_hardware_foreach_bind(_TFunRet (_TCarrierHardware::*fn)())
	{
		return ch_foreach_bind_t<_TCarrierHardware, _TFunRet>(fn);
	}


//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Converts an ICarrierHardware member function into a function suitable for running in std::for_each
 * Specialisation for member functions that return bool true for success. On failure, the failure reason is stored
 * and no subsequent function calls will be run
 *
 * @param fn The member function returning bool
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware>
class ch_foreach_bind_t<_TCarrierHardware, bool> : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit ch_foreach_bind_t<_TCarrierHardware, bool>(bool (_TCarrierHardware::*fn)()) :
  	  mFn(fn),
  	  mStatus(true),
  	  mFailReason("")
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  if (mStatus)
	  {
		  mStatus = (a.*mFn)();
		  if (!mStatus)
		  {
			  mFailReason = a.failReason() ;
		  }
	  }
	  return a ;
  }

  std::string failReason(void)
  {
	  return mFailReason ;
  }

  bool getStatus(void)
  {
	  return mStatus ;
  }

private:
  bool (_TCarrierHardware::*mFn)() ;
  bool mStatus ;
  std::string mFailReason ;
};



//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Converts an ICarrierHardware member function into a function suitable for running in std::for_each
 * Binds a Carrier Hardware object member function with a predicate member function.
 * Creates a unary operator suitable for running in std::for_each
 *
 * @param fn The member function
 * @param pred The member predicate function
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _TFunRet>
class ch_pred_foreach_bind_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit ch_pred_foreach_bind_t(_TFunRet (_TCarrierHardware::*fn)(), const bool (_TCarrierHardware::*pred)() const)
  : mFn(fn),
    mPred(pred)
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  if ((a.*mPred)())
	  {
		  (a.*mFn)();
	  }
	  return a ;
  }

private:
  _TFunRet (_TCarrierHardware::*mFn)() ;
  const bool (_TCarrierHardware::*mPred)() const;
};

template <typename _TCarrierHardware, typename _TFunRet>
	inline ch_pred_foreach_bind_t<_TCarrierHardware, _TFunRet>
	carrier_hardware_foreach_bind(_TFunRet (_TCarrierHardware::*fn)(), const bool (_TCarrierHardware::*pred)() const)
	{
		return ch_pred_foreach_bind_t<_TCarrierHardware, _TFunRet>(fn, pred);
	}


//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Converts an ICarrierHardware member function into a function suitable for running in std::for_each
 * Binds a Carrier Hardware object member function with a predicate member function.
 * Creates a unary operator suitable for running in std::for_each
 * Specialisation for member functions that return bool true for success. On failure, the failure reason is stored
 * and no subsequent function calls will be run
 *
 * @param fn The member function
 * @param pred The member predicate function
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware>
class ch_pred_foreach_bind_t<_TCarrierHardware, bool> : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit ch_pred_foreach_bind_t(bool (_TCarrierHardware::*fn)(), const bool (_TCarrierHardware::*pred)() const) :
  	  mFn(fn),
  	  mPred(pred),
  	  mStatus(true),
  	  mFailReason("")
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  if (mStatus)
	  {
		  if ((a.*mPred)())
		  {
			  mStatus = (a.*mFn)();
			  if (!mStatus)
			  {
				  mFailReason = a.failReason() ;
			  }
		  }
	  }
	  return a ;
  }

  std::string failReason(void)
  {
	  return mFailReason ;
  }

  bool getStatus(void)
  {
	  return mStatus ;
  }

private:
  bool (_TCarrierHardware::*mFn)() ;
  const bool (_TCarrierHardware::*mPred)() const;
  bool mStatus ;
  std::string mFailReason ;

};

//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function with 1 argument
 *
 * Converts an ICarrierHardware member function into a function suitable for running in std::for_each, binding
 * a single argument
 *
 * @param fn The member function
 * @param arg1 the argument
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
class ch_foreach_bind1_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit ch_foreach_bind1_t(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1), const _TArg1& arg1)
  : mFn(fn),
    mArg1(arg1)
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  (a.*mFn)(mArg1);
	  return a ;
  }

private:
  _TFunRet (_TCarrierHardware::*mFn)(const _TArg1& arg1) ;
  const _TArg1& mArg1 ;
};

template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
	inline ch_foreach_bind1_t<_TCarrierHardware, _TArg1, _TFunRet>
	carrier_hardware_foreach_bind1(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1), const _TArg1& arg1)
	{
		return ch_foreach_bind1_t<_TCarrierHardware, _TArg1, _TFunRet>(fn, arg1);
	}

//------------------------------------------------------------------------------------------------------------------------------
template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
class ch_foreach_const_bind1_nonconst_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit ch_foreach_const_bind1_nonconst_t(_TFunRet (_TCarrierHardware::*fn)(_TArg1& arg1) const, _TArg1& arg1)
  : mFn(fn),
    mArg1(arg1)
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  (a.*mFn)(mArg1);
	  return a ;
  }

  const _TCarrierHardware& operator()(const _TCarrierHardware& a)
  {
	  (a.*mFn)(mArg1);
	  return a ;
  }

private:
  _TFunRet (_TCarrierHardware::*mFn)(_TArg1& arg1) const ;
  _TArg1& mArg1 ;
};

template <typename _TCarrierHardware, typename _TArg1, typename _TFunRet>
	inline ch_foreach_const_bind1_nonconst_t<_TCarrierHardware, _TArg1, _TFunRet>
	carrier_hardware_foreach_bind1(_TFunRet (_TCarrierHardware::*fn)(_TArg1& arg1) const, _TArg1& arg1)
	{
		return ch_foreach_const_bind1_nonconst_t<_TCarrierHardware, _TArg1, _TFunRet>(fn, arg1);
	}


//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function with 2 argument2
 *
 * Converts an ICarrierHardware member function into a function suitable for running in std::for_each, binding
 * 2 arguments
 *
 * @param fn The member function
 * @param arg1 the 1st argument
 * @param arg2 the 2nd argument
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _TArg1, typename _TArg2, typename _TFunRet>
class ch_foreach_bind2_t : public std::unary_function<_TCarrierHardware&, _TCarrierHardware&>
{
public:
  explicit ch_foreach_bind2_t(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1, const _TArg2& arg2),
		  const _TArg1& arg1, const _TArg2& arg2)
  : mFn(fn),
    mArg1(arg1),
    mArg2(arg2)
  {
  }

  _TCarrierHardware& operator()(_TCarrierHardware& a)
  {
	  (a.*mFn)(mArg1, mArg2);
	  return a ;
  }

private:
  _TFunRet (_TCarrierHardware::*mFn)(const _TArg1& arg1, const _TArg2& arg2) ;
  const _TArg1& mArg1 ;
  const _TArg2& mArg2 ;
};

template <typename _TCarrierHardware, typename _TArg1, typename _TArg2, typename _TFunRet>
	inline ch_foreach_bind2_t<_TCarrierHardware, _TArg1, _TArg2, _TFunRet>
	carrier_hardware_foreach_bind2(_TFunRet (_TCarrierHardware::*fn)(const _TArg1& arg1, const _TArg2& arg2),
		const _TArg1& arg1, const _TArg2& arg2)
	{
		return ch_foreach_bind2_t<_TCarrierHardware, _TArg1, _TArg2, _TFunRet>(fn, arg1, arg2);
	}




}

#endif /* _MPLANE_CommonCarrierHardwareFunctionalForeach_H_ */
