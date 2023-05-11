/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SavedInternalKey.h
 * \brief     Saved key for NIMROD
 *
 *
 * \details
 *
 */


#ifndef SAVEDINTERNALKEY_H_
#define SAVEDINTERNALKEY_H_

#include "SavedKey.h"

namespace Mplane {

/**
 * \class 	SavedInternalKey
 * \brief   Saved key for NIMROD
 * \details Internally generated saved key (does not need to be set externally)
 */
class SavedInternalKey : public SavedKey {
public:
	using super = SavedKey ;

	SavedInternalKey() ;
	virtual ~SavedInternalKey() ;

	/**
	 * Get the singleton
	 */
	static std::shared_ptr<IKey> getInstance() ;

private:
	/**
	 * If key is not already set, then auto-create it
	 */
	bool setInitialKey() ;
} ;

}

#endif /* SAVEDINTERNALKEY_H_ */
