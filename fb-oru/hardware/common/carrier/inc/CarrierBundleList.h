/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CarrierBundleList.h
 * \brief     Manage list of carrier bundles
 *
 *
 * \details
 *
 */


#ifndef CARRIERBUNDLELIST_H_
#define CARRIERBUNDLELIST_H_

#include "Mutex.h"
#include "ICarrierBundleList.h"

namespace Mplane {

/*!
 * \class CarrierBundleList
 */
class CarrierBundleList : public virtual ICarrierBundleListSetter {
public:
	CarrierBundleList() ;
	virtual ~CarrierBundleList() ;

	/**
	 * Get multi-carrier bundle for tx port
	 * @param tx
	 */
	virtual std::shared_ptr<ICarrierBundle> getMultiCarrierBundle(unsigned tx) const override ;

	/**
	 * Get carrier bundle for tx port
	 * @param tx
	 */
	virtual std::shared_ptr<ICarrierBundle> getCarrierBundle(unsigned tx) const override ;


	/**
	 * Set the carrier bundle for the multicarrier list
	 * @param tx
	 * @param carrierBundle
	 */
	virtual void setMultiCarrierBundle(unsigned tx, const ICarrierBundle& carrierBundle) override ;

	/**
	 * Set the carrier bundle for the non-multicarrier list
	 * @param tx
	 * @param carrierBundle
	 */
	virtual void setCarrierBundle(unsigned tx, const ICarrierBundle& carrierBundle) override ;

private:
	unsigned mNumAntennas ;
	mutable Mutex mMutex ;

    /**
     * Carrier bundle for all enabled carriers - one per antenna
     */
    std::vector< std::shared_ptr<ICarrierBundle> > mCarrierBundles ;

    /**
     * Multi-Carrier bundle for all configured carriers - one per antenna
     */
    std::vector< std::shared_ptr<ICarrierBundle> > mMultiCarrierBundles ;


} ;

}

#endif /* CARRIERBUNDLELIST_H_ */
