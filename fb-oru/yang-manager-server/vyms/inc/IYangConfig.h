/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangConfig.h
 * \brief     Yang Manger Server configuration virtual interface
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _VYMS_INC_IYANGCONFIG_H_
#define _VYMS_INC_IYANGCONFIG_H_

#include <memory>
#include <string>
#include <map>

#include "GlobalTypeDefs.h"

#include "IYangElement.h"

namespace Mplane
{
	class IYangConfig
	{
	public:
		static std::shared_ptr<IYangConfig> getConfigSingleton(void);		//!> Configuration singleton interface

		// Config status
		virtual bool getConfigLoaded(void) = 0;								//!> Is the configuration loaded
		virtual void setConfigLoaded(bool) = 0;

		// Leaf or list leaf value supporting methods
		virtual std::string getValue(std::string path) = 0;					//!> For a given path, get the value of the leaf or list leaf entry
		virtual std::string getAccess(std::string path) = 0;				//!> For a given path, get the access permissions of the leaf or list leaf entry

		// List the entire config tree
		virtual void listConfigTree(std::string & configTree) = 0;			//!> List the entire config tree

		// Module supporting methods
		virtual bool isModuleSupported(std::string module) = 0;				//!> For a given module string, is it a supported module
		virtual void listSupportedModules(std::string & moduleList) = 0;	//!> List all supported modules.
		virtual std::string getModuleVersion(std::string module) = 0;		//!> Get the module version.
		virtual void listModuleFeatures(std::string module, std::string & featureList) = 0; //!> For a given module string, list all features as a string in the format <featureName>=<featureValue>,...
		virtual void listModuleFeatures(std::string module, std::map<std::string, bool> & featureList) = 0;	//!> For a given module string, list all features along with the enable/disable status.
		virtual bool isModuleFeatureEnabled(std::string module, std::string feature) = 0;		//!> For a given module string, is the feature enabled

		// Choice supporting methods
		virtual std::string getChoiceCaseName(std::string path) = 0;		//!> Get the name of the case that is associated with a choice.

		// List supporting methods
		virtual unsigned int getNumOfListEntries(std::string path) = 0;		//!> Get the number of entries associated with a list

		// List Leaf supporting methods.
		virtual unsigned int getNumOfListLeafEntries(std::string path) = 0;	//!> Get the number of entries associated with a list leaf

		// Config information
		virtual void setYangVersion(std::string yangVersion) = 0;			//!> Set the yang version
		virtual void setOranVersion(std::string oranVersion) = 0;			//!> Set the oran version
		virtual void setProduct(std::string productName) = 0;				//!> Set product name
		virtual void setVariant(std::string productVariant) = 0;			//!> Set product variant
		virtual void setFormatVersion(std::string formatVersion) = 0;		//!> Set format version
		virtual void setCompanyName(std::string companyName) = 0;			//!> Set company name

		virtual std::string getYangVersion(void) = 0;						//!> Get the yang version
		virtual std::string getOranVersion(void) = 0;						//!> Get the oran version
		virtual std::string getProduct(void) = 0;							//!> Get product name
		virtual std::string getVariant(void) = 0;							//!> Get product variant
		virtual std::string getFormatVersion(void) = 0;						//!> Get format version
		virtual std::string getCompanyName(void) = 0;						//!> Get company name

		virtual std::shared_ptr<IYangElement> getConfigFile(void) = 0; 		//!> For internal use with the Parser and Config only.

		virtual ~IYangConfig() {}
	};
}

#endif /* _VYMS_INC_IYANGCONFIG_H_ */
