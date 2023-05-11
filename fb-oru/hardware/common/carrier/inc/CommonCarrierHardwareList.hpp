#ifndef _MPLANE_CommonCarrierHardwareList_H_
#define _MPLANE_CommonCarrierHardwareList_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CommonCarrierHardwareList.h
 * \brief     Common list of carrier hardware objects
 *  base class
 *
 *
 * \details   Extends the ICarrierHardwareList interface via templating
 *
 */

#include <iostream>
#include <numeric>
#include <functional>
#include <algorithm>
#include <vector>

#include "ICarrier.h"
#include "ICarrierHardware.h"
#include "ICarrierFail.h"

#include "CommonCarrierHardwareFunctional.h"
#include "CommonCarrierFail.h"


namespace Mplane
{

using namespace Mplane;


/*! @brief  Common carrier hardware list
 *
 *  The CommonCarrierHardwareList class provides a base implementation of the ICarrierHardwareList interface.
 *
 *  Mainly provides iteration methods
 *
 *
 */
template <typename _TCarrierHardware, typename _TCarrierFail = CommonCarrierFail>
class CommonCarrierHardwareList : public virtual ICarrierHardwareList
{
public:
	typedef _TCarrierHardware value_type ;
	typedef _TCarrierFail fail_type ;

	typedef typename std::vector<_TCarrierHardware>::iterator iterator ;
	typedef typename std::vector<_TCarrierHardware>::const_iterator const_iterator ;

    /*! @brief  Constructor
     *
     *  Construct the list
     */
	CommonCarrierHardwareList<_TCarrierHardware, _TCarrierFail>() :
		mCarrierList(),
		mFail(new _TCarrierFail)
	{
	}

    /*! @brief  Add a carrier to the list
     *
     *  Given the hardware-independent carrier instance, creates a hardware dependent
     *  carrier to calculate the hardware-specific settings
     * @param carrier new carrier reference
     * @return false if cannot accept the carrier settings
     */
    virtual bool addCarrier(const ICarrier &carrier)
    {
    	if (static_cast<unsigned>(carrier.getIndex()) >= mCarrierList.size())
    		mCarrierList.resize(carrier.getIndex()+1) ;

    	mCarrierList.at(carrier.getIndex()) = _TCarrierHardware(&carrier) ;
    	return true ;
    }

    /*! @brief  Validate the carrier change
     *
     *  Ensure this worker is happy with the proposed carrier change
     * @param carrier new carrier reference
     * @return true on success; false on failure (use failReason() method to get reason string)
     */
    virtual bool validateChange(const ICarrier& carrier)
    {
    	if (static_cast<unsigned>(carrier.getIndex()) > mCarrierList.size())
    	{
    		mFail->setFailReason("carrier index larger than carrier hardware list length") ;
    		return false ;
    	}

    	_TCarrierHardware *ch = &mCarrierList[carrier.getIndex()] ;
    	bool status = ch->validateChange(carrier) ;
    	if (!status)
    		mFail->setFailReason( ch->failReason() ) ;
    	return status ;
    }

    /*! @brief  Carrier changed notification
     *
     *  Given a changed hardware-independent carrier instance, gets the hardware-specific
     *  carrier to update it's values
     * @param carrier new carrier reference
     * @return false if cannot accept the carrier settings
     */
    virtual bool carrierChange(const ICarrier &carrier)
    {
    	if (static_cast<unsigned>(carrier.getIndex()) > mCarrierList.size())
    	{
    		mFail->setFailReason("carrier index larger than carrier hardware list length") ;
    		return false ;
    	}

    	_TCarrierHardware *ch = &mCarrierList[carrier.getIndex()] ;
    	bool status = ch->carrierChange(carrier) ;
    	if (!status)
    		mFail->setFailReason( ch->failReason() ) ;
    	return status ;
    }

