#ifndef _MPLANE_CommonCarrierHardwareFunctionalSummarise_H_
#define _MPLANE_CommonCarrierHardwareFunctionalSummarise_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierHardwareFunctional-summarise.h
 * \brief     Template functions for CarrierHardware
 *
 *
 * \details   Binder functions for ICarrierHardware use with CarrierHardwareList summaries function (i.e. std::accumulate)
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
 * Creates an binary operator for use with std::accumulate
 *
 * @param fn The member function
 * @param arg an argument to fn
 * @return a binary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _Arg>
class ch_binary_bind_t : public std::binary_function<const _TCarrierHardware&, const _TCarrierHardware&, const _TCarrierHardware>
{
public:
  explicit ch_binary_bind_t(const _TCarrierHardware (_TCarrierHardware::*fn)(const _TCarrierHardware&, const _Arg) const, const _Arg arg)
  : mFn(fn),
    mArg(arg)
  { }

  const _TCarrierHardware operator()(const _TCarrierHardware& a, const _TCarrierHardware& b) const
  {
	  return (a.*mFn)(b, mArg);
  }

private:
  const _TCarrierHardware (_TCarrierHardware::*mFn)(const _TCarrierHardware&, const _Arg) const;
  const _Arg mArg ;
};

template <typename _TCarrierHardware, typename _Arg>
	inline ch_binary_bind_t<_TCarrierHardware, _Arg>
	carrier_hardware_summarise_bind(const _TCarrierHardware (_TCarrierHardware::*fn)(const _TCarrierHardware&, const _Arg) const, const _Arg arg)
	{
		return ch_binary_bind_t<_TCarrierHardware, _Arg>(fn, arg);
	}



//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Bind a carrier hardware object member function
 *
 * Binds a Carrier Hardware object member function with a predicate member function that takes an argument.
 * Creates an binary operator for use with std::accumulate
 *
 * @param fn The member function
 * @param pred The member predicate function
 * @param arg an argument to pred
 * @return a binary operation usable in STL algorithms
 */
template <typename _TCarrierHardware, typename _Arg>
class ch_pred_binary_bind_t : public std::binary_function<const _TCarrierHardware&, const _TCarrierHardware&, const _TCarrierHardware>
{
public:
  explicit ch_pred_binary_bind_t(const _TCarrierHardware (_TCarrierHardware::*fn)(const _TCarrierHardware&) const, const bool (_TCarrierHardware::*pred)(const _Arg) const, const _Arg arg)
  : mFn(fn),
    mPred(pred),
  mArg(arg)
  { }

  const _TCarrierHardware operator()(const _TCarrierHardware& a, const _TCarrierHardware& b) const
  {
	  if ((b.*mPred)(mArg))
	  {
		  return (a.*mFn)(b);
	  }
	  return a ;
  }

private:
  const _TCarrierHardware (_TCarrierHardware::*mFn)(const _TCarrierHardware&) const;
  const bool (_TCarrierHardware::*mPred)(const _Arg) const;
  const _Arg mArg ;
};

template <typename _TCarrierHardware, typename _Arg>
	inline ch_pred_binary_bind_t<_TCarrierHardware, _Arg>
	carrier_hardware_summarise_bind(const _TCarrierHardware (_TCarrierHardware::*fn)(const _TCarrierHardware&) const, const bool (_TCarrierHardware::*pred)(const _Arg) const, const _Arg arg)
	{
		return ch_pred_binary_bind_t<_TCarrierHardware, _Arg>(fn, pred, arg);
	}



}

#endif /* _MPLANE_CommonCarrierHardwareFunctionalSummarise_H_ */
