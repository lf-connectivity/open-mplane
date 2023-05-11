/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IBusSettings.h
 * \brief     IBus settings
 *
 *
 * \details   Every IBus will have some associated settings. This virtual interface defines the API for writeable and read-only
 * 				view on those settings
 *
 */


#ifndef VHI_INC_IBUSSETTINGS_H_
#define VHI_INC_IBUSSETTINGS_H_


namespace Mplane {

/*!
 * \class  IBusReadonlySettings
 * \brief  Read-only set of IBus settings
 * \details
 *
 */
class IBusReadonlySettings {
public:

	IBusReadonlySettings() {}
	virtual ~IBusReadonlySettings() {}

	/**
	 * Is the data transported over the bus MS first?
	 * NOTE: This is only the data transport over the bus. The endpoint device may
	 * use the data in any endian
	 */
	virtual bool isBigEndian() const =0 ;


	/**
	 * Is the data transported over the bus LS first?
	 * NOTE: This is only the data transport over the bus. The endpoint device may
	 * use the data in any endian
	 */
	virtual bool isLittleEndian() const =0 ;

	/**
	 * For read and write operations from an offset, this method indicates the
	 * size of the offset parameter in number of bits.
	 */
	virtual unsigned getOffsetNumBits() const =0 ;
} ;

/*!
 * \class  IBusSettings
 * \brief  Write set of IBus settings
 * \details
 *
 */
class IBusSettings : public virtual IBusReadonlySettings {
public:

	IBusSettings() {}
	virtual ~IBusSettings() {}

	/**
	 * Data transported over the bus MS first
	 */
	virtual bool setBigEndian() =0 ;


	/**
	 * Data transported over the bus LS first
	 */
	virtual bool setLittleEndian() =0 ;

	/**
	 * Number of bits in the offset used in read/write operations
	 */
	virtual bool setOffsetNumBits(unsigned size) =0 ;

} ;

}

#endif /* VHI_INC_IBUSSETTINGS_H_ */
