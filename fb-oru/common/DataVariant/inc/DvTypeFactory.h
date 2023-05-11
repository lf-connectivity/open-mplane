/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DvTypeFactory.h
 * \brief     Factory for creating type instances. Also creates a singleton list of types
 *
 *
 * \details   Factory method for creating the correct IDvType instance based on the requested type
 *
 * 			Also create a single instance of a list of all the possible types, having a single instance of each type. These instances
 * 			can then be thought of as "static" and we can iterate through the list calling the object's methods as if they were common
 * 			static methods.
 *
 * 			The class provides the list of the types in the order in which they should be processed. For example, when trying a string
 * 			to set a DataVariant value, we want to attempt to use the string in a particular order, ending with the "STRING" type
 *
 */


#ifndef DVTYPEFACTORY_H_
#define DVTYPEFACTORY_H_

#include <vector>
#include <memory>

#include "IDvType.h"

namespace Mplane {

class DvTypeFactory {
public:
	/**
	 * Singleton creation of the single list of all types, created in the order in which they should be processed
	 */
	static std::vector< std::shared_ptr<IDvType> > getTypes() ;

	/**
	 * Factory method for creating type instances of a specified type
	 * @param type
	 * @return shared pointer to the type instance
	 */
	static std::shared_ptr<IDvType> factory(DataVariantType::Type type, const std::string& typeStr = "") ;

	/**
	 * Factory method for creating type instances from a type string
	 * @param type
	 * @return shared pointer to the type instance
	 */
	static std::shared_ptr<IDvType> factory(const std::string& typeStr) ;

	/**
	 * Factory method for creating type instances by copying an existing instance
	 * @param rhs the value to copy
	 * @return shared pointer to the type instance
	 */
	static std::shared_ptr<IDvType> copy(std::shared_ptr<IDvType> rhs) ;

} ;

}

#endif /* DVTYPEFACTORY_H_ */
