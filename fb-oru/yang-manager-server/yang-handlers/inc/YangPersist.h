/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangPersist.h
 * \brief     Make certain yang model values persistent
 *
 *
 * \details   Make certain yang model values persistent
 *
 */


#ifndef YANG_HANDLERS_INC_YANGPERSIST_H_
#define YANG_HANDLERS_INC_YANGPERSIST_H_

#include "IYangPersist.h"

namespace Mplane {

/*!
 * \class  YangPersist
 * \brief
 * \details
 *
 */
class YangPersist : public virtual IYangPersist {
public:
	YangPersist(const std::string& yangModelName) ;
	virtual ~YangPersist() ;

	/**
	 * Read the stored values and return the xpath/value pairs as a map
	 */
	virtual std::map<std::string, std::string> read() override ;

	/**
	 * Get the current values
	 */
	virtual std::map<std::string, std::string> values() const override ;


	/**
	 * Set multiple values
	 * Note that the xpath is checked against the current persisten paths and the value will be ignored
	 * if it's xpath doesn't match any of the persistent paths
	 */
	virtual void set(const std::map<std::string, std::string>& values) override ;

	/**
	 * Set a value
	 * Note that the xpath is checked against the current persisten paths and the value will be ignored
	 * if it's xpath doesn't match any of the persistent paths
	 */
	virtual void set(const std::string& xpath, const std::string& value) override ;

	/**
	 * Add an xpath for persistent values
	 */
	virtual void setPersist(const std::set<std::string>& xpaths) override ;

	/**
	 * Add an xpath for persistent values
	 */
	virtual void setPersist(const std::string& xpath) override ;

	/**
	 * Write out the current values in memory to make them persistent
	 */
	virtual bool write() override ;

protected:
	bool xpathMatchesPersist(const std::string& xpath) const ;

private:
	std::string mYangModelName ;
	std::string mSaveFilename ;
	bool mDirty ;
	std::map<std::string, std::string> mValues ;
	std::set<std::string> mPersistPaths ;
} ;

}

#endif /* YANG_HANDLERS_INC_YANGPERSIST_H_ */
