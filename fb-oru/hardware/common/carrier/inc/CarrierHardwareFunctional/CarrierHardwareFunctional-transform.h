#ifndef _MPLANE_CommonCarrierHardwareFunctionalTransform_H_
#define _MPLANE_CommonCarrierHardwareFunctionalTransform_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierHardwareFunctional-transform.h
 * \brief     Template functions for CarrierHardware
 *
 *
 * \details   Binder functions for ICarrierHardware use with CarrierHardwareList transform STL
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
 * Binds a Carrier Hardware object member function with an argument.
 * Creates an unary operator for use with std::transform
 *
 * @param fn The member function
 * @param arg an argument to fn
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _Arg>
class ch_unary_bind_t : public std::unary_function<const _TCarrierHardware&, const _TCarrierHardware>
{
public:
  explicit ch_unary_bind_t(const _TCarrierHardware (_TCarrierHardware::*fn)(const _Arg) const, const _Arg arg)
  : mFn(fn),
    mArg(arg)
  { }

  const _TCarrierHardware operator()(const _TCarrierHardware& a) const
  {
	  return (a.*mFn)(mArg);
  }

private:
  const _TCarrierHardware (_TCarrierHardware::*mFn)(const _Arg) const;
  const _Arg mArg ;
};

template <typename _TCarrierHardware, typename _Arg>
	inline ch_unary_bind_t<_TCarrierHardware, _Arg>
	carrier_hardware_transform_bind(const _TCarrierHardware (_TCarrierHardware::*fn)(const _Arg) const, const _Arg arg)
	{
		return ch_unary_bind_t<_TCarrierHardware, _Arg>(fn, arg);
	}



//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Binds a Carrier Hardware object member function with a predicate member function.
 * Creates a unary operator for use with std::transform
 *
 * @param fn The member function returning a ref to _TCarrierHardware
 * @param pred The member predicate function
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware>
class ch_pred_unary_bind_t : public std::unary_function<const _TCarrierHardware&, const _TCarrierHardware>
{
public:
  explicit ch_pred_unary_bind_t(const _TCarrierHardware (_TCarrierHardware::*fn)() const, const bool (_TCarrierHardware::*pred)() const)
  : mFn(fn),
    mPred(pred)
  { }

  const _TCarrierHardware operator()(const _TCarrierHardware& a) const
  {
	  if ((a.*mPred)())
	  {
		  return (a.*mFn)();
	  }
	  return a ;
  }

private:
  const _TCarrierHardware (_TCarrierHardware::*mFn)() const;
  const bool (_TCarrierHardware::*mPred)() const;
};

template <typename _TCarrierHardware>
	inline ch_pred_unary_bind_t<_TCarrierHardware>
	carrier_hardware_transform_bind(const _TCarrierHardware (_TCarrierHardware::*fn)() const, const bool (_TCarrierHardware::*pred)() const)
	{
		return ch_pred_unary_bind_t<_TCarrierHardware>(fn, pred);
	}


//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Binds a Carrier Hardware object member function with a predicate member function that takes an argument.
 * Creates a unary operator for use with std::transform
 *
 * @param fn The member function
 * @param pred The member predicate function
 * @param arg an argument to pred
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _Arg>
class ch_pred_arg_unary_bind_t : public std::unary_function<const _TCarrierHardware&, const _TCarrierHardware>
{
public:
  explicit ch_pred_arg_unary_bind_t(const _TCarrierHardware (_TCarrierHardware::*fn)() const, const bool (_TCarrierHardware::*pred)(const _Arg) const, const _Arg arg)
  : mFn(fn),
    mPred(pred),
    mArg(arg)
  { }

  const _TCarrierHardware operator()(const _TCarrierHardware& a) const
  {
	  if ((a.*mPred)(mArg))
	  {
		  return (a.*mFn)();
	  }
	  return a ;
  }

private:
  const _TCarrierHardware (_TCarrierHardware::*mFn)() const;
  const bool (_TCarrierHardware::*mPred)(const _Arg) const;
  const _Arg mArg ;
};

template <typename _TCarrierHardware, typename _Arg>
	inline ch_pred_arg_unary_bind_t<_TCarrierHardware, _Arg>
	carrier_hardware_transform_bind(const _TCarrierHardware (_TCarrierHardware::*fn)() const, const bool (_TCarrierHardware::*pred)(const _Arg) const, const _Arg arg)
	{
		return ch_pred_arg_unary_bind_t<_TCarrierHardware, _Arg>(fn, pred, arg);
	}

//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Binds a Carrier Hardware object member function with a predicate member function that takes an argument.
 * Creates an unary operator for use with std::transform
 *
 * @param fn The member function
 * @param fn_arg an argument to function
 * @param pred The member predicate function
 * @param pred_arg an argument to pred
 * @return a unary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _Fn_arg, typename _Pred_arg>
class ch_pred_arg_unary_bind2_t : public std::unary_function<const _TCarrierHardware&, const _TCarrierHardware>
{
public:
  explicit ch_pred_arg_unary_bind2_t(
			const _TCarrierHardware (_TCarrierHardware::*fn)(const _Fn_arg) const,
			const _Fn_arg fn_arg,
			const bool (_TCarrierHardware::*pred)(const _Pred_arg) const,
			const _Pred_arg pred_arg) :
  mFn(fn),
  mPred(pred),
  mFnArg(fn_arg),
  mPredArg(pred_arg)
  { }

  const _TCarrierHardware operator()(const _TCarrierHardware& a) const
  {
	  if ((a.*mPred)(mPredArg))
	  {
		  return (a.*mFn)(mFnArg);
	  }
	  return a ;
  }

private:
  const _TCarrierHardware (_TCarrierHardware::*mFn)(const _Fn_arg) const;
  const bool (_TCarrierHardware::*mPred)(const _Pred_arg) const;
  const _Fn_arg mFnArg ;
  const _Pred_arg mPredArg ;
};

template <typename _TCarrierHardware, typename _Fn_arg, typename _Pred_arg>
	inline ch_pred_arg_unary_bind2_t<_TCarrierHardware, _Fn_arg, _Pred_arg>
	carrier_hardware_transform_bind(
			const _TCarrierHardware (_TCarrierHardware::*fn)(const _Fn_arg) const,
			const _Fn_arg fn_arg,
			const bool (_TCarrierHardware::*pred)(const _Pred_arg) const,
			const _Pred_arg pred_arg)
	{
		return ch_pred_arg_unary_bind2_t<_TCarrierHardware, _Fn_arg, _Pred_arg>(fn, fn_arg, pred, pred_arg);
	}

}

#endif /* _MPLANE_CommonCarrierHardwareFunctionalTransform_H_ */
