/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangPersist.h
 * \brief     Virtual interface to persistent YANG model values
 *
 *
 * \details   Virtual interface to persistent YANG model values
 *
 */


#ifndef VYMS_INC_IYANGPERSIST_H_
#define VYMS_INC_IYANGPERSIST_H_

#include <set>
#include <memory>
#include <string>
#include <map>

namespace Mplane {

/*!
 * \class  IYangPersist
 * \brief
 * \details
 *
 */
class IYangPersist {
public:

	/**
	 * Factory - values are saved by yang model name
	 */
	static std::shared_ptr<IYangPersist> factory(const std::string& module) ;

	IYangPersist() {}
	virtual ~IYangPersist() {}

	/**
	 * Read the stored values and return the xpath/value pairs as a map
	 */
	virtual std::map<std::string, std::string> read() =0 ;

	/**
	 * Get the current values
	 */
	virtual std::map<std::string, std::string> values() const =0 ;


	/**
	 * Set multiple values
	 * Note that the xpath is checked against the current persisten paths and the value will be ignored
	 * if it's xpath doesn't match any of the persistent paths
	 */
	virtual void set(const std::map<std::string, std::string>& values) =0 ;

	/**
	 * Set a value
	 * Note that the xpath is checked against the current persisten paths and the value will be ignored
	 * if it's xpath doesn't match any of the persistent paths
	 */
	virtual void set(const std::string& xpath, const std::string& value) =0 ;

	/**
	 * Add an xpath for persistent values
	 */
	virtual void setPersist(const std::set<std::string>& xpaths) =0 ;

	/**
	 * Add an xpath for persistent values
	 */
	virtual void setPersist(const std::string& xpath) =0 ;

	/**
	 * Write out the current values in memory to make them persistent
	 */
	virtual bool write() =0 ;

} ;

}

#endif /* VYMS_INC_IYANGPERSIST_H_ */
