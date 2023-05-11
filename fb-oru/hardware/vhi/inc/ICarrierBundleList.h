/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ICarrierBundleList.h
 * \brief     Virtual interface to lists of ICarrierBundle objects
 *
 *
 * \details
 *
 */


#ifndef ICARRIERBUNDLELIST_H_
#define ICARRIERBUNDLELIST_H_

#include <vector>
#include <memory>
#include "ICarrierBundle.h"

namespace Mplane {

/*!
 * \class ICarrierBundleList
 */
class ICarrierBundleList {
public:
	ICarrierBundleList() {}
	virtual ~ICarrierBundleList() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<ICarrierBundleList> getInstance() ;

	/**
	 * Get multi-carrier bundle for tx port
	 * @param tx
	 */
	virtual std::shared_ptr<ICarrierBundle> getMultiCarrierBundle(unsigned tx) const =0 ;

	/**
	 * Get carrier bundle for tx port
	 * @param tx
	 */
	virtual std::shared_ptr<ICarrierBundle> getCarrierBundle(unsigned tx) const =0 ;
} ;

/*!
 * \class ICarrierBundleListSetter
 */
class ICarrierBundleListSetter : public virtual ICarrierBundleList {
public:
	ICarrierBundleListSetter() {}
	virtual ~ICarrierBundleListSetter() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<ICarrierBundleListSetter> getInstance() ;

	/**
	 * Set the carrier bundle for the multicarrier list
	 * @param tx
	 * @param carrierBundle
	 */
	virtual void setMultiCarrierBundle(unsigned tx, const ICarrierBundle& carrierBundle) =0 ;

	/**
	 * Set the carrier bundle for the non-multicarrier list
	 * @param tx
	 * @param carrierBundle
	 */
	virtual void setCarrierBundle(unsigned tx, const ICarrierBundle& carrierBundle) =0 ;
} ;

}

#endif /* ICARRIERBUNDLELIST_H_ */
