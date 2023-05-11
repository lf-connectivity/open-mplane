/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangConfigParser.h
 * \brief     Yang Manger Server configuration file parser virtual interface
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _VYMS_INC_IYANGCONFIGPARSER_H_
#define _VYMS_INC_IYANGCONFIGPARSER_H_

#include <memory>

#include "GlobalTypeDefs.h"

namespace Mplane
{
class IYangConfigParser {
 public:
  virtual ReturnType::State load(void) = 0; //!> Load the configuration file

  virtual bool isConfigFileLoaded(void) = 0; //!> Has the config file loaded
                                             //! completely with no errors

  virtual void getYangVersion(std::string& yangVersion) = 0; //!> Get the YANG
                                                             //! format version
  virtual void getOranVersion(std::string& oranVersion) = 0; //!> Get the ORAN
                                                             //! version used to
                                                             //! generate the
                                                             //! config xml
  virtual void getProduct(std::string& product) = 0; //!> Get the produce name
  virtual void getVarient(std::string& variant) = 0; //!> Get the
                                                     //! product
                                                     //! variant
  virtual void getFormatVersion(std::string& formatVersion) = 0; //!> Get the
                                                                 //! format
                                                                 //! version
                                                                 //! of the xml
  virtual void getCompany(std::string& company) = 0; //!> Get the company that
                                                     //! provided the config xml

  virtual ~IYangConfigParser() {}
};
}

#endif /* _VYMS_INC_IYANGCONFIGPARSER_H_ */