    /*! @brief  About to apply changes to hardware
     *
     * Called just prior to calling the updateHardware() method. Allows carrier to disable anything
     * that might affect the TX while changing setting (for example)
     * @return false if cannot accept the carrier settings
     */
    virtual bool preUpdate()
    {
    	ch_pred_foreach_bind_t<_TCarrierHardware, bool> functor = std::for_each(
			mCarrierList.begin(),
			mCarrierList.end(),
			carrier_hardware_foreach_bind(&_TCarrierHardware::preUpdate, &_TCarrierHardware::isChanged)
		) ;

    	if (!functor.getStatus())
    	{
    		mFail->setFailReason( functor.failReason() ) ;
    	}

    	return functor.getStatus() ;
    }

    /*! @brief  Apply changes to hardware
     *
     * Called after Mplane::ICarrier::carrierChange() to actively apply the changed values to the hardware
     * @return false if cannot accept the carrier settings
     */
    virtual bool updateHardware()
    {
    	ch_pred_foreach_bind_t<_TCarrierHardware, bool> functor = std::for_each(
			mCarrierList.begin(),
			mCarrierList.end(),
			carrier_hardware_foreach_bind(&_TCarrierHardware::updateHardware, &_TCarrierHardware::isChanged)
		) ;

    	if (!functor.getStatus())
    	{
    		mFail->setFailReason( functor.failReason() ) ;
    	}

    	return functor.getStatus() ;
    }

    /*! @brief  Have just applied changes to hardware
     *
     * Called just after calling the updateHardware() method. Allows carrier to re-enable anything previously
     * disabled
     * @return false if cannot accept the carrier settings
     */
    virtual bool postUpdate()
    {
    	ch_pred_foreach_bind_t<_TCarrierHardware, bool> functor = std::for_each(
			mCarrierList.begin(),
			mCarrierList.end(),
			carrier_hardware_foreach_bind(&_TCarrierHardware::postUpdate, &_TCarrierHardware::isChanged)
		) ;

    	if (!functor.getStatus())
    	{
    		mFail->setFailReason( functor.failReason() ) ;
    	}

    	return functor.getStatus() ;
    }

    /*! @brief  All changes are complete
     *
     * Called after postUpdate() to indicate that all changes have been completed
     */
    virtual void changeComplete()
    {
		std::for_each(
			mCarrierList.begin(),
			mCarrierList.end(),
			carrier_hardware_foreach_bind(&_TCarrierHardware::changeComplete)
		) ;
    }


    /** @brief  Get a carrier hardware from the list
     *
     * @param index		carrier index
     * @return carrier hardware pointer or NULL if invalid index
     */
	virtual _TCarrierHardware* getCarrierHardware(const unsigned index)
	{
		if (index < mCarrierList.size())
			return &mCarrierList.at(index) ;
		return NULL ;
	}

    /** @brief  Get a carrier from the list
     *
     * @param index		carrier index
     * @return carrier reference
     */
	virtual const ICarrier& getCarrier(const unsigned index) const
	{
		return mCarrierList.at(index).getCarrier() ;
	}

	typedef const _TCarrierHardware (_TCarrierHardware::*BinaryFunction)(const _TCarrierHardware&)  ;
	typedef _TCarrierHardware (_TCarrierHardware::*UnaryFunction)()  ;

	/** @brief Summarise the list
	 *
	 * Iterate over the carrier hardware list summarising the appropriate field(s). Returns a ICarrierHardware
	 * object containing the summary
	 *
	 * @param fn	A binary sum ICarrierHardware member function
	 * @return ICarrierHardware object containing the summed field(s)
	 */
	virtual const _TCarrierHardware summariseList(BinaryFunction fn)
	{
		return std::accumulate(mCarrierList.begin(), mCarrierList.end(), _TCarrierHardware(), std::mem_fun_ref(fn)) ;
	}

	/** @brief Summarise the list
	 *
	 * Iterate over the carrier hardware list summarising the appropriate field(s). Returns a ICarrierHardware
	 * object containing the summary
	 *
	 * @param fn	A binary sum ICarrierHardware member function
	 * @return ICarrierHardware object containing the summed field(s)
	 */
	template <typename _TOp>
	const _TCarrierHardware summariseList(_TOp fn)
	{
		return std::accumulate(mCarrierList.begin(), mCarrierList.end(), _TCarrierHardware(), fn) ;
	}

