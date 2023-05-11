/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangConfigParser_unittest.cpp
 * \brief     YANG configuration parser unit tests
 *
 *
 * \details   YANG configuration parser unit tests
 *
 */

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <iostream>
#include <memory>

#include "IConfigCoordinator.h"
#include "IYangConfigParser.h"
#include "IYangConfig.h"

#include "YangConfigParser.h"
#include "YangConfigDownload.h"
#include "YangConfig.h"

using namespace Mplane;

class TestYangMakeElements : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
        Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_NORMAL, "YANG") ;

        std::cout << test_info->name() << " - SETUP complete" << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here

	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}
protected:

private:
};

TEST_F(TestYangMakeElements, basicMakeElements)
{
	std::shared_ptr <IYangElement> module1( IYangElement::makeElement("module", "first"));

	std::shared_ptr <IYangElement> leaf( IYangElement::makeElement("leaf", "first", "1"));

	module1->addChildElement(leaf);

	std::shared_ptr <IYangElement> container( IYangElement::makeElement("container", "first"));

	module1->addChildElement(container);

	std::shared_ptr <IYangElement> list( IYangElement::makeElement("list", "first"));

	container->addChildElement(list);

	std::shared_ptr <IYangElement> listLeaf1( IYangElement::makeElement("leaf1", "first", "1"));
	std::shared_ptr <IYangElement> listLeaf2( IYangElement::makeElement("leaf2", "second", "2"));

	list->addChildElement(listLeaf1);
	list->addChildElement(listLeaf2);

	std::shared_ptr <IYangElement> foundLeaf = module1->getElement("leaf", "first");

	std::cout << "Leaf value = " << foundLeaf->getValue() << std::endl;

	ASSERT_EQ(foundLeaf->getValue(), "1");

	std::shared_ptr <IYangElement> foundContainer = module1->getElement("container", "first");
	std::shared_ptr <IYangElement> foundList = foundContainer->getElement("list", "first");
	std::shared_ptr <IYangElement> foundListLeaf = foundList->getElement("leaf2", "second");

	std::cout << "Leaf value = " << foundListLeaf->getValue() << std::endl;

	ASSERT_EQ(foundListLeaf->getValue(), "2");
}

TEST_F(TestYangMakeElements, makeElementsFromConfigFile)
{
	std::shared_ptr<IYangConfig> configuration(IYangConfig::getConfigSingleton());

	std::shared_ptr<IYangElement> file(configuration->getConfigFile());

	std::shared_ptr <IYangElement> module1( IYangElement::makeElement("module", "first"));

	file->addChildElement(module1);

	std::string elementList;
	file->listElements(elementList);

	std::cout << elementList << std::endl;

	ASSERT_EQ(file->getNumberOfChildElements(), (unsigned int)1);

	std::shared_ptr <IYangElement> leaf( IYangElement::makeElement("leaf", "first", "1"));

	module1->addChildElement(leaf);

	std::shared_ptr <IYangElement> container( IYangElement::makeElement("container", "first"));

	module1->addChildElement(container);

	std::shared_ptr <IYangElement> list( IYangElement::makeElement("list", "first"));

	container->addChildElement(list);

	std::shared_ptr <IYangElement> listLeaf1( IYangElement::makeElement("leaf1", "first", "1"));
	std::shared_ptr <IYangElement> listLeaf2( IYangElement::makeElement("leaf2", "second", "2"));

	list->addChildElement(listLeaf1);
	list->addChildElement(listLeaf2);

	ASSERT_EQ(list->getNumberOfChildElements(), (unsigned int)2);

	std::shared_ptr <IYangElement> foundLeaf = module1->getElement("leaf", "first");

	std::cout << "Leaf value = " << foundLeaf->getValue() << std::endl;

	ASSERT_EQ(foundLeaf->getValue(), "1");

	std::shared_ptr <IYangElement> foundContainer = module1->getElement("container", "first");
	std::shared_ptr <IYangElement> foundList = foundContainer->getElement("list", "first");
	std::shared_ptr <IYangElement> foundListLeaf = foundList->getElement("leaf2", "second");

	std::cout << "Leaf value = " << foundListLeaf->getValue() << std::endl;

	ASSERT_EQ(foundListLeaf->getValue(), "2");

	//configuration->clearConfigTree();
}

