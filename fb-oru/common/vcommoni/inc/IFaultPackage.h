/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IFaultPackage.h
 * \brief     Interface to class which packages up fault owner and fault(s)
 *
 *
 * \details   Every IFault must be managed by an IFaultOwner. This class creates a single object that an application can
 * 				create to add a fault (or collection of faults) with the appropriate owner.
 *
 */


#ifndef IFAULTPACKAGE_H_
#define IFAULTPACKAGE_H_


namespace Mplane {

/**
 * At present this is just an empty class used for inheritence
 */
class IFaultPackage {
public:
	IFaultPackage() {}
	virtual ~IFaultPackage() {}

} ;

}

#endif /* IFAULTPACKAGE_H_ */