	/** @brief iterate the list
	 *
	 * Iterate over the carrier hardware list calling the function to change each entry.
	 *
	 * @param fn	An ICarrierHardware member function
	 */
	virtual void transformList(UnaryFunction fn)
	{
		std::transform(mCarrierList.begin(), mCarrierList.end(), mCarrierList.begin(), std::mem_fun_ref(fn)) ;
	}

	/** @brief iterate the list
	 *
	 * Iterate over the carrier hardware list calling the function to change each entry.
	 *
	 * @param fn	Any unary function
	 */
	template <typename _TOp>
	void transformList(_TOp fn)
	{
		std::transform(mCarrierList.begin(), mCarrierList.end(), mCarrierList.begin(), fn) ;
	}


	/** @brief iterate the list
	 *
	 * Iterate over the carrier hardware list calling the function to change each entry.
	 *
	 * @param fn	An ICarrierHardware member function
	 */
	virtual void foreachList(UnaryFunction fn)
	{
		std::for_each(mCarrierList.begin(), mCarrierList.end(), std::mem_fun_ref(fn)) ;
	}

	/** @brief iterate the list
	 *
	 * Iterate over the carrier hardware list calling the function to change each entry.
	 *
	 * @param fn	Any unary function
	 */
	template <typename _TOp>
	void foreachList(_TOp fn)
	{
		std::for_each(mCarrierList.begin(), mCarrierList.end(), fn) ;
	}

	/**
	 * Get starting iterator
	 * @return list beginning
	 */
	iterator begin() { return mCarrierList.begin() ; }

	/**
	 * Get ending iterator
	 * @return list end
	 */
	iterator end() { return mCarrierList.end() ; }

	/**
	 * Get starting iterator
	 * @return list beginning
	 */
	const_iterator begin() const { return mCarrierList.begin() ; }

	/**
	 * Get ending iterator
	 * @return list end
	 */
	const_iterator end()  const { return mCarrierList.end() ; }


    /*! @brief  Get failure reason
     *
     *  If a method fails, then this method will return a
     *  string describing the reason for failure
     * @return string containing reason for failure, or empty string if no fail
     */
    virtual std::string failReason(void)
    {
    	return mFail->failReason() ;
    }


    /**
     * @brief Return the size of the list
     * @return number of CarrierHardware objects in list
     */
    virtual unsigned size(void) const
    {
    	return mCarrierList.size() ;
    }

    /**
     * @brief Return boolean stating whether list is empty or not
     * @return true if empty
     */
    virtual bool empty(void) const
    {
    	return mCarrierList.empty() ;
    }

    /**
     * @brief Print out contents of carrier list to stdout
     * Used for debug only
     */
    virtual void showCarriers(std::ostream& os = std::cout) const
    {
    	os << "== Carrier Hardware List ==" << std::endl ;
    	std::for_each(mCarrierList.begin(), mCarrierList.end(),
    		carrier_hardware_foreach_bind1(&_TCarrierHardware::showCarrier, os)
    	) ;
    	os << "===========================" << std::endl ;
    }

    /**
     * Returns the list of CarrierHardware pointers
     */
    virtual std::vector<ICarrierHardware*> getList() override
	{
    	std::vector<ICarrierHardware*> list ;
    	for (auto& ch : mCarrierList)
    	{
    		list.push_back(&ch) ;
    	}
    	return list ;
	}


    /*! @brief  Destructor
     *
     */
    virtual ~CommonCarrierHardwareList<_TCarrierHardware, _TCarrierFail>()
	{
	}

private:
    /**
    * List of carrier hardware entries
    */
    std::vector<_TCarrierHardware> mCarrierList;

    /**
     * CarrierFail object
     */
    std::shared_ptr<ICarrierFail> mFail ;

};



}


#endif /* _MPLANE_COMMONCARRIERSERVER_H_ */
