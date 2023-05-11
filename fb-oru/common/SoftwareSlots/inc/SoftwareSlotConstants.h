/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SoftwareSlotConstants.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef SOFTWARESLOTS_INC_SOFTWARESLOTCONSTANTS_H_
#define SOFTWARESLOTS_INC_SOFTWARESLOTCONSTANTS_H_

#include <string>

namespace Mplane {

/*!
 * \class  SoftwareSlotConstants
 * \brief
 * \details
 *
 */
class SoftwareSlotConstants {
public:
	static unsigned DefaultNumSlots ;
	static std::string MgmtDir ;
	static std::string ManifestsSubdir ;
	static std::string SlotsSubdir ;
	static std::string InvalidSubdir ;
	static std::string ReadonlySubdir ;
} ;

}

#endif /* SOFTWARESLOTS_INC_SOFTWARESLOTCONSTANTS_H_ */
