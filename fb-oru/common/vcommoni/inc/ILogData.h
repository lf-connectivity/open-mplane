/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ILogData.h
 * \brief     Data logging methods
 *
 *
 * \details   Interface to the methods used for data logging
 *
 */


#ifndef ILOGDATA_H_
#define ILOGDATA_H_


namespace Mplane {

class ILogData {
public:
	ILogData() {}
	virtual ~ILogData() {}

	/**
	 * log an hourly data event
	 * @param dataSource	Name of data source
	 * @param dataStr		String to log
	 */
	virtual void dataHourly(const std::string& dataSource, const std::string& dataStr) const =0 ;

	/**
	 * log a daily data event
	 * @param dataSource	Name of data source
	 * @param dataStr		String to log
	 */
	virtual void dataDaily(const std::string& dataSource, const std::string& dataStr) const =0 ;
} ;

}

#endif /* ILOGDATA_H_ */
