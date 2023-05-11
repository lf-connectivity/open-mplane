/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedKey.h
 * \brief     Saved key for KS CART
 *
 *
 * \details
 *
 */


#ifndef SAVEDKEY_H_
#define SAVEDKEY_H_

#include "Key.h"

namespace Mplane {

class SavedKey : public Key {
public:
	using super = Key ;

	SavedKey() ;
	virtual ~SavedKey() ;

	/**
	 * Get the singleton
	 */
	static std::shared_ptr<IKey> getInstance() ;

	/**
	 * Set the license key from a hex string
	 * @param licenseKey
	 * @return true if valid 128bit hex value string; false otherwise
	 */
	virtual bool setLicenseKey(const std::string& licenseKey) override ;

	/**
	 * Get the key in an encoded form suitable for sharing with other applications
	 * @return
	 */
	virtual std::string encodedKey() override ;

	/**
	 * Use an encoded key string to set the license key
	 * @param encodedKey
	 * @return true if key set; false otherwise
	 */
	virtual bool setFromEncodedKey(const std::string& encodedKey) override ;

	/**
	 * Get the license key as an array suitable for using with Crypt
	 * @return the license key value
	 */
	virtual std::vector<uint32_t> licenseKey() const override ;

	/**
	 * Is the license key currently set?
	 */
	virtual bool isSet() const override ;

} ;

}

#endif /* SAVEDKEY_H_ */
