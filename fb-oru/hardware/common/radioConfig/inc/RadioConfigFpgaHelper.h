/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RadioConfigFpgaHelper.h
 * \brief     Helper class for RadioConfig
 *
 *
 * \details   Uses the FPGA settings to configure the RadioConfig
 *
 */


#ifndef COMMON_RADIOCONFIG_INC_RADIOCONFIGFPGAHELPER_H_
#define COMMON_RADIOCONFIG_INC_RADIOCONFIGFPGAHELPER_H_


namespace Mplane {

/*!
 * \class  RadioConfigFpgaHelper
 * \brief
 * \details
 *
 */
class RadioConfigFpgaHelper {
public:
	/**
	 * Use the fpga registers to determine various limits and apply them to the RadioConfig
	 */
	static bool applyFpgaLimits() ;
} ;

}

#endif /* COMMON_RADIOCONFIG_INC_RADIOCONFIGFPGAHELPER_H_ */
