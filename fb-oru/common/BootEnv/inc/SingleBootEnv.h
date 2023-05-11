/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SingleBootEnv.h
 * \brief     Manages access to the u-boot environment
 *
 *
 * \details   A case where only a single u-boot environment is stored
 *
 */


#ifndef SINGLEBOOTENV_H_
#define SINGLEBOOTENV_H_

#include <vector>
#include <memory>
#include <map>
#include <string>

#include "Mutex.h"
#include "Loggable.h"
#include "BootEnv.h"
#include "IBootEnvDevice.h"

namespace Mplane {

class SingleBootEnv : public BootEnv {
public:
	virtual ~SingleBootEnv() ;

protected:
	// May be overridden by derived object

	/**
	 * Write the new environment
	 * @return false (and set error string) on any error
	 */
	virtual bool writeEnv(const std::map<std::string, std::string>& newEnv) override ;

protected:
	// constructor
	// deferInit		- set when derived class wants to defer initialisation until that class is ready
	SingleBootEnv(bool deferInit = false) ;

} ;

}

#endif /* BOOTENV_H_ */