class TestFromConfigFile : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        const ::testing::TestInfo* const test_info =
                ::testing::UnitTest::GetInstance()->current_test_info();

        std::cout << std::endl << "*** " << test_info->test_case_name()
                << " Tests ***" << std::endl;
        std::cout << test_info->name() << " - SETUP" << std::endl;

        // Do the setup here
		std::shared_ptr<IConfigDownload> mYangConfigDownload( std::make_shared<YangConfigDownload>() );
		std::shared_ptr<YangConfigParser> mYangConfigParser(std::make_shared<YangConfigParser>());

	    // Get the instance of configuration coordinator
	    std::shared_ptr<IConfigCoordinator> configCoord = IConfigCoordinator::singleton();

	    // Register the Yang config download and Yang config parser with the coordinator
	    configCoord->registerConfig(mYangConfigDownload, mYangConfigParser);

		// Tell config download manager to change the root install directory.
		std::string failReason ;
		mYangConfigDownload->testInjectInstallDir("../../../ConfigParser/gtest/config", failReason) ;
		mYangConfigDownload->setInstallFileName("YangConfig.xml",failReason);

		// Load the configuration file
		ReturnType::State returnType = configCoord->load(mYangConfigDownload->getName());

		// Check the return type of the load to make sure it is successful
		ASSERT_EQ(returnType, ReturnType::RT_OK);

        std::cout << test_info->name() << " - SETUP complete " << std::endl;
    }

    virtual void TearDown()
	{
	  const ::testing::TestInfo* const test_info =
			  ::testing::UnitTest::GetInstance()->current_test_info();

	  std::cout << test_info->name() << " - TEARDOWN" << std::endl;

	  // Do the tear down here

	  std::cout << test_info->name() << " - TEARDOWN complete" << std::endl;
	}
protected:

private:
};

