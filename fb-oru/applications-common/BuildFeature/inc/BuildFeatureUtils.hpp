/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      BuildFeatureUtils.hpp
 * \brief     BuildFeature class utilities
 *
 *
 * \details
 *
 */


#ifndef BuildFeatureUTILS_HPP_
#define BuildFeatureUTILS_HPP_

#include <memory>

#include "IBuildFeature.h"
#include "BuildFeatureList.h"

namespace Mplane {

template <class T>
class BuildFeatureUtils {
public:
	static std::shared_ptr<IBuildFeature> getInstance()
	{
		static std::shared_ptr<IBuildFeature> instance(std::make_shared<T>()) ;
		return instance ;
	}

	static int registerBuildFeature()
	{
		return BuildFeatureList::getInstance()->registerBuildFeature(
			[]()->std::shared_ptr<IBuildFeature> {
				return T::getInstance() ;
			}
		) ;
	}
} ;

}

#endif /* BuildFeatureUTILS_HPP_ */
