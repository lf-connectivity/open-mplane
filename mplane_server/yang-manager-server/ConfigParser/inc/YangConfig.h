/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfig.h
 * \brief     Yang Manger Server configuration class
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _INC_YANG_CONFIG_H_
#define _INC_YANG_CONFIG_H_

#include <string>
#include <memory>
#include <vector>

#include "Loggable.h"

#include "IYangConfig.h"
#include "YangElement.h"

namespace Mplane
{
class YangConfig : public IYangConfig, public Loggable {

 public:
  YangConfig();

  virtual ~YangConfig() {}

  virtual bool getConfigLoaded(void); //!> Is the configuration loaded
  virtual void setConfigLoaded(bool configLoaded);

  virtual std::string getValue(std::string path); //!> For a given path, get the
                                                  //! value of the leaf or list
                                                  //! leaf entry
  virtual std::string getAccess(std::string path); //!> For a given path, get
                                                   //! the access permissions of
                                                   //! the leaf or list leaf
                                                   //! entry

  virtual void listConfigTree(std::string& configTree); //!> List the entire
                                                        //! config tree

  virtual bool isModuleSupported(std::string module); //!> For a given module
                                                      //! string, is it a
                                                      //! supported module
  virtual void listSupportedModules(std::string& moduleList); //!> List all
                                                              //! supported
                                                              //! modules.
  virtual std::string getModuleVersion(std::string module); //!> Get the module
                                                            //! version number
  virtual void listModuleFeatures(
      std::string module,
      std::map<std::string, bool>& featureList); //!> For a given module string,
                                                 //! list all features along
                                                 //! with the enable/disable
                                                 //! status.
  virtual void listModuleFeatures(
      std::string module,
      std::string& featureList); //!> For a given module string, list all
                                 //! features as a string in the format
                                 //!< featureName>=<featureValue>,...
  virtual bool isModuleFeatureEnabled(
      std::string module, std::string feature); //!> For a given module string,
                                                //! is the feature enabled

  virtual std::string getChoiceCaseName(std::string path); //!> Get the name  of
                                                           //! the case for a
                                                           //! choice

  virtual unsigned int getNumOfListEntries(
      std::string path); //!> Get the number of entries for a list
  virtual unsigned int getNumOfListLeafEntries(
      std::string path); //!> Get the number of entries for a list leaf

  // Config information
  virtual void setYangVersion(std::string yangVersion); //!> Set the yang
                                                        //! version
  virtual void setOranVersion(std::string oranVersion); //!> Set the oran
                                                        //! version
  virtual void setProduct(std::string productName); //!> Set product name
  virtual void setVariant(std::string productVariant); //!> Set product variant
  virtual void setFormatVersion(std::string formatVersion); //!> Set format
                                                            //! version
  virtual void setCompanyName(std::string companyName); //!> Set company name

  virtual std::string getYangVersion(void); //!> Get the yang version
  virtual std::string getOranVersion(void); //!> Get the oran version
  virtual std::string getProduct(void); //!> Get product name
  virtual std::string getVariant(void); //!> Get product variant
  virtual std::string getFormatVersion(void); //!> Get format version
  virtual std::string getCompanyName(void); //!> Get company name

  virtual std::shared_ptr<IYangElement> getConfigFile(
      void); //!> Get configuration file top level configuration element

 private:
  std::shared_ptr<IYangElement> mConfig; //!> Top level configuration element

  static const std::string typeNameDelimiterStr; //!> Defintion of the delimiter
                                                 //! between the type and name -
                                                 //!"-"
  static const std::string pathDelimiterStr; //!> Definition of the path
                                             //! delimiter - "/"
  static const std::string listDelimiterStr; //!> Definition of the list index
                                             //! delimiter - "["

  static const std::string leafStr; //!> Definition of the leaf string - "leaf"
  static const std::string listStr; //!> Definition of the list string - "list"
  static const std::string listEntryStr; //!> Definition of the list Entry
                                         //! string - "listEntry"
  static const std::string listLeafStr; //!> Definition of the list leaf string
                                        //!- "listLeaf"
  static const std::string entryStr; //!> Definition of the entry string -
                                     //!"entry"
  static const std::string moduleStr; //!> Definition of the module string -
                                      //!"module"
  static const std::string choiceStr; //!> Definition of the choice string -
                                      //!"choice"
  static const std::string caseStr; //!> Definition of the case string - "case"
  static const std::string featureStr; //!> Definition of the feature string -
                                       //!"feature"

  bool mIsConfigLoaded; //!> Member variable to store the config loaded state

  std::string mYangVersion; //!> Member variable to store the yang version
  std::string mOranVersion; //!> Member variable to store the ORAN version
  std::string mProductName; //!> Member variable to store the product name
  std::string mVarientName; //!> Member variable to store the variant name
  std::string mFormatVersion; //!> Member variable to store the file format
                              //! version
  std::string mCompanyName; //!> Member variable to store the company name

  void commonSearch(
      std::shared_ptr<IYangElement> elementSearch,
      std::string& path,
      bool& foundListDelimiter,
      std::shared_ptr<IYangElement>& elementFound,
      std::string& type,
      std::string& index,
      std::size_t& pathDelimiterPos); //!> Common search method

  unsigned int commonGetNumEntries(
      std::string path,
      std::string elementType); //!> Common get number of entries

  void commonGet(
      std::string path,
      std::string& value,
      std::string& access); //!> Common get for values and access attributes.

  void recursiveElementSearch(
      std::shared_ptr<IYangElement> parentElement,
      std::string& resultString,
      unsigned int indent);
};
}



#endif /* _VYMS_INC_YANG_CONFIG_H_ */
