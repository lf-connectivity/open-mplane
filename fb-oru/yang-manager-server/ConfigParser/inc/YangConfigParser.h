/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfigParser.h
 * \brief     Yang Manger Server configuration file parser
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _INC_CONFIGPARSER_H_
#define _INC_CONFIGPARSER_H_

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "libtinyxml2/tinyxml2.h"

#include "IYangConfigParser.h"
#include "IYangConfig.h"

#include "CommonConfigBase.h"
#include "ConfigDownload.h"

namespace Mplane
{
	class YangConfigParser : public CommonConfigBase, public IYangConfigParser
	{
	public:
		YangConfigParser();

		~YangConfigParser();

		virtual ReturnType::State load(void);

		virtual void show(void){};

		virtual bool isConfigFileLoaded(void);
		virtual void getYangVersion(std::string & yangVersion);
		virtual void getOranVersion(std::string & oranVersion);
		virtual void getProduct(std::string & product);
		virtual void getVarient(std::string & varient);
		virtual void getFormatVersion(std::string & formatVersion);
		virtual void getCompany(std::string & company);

	protected:
		 // Top level extraction methods that are not iterative
		 bool extractModule(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
		 void extractAllFeatures(tinyxml2::XMLElement* node);

	private:
		bool parseConfig(tinyxml2::XMLElement* node) ;

		bool findElementNoAttributes(tinyxml2::XMLElement *node,
				std::string elementType, std::string & elementName );
		bool findElementWithAttributes(tinyxml2::XMLElement *node,
						std::string elementType, std::string & elementName, std::string & elementValue );
		bool findElementAndExtract(tinyxml2::XMLElement *node, std::shared_ptr<IYangElement> parentElement ,
				std::shared_ptr<IYangElement> moduleElement );

		bool getElementType(std::string nodeName, std::string & elementType);

		bool mConfigFileLoaded;

		std::shared_ptr<IYangConfig> mConfig; //!> The pointer to the config
		std::shared_ptr<IYangElement> mFile;
		std::map<std::string, std::map<std::string, bool>> mModuleFeatureMap;

		//XML strings
		static const std::string mXmlRootStr;
		static const std::string mXmlYangVersionStr;
		static const std::string mXmlModuleStr;
		static const std::string mXmlFileVersionStr;
		static const std::string mXmlIfFeatureStr;
		static const std::string mXmlFeatureStr;
		static const std::string mXmlContainerStr;
		static const std::string mXmlSubContainerStr;
		static const std::string mXmlListStr;
		static const std::string mXmlChoiceStr;
		static const std::string mXmlCaseStr;
		static const std::string mXmlListEntryStr;
		static const std::string mXmlLeafStr;
		static const std::string mXmlGeneralStr;
		static const std::string mXmlOranInfoStr;
		static const std::string mXmlProductInfoStr;
		static const std::string mXmlListLeafStr;
		static const std::string mXmlEntryStr;

		static const std::string mXmlElementDelimiterStr;
		static const std::string mXmlModuleFeatureDelimiterStr;
		static const std::string mXmlValueStr;
		static const std::string mXmlAccessStr;
		static const std::string mXmlRefStr;

		static const std::string mXmlOranVersionStr;
		static const std::string mXmlProductStr;
		static const std::string mXmlVarientStr;
		static const std::string mXmlFormatVersionStr;
		static const std::string mXmlCompanyStr;

		static const std::string mElementName;

		std::string mYangVersion; //!> Overall yang version XML config was generated from using the models

		std::string mOranVersion;
		std::string mProduct;
		std::string mVarient;
		std::string mFormatVersion;
		std::string mCompany;

		struct ExtractElements : public Loggable
		{
			ExtractElements( std::map<std::string, std::map<std::string, bool>> featureMap);

			~ExtractElements(){};

		    typedef bool (ExtractElements::*extractMethod)(tinyxml2::XMLElement*, std::shared_ptr<IYangElement>);
		    std::map<std::string, extractMethod> extractMethodMap;
		    std::map<std::string, std::map<std::string, bool>> mFeatureMap;

			bool getElementName(std::string nodeName, std::string & elementName);
			bool getElementType(std::string nodeName, std::string & elementType);
			bool isFeatureEnabled(std::string moduleName, std::string featureName);

			// Extract methods
			bool extractSubContainer(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractList(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractChoice(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractListEntry(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractLeaf(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractListLeaf(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractEntry(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractCase(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractFeature(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);
			bool extractIfFeature(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);

			bool extractCommon(tinyxml2::XMLElement* node, std::shared_ptr<IYangElement> parentElement);

		    int call( const std::string & elementStr, tinyxml2::XMLElement* node,
		    		std::shared_ptr<IYangElement> parentElement)
		    {
		        extractMethod method = extractMethodMap[elementStr];
		        return (this->*method)(node, parentElement);
		    }
		};

		bool callExtractMethod(const std::string nodeName,
				tinyxml2::XMLElement *node,
				std::shared_ptr<IYangElement> parentElement,
				std::shared_ptr<IYangElement> moduleElement);
	};
}


#endif /* _INC_CONFIGPARSER_H_ */