TEST_F(TestFromConfigFile, TestFromSingleton)
{
	std::shared_ptr<IYangConfig> config = IYangConfig::getConfigSingleton();
	std::shared_ptr<IYangElement> file = config->getConfigFile();

	std::shared_ptr<IYangElement> module = file->getElement("module", "o-ran-ald-port");
	ASSERT_FALSE(nullptr == module);

	bool isModuleSupported = config->isModuleSupported("o-ran-dhcp");
	ASSERT_TRUE(isModuleSupported);

	std::string moduleVersion;
	moduleVersion = config->getModuleVersion("o-ran-dhcp");
	ASSERT_TRUE("1.0" == moduleVersion);

	std::string moduleList = "\0";
	config->listSupportedModules(moduleList);
	std::cout << "Module List - " << moduleList << std::endl;
	ASSERT_NE("\0", moduleList);

	std::string leafvalue = "\0";
	leafvalue =	config->getValue("module-o-ran-ald-port/container-ald-ports-io/leaf-over-current-supported");
	std::cout << "leaf value is - " << leafvalue << std::endl;
	ASSERT_EQ("false", leafvalue);

	leafvalue =	config->getValue("module-o-ran-ald-port/container-ald-ports-io/list-ald-port[0]/leaf-port-id");
	std::cout << "leaf value is - " << leafvalue << std::endl;
	ASSERT_EQ("0", leafvalue);

	leafvalue =	config->getValue("module-o-ran-ald-port/container-ald-ports-io/list-ald-port[1]/leaf-port-id");
	std::cout << "leaf value is - " << leafvalue << std::endl;
	ASSERT_EQ("1", leafvalue);

	leafvalue =	config->getValue("module-o-ran-ald-port/container-ald-ports-io/list-ald-port[2]/leaf-port-id");
	std::cout << "leaf value is - " << leafvalue << std::endl;
	ASSERT_EQ("\0", leafvalue);

	leafvalue =	config->getValue("module-o-ran-dhcp/container-dhcp/list-interfaces[0]/container-dhcpv6/container-dhcp-client-identifier/choice-duid-type/case-duid-en/leaf-duid-en-enterprise-number");
	std::cout << "leaf value is - " << leafvalue << std::endl;
	ASSERT_EQ("10531089", leafvalue);

	std::string leafaccess = "\0";
	leafaccess = config->getAccess("module-o-ran-dhcp/container-dhcp/list-interfaces[0]/container-dhcpv6/container-dhcp-client-identifier/choice-duid-type/case-duid-en/leaf-duid-en-enterprise-number");
	std::cout << "leaf access permissions are - " << leafaccess << std::endl;
	ASSERT_EQ("rw", leafaccess);

	leafaccess = config->getAccess("module-o-ran-software-management/container-software-inventory/list-software-slot[0]/leaf-status");
	std::cout << "leaf access permissions are - " << leafaccess << std::endl;
	ASSERT_EQ("ro", leafaccess);

	std::string entryValue;
	entryValue = config->getValue("module-o-ran-dhcp/container-dhcp/list-interfaces[0]/container-dhcpv4/listLeaf-domain-name-servers[0]");
	ASSERT_TRUE("DNS-Swindon" == entryValue);

	unsigned int numberOfListEntries;
	numberOfListEntries = config->getNumOfListEntries("module-o-ran-dhcp/container-dhcp/list-interfaces");
	ASSERT_TRUE((unsigned int)1 == numberOfListEntries);

	unsigned int numberOfListLeafEntries;
	numberOfListLeafEntries = config->getNumOfListLeafEntries("module-o-ran-dhcp/container-dhcp/list-interfaces[0]/container-dhcpv4/listLeaf-domain-name-servers");
	ASSERT_EQ((unsigned int)2, numberOfListLeafEntries);

	std::string caseName;
	caseName =	config->getChoiceCaseName("module-o-ran-dhcp/container-dhcp/list-interfaces[0]/container-dhcpv6/container-dhcp-client-identifier/choice-duid-type");
	ASSERT_TRUE("duid-en" == caseName);

	ASSERT_TRUE(config->isModuleFeatureEnabled("o-ran-interfaces", "ALIASMAC-BASED-CU-PLANE"));
	ASSERT_FALSE(config->isModuleFeatureEnabled("o-ran-ald-port", "OVERCURRENT-SUPPORTED"));
	ASSERT_TRUE(config->isModuleFeatureEnabled("ietf-hardware", "hardware-state"));
	ASSERT_TRUE(config->isModuleFeatureEnabled("ietf-hardware", "hardware-sensor"));
	ASSERT_FALSE(config->isModuleFeatureEnabled("ietf-hardware", "entity-mib"));

	entryValue = config->getValue("module-ietf-hardware/container-hardware/list-component[0]/container-state/leaf-oper-state");
	ASSERT_TRUE("active" == entryValue);

	entryValue = config->getValue("module-ietf-hardware/container-hardware/list-component[0]/container-state/leaf-power-state");
	ASSERT_TRUE("\0" == entryValue);

	entryValue = config->getValue("module-ietf-interfaces/container-interfaces/list-interface[0]/leaf-link-up-down-trap-enable");
	ASSERT_TRUE("enabled" == entryValue);

	std::map<std::string, bool> featureMap;
	config->listModuleFeatures("o-ran-performance-management", featureMap);
	ASSERT_EQ(featureMap.size(), (unsigned int)2);
	ASSERT_EQ(featureMap["GRANULARITY-TRANSPORT-MEASUREMENT"], false);
	ASSERT_EQ(featureMap["GRANULARITY-EAXC-ID-MEASUREMENT"], true);

	featureMap.clear();
	config->listModuleFeatures("ietf-interfaces", featureMap);
	ASSERT_EQ(featureMap.size(), (unsigned int)3);
	ASSERT_EQ(featureMap["arbitrary-names"], false);
	ASSERT_EQ(featureMap["pre-provisioning"], false);
	ASSERT_EQ(featureMap["if-mib"], true);

	std::string configTree;
	config->listConfigTree(configTree);
	ASSERT_NE(std::string::npos, configTree.size());
	ASSERT_NE((long unsigned int)0, configTree.size());

}
