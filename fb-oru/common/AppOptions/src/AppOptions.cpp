/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppOptions.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include "stringfunc.hpp"
#include "IBootEnv.h"
#include "AppOptions.h"

using namespace Mplane;

//=============================================================================================================
// CLASSES
//=============================================================================================================

// Wrap up the AppOptionSpec class for factory use only
class AppOptionSpecFactory : public AppOptionSpec
{
public:
	AppOptionSpecFactory(const std::string& name, const DataVariantType::Type& type,
			const std::string& description, const std::string& defaultValue, const std::string& useEnvVar) :
		AppOptionSpec(name, type, description, defaultValue, useEnvVar)
	{}

	virtual ~AppOptionSpecFactory() {}

};


// Wrap up the AppOptions class so we can create the singleton (makes the constructor available)
class AppOptionsSingleton : public AppOptions
{
public:
	AppOptionsSingleton(int argc, const char** argv,
			const std::string& applicationDescription,
			const std::vector< std::shared_ptr<IAppOptionSpec> >& optionsSpecification) :
		AppOptions(argc, argv, applicationDescription, optionsSpecification)
	{}

	virtual ~AppOptionsSingleton() {}

};

//=============================================================================================================
// AppOptionSpec - FACTORY
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAppOptionSpec> Mplane::IAppOptionSpec::factory(
		const std::string& name, const DataVariantType::Type& type,
		const std::string& description)
{
	return IAppOptionSpec::factory(name, type, description, "", "") ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAppOptionSpec> Mplane::IAppOptionSpec::factory(
		const std::string& name, const DataVariantType::Type& type,
		const std::string& description, const std::string& defaultValue)
{
	return IAppOptionSpec::factory(name, type, description, defaultValue, "") ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAppOptionSpec> Mplane::IAppOptionSpec::factory(
		const std::string& name, const DataVariantType::Type& type,
		const std::string& description, const std::string& defaultValue,
		const std::string& useEnvVar)
{
	return std::make_shared<AppOptionSpecFactory>(name, type, description, defaultValue, useEnvVar) ;
}

//=============================================================================================================
// AppOptionSpec - PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::AppOptionSpec::~AppOptionSpec()
{
}

//-------------------------------------------------------------------------------------------------------------
DataVariant& Mplane::AppOptionSpec::getData()
{
	return mDataVariant ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::AppOptionSpec::getUseEnv() const
{
	return mUseEnvVar ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::AppOptionSpec::getDefault() const
{
	return mDefault ;
}

//-------------------------------------------------------------------------------------------------------------
std::string Mplane::AppOptionSpec::getDescription() const
{
	return mDescription ;
}

//-------------------------------------------------------------------------------------------------------------
Mplane::AppOptionSpec::AppOptionSpec(const std::string& name,
		const DataVariantType::Type& type, const std::string& description,
		const std::string& defaultValue, const std::string& useEnvVar) :
	mUseEnvVar(useEnvVar),
	mDefault(defaultValue),
	mDescription(description),
	mDataVariant(type, name)
{
	// Special variant for BOOL
	if (mDefault.empty() && mDataVariant.getType() == DataVariantType::Bool)
		mDefault = "false" ;
}

//=============================================================================================================
// AppOptions - SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAppOptions> Mplane::IAppOptions::singleton(int argc,
		const char** argv, const std::string& applicationDescription,
		const std::vector<std::shared_ptr<IAppOptionSpec> >& optionsSpecification)
{
	static std::shared_ptr<IAppOptions> instance(new AppOptionsSingleton(argc, argv, applicationDescription, optionsSpecification)) ;
	return instance ;
}


//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAppOptions> Mplane::IAppOptions::createInstance(int argc,
		const char** argv, const std::string& applicationDescription,
		const std::vector<std::shared_ptr<IAppOptionSpec> >& optionsSpecification)
{
	return AppOptions::singleton(argc, argv, applicationDescription, optionsSpecification) ;
}

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<IAppOptions> Mplane::IAppOptions::getInstance()
{
	return AppOptions::singleton(0, NULL, "", std::vector<std::shared_ptr<IAppOptionSpec> >{}) ;
}


//=============================================================================================================
// AppOptions - PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::AppOptions::~AppOptions()
{
}

//-------------------------------------------------------------------------------------------------------------
const DataVariant Mplane::AppOptions::getOption(const std::string& name) const
{
	auto entry(mOptions.find(name)) ;
	if (entry == mOptions.end())
	{
		std::cerr << "Invalid option name " << name << " aborting" << std::endl ;
		abort() ;
	}

	return entry->second->getData() ;
}


//=============================================================================================================
// AppOptions - PROTECTED
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Mplane::AppOptions::AppOptions(int argc, const char** argv,
		const std::string& applicationDescription,
		const std::vector<std::shared_ptr<IAppOptionSpec> >& optionsSpecification) :
	mDescription(applicationDescription),
	mOptions()
{
	// Process vector into map
	for (auto entry : optionsSpecification)
	{
		DataVariant& dv(entry->getData());
		mOptions[dv.getName()] = entry ;
	}

	// Handle args
	processOptions(argc, argv) ;
}


//=============================================================================================================
// AppOptions - PRIVATE
//=============================================================================================================


//-------------------------------------------------------------------------------------------------------------
void Mplane::AppOptions::processOptions(int argc, const char** argv)
{
	processCmdline(argc, argv) ;
	processEnv() ;
	processDefaults() ;
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::AppOptions::processCmdline(int argc, const char** argv)
{
	if (argv == NULL)
	{
		std::cerr << "AppOptions getInstance() called before createInstance()" << std::endl ;
		abort() ;
	}

	// process arguments
	for (int n=1; n < argc; ++n)
	{
		// Check for option
		std::string arg(argv[n]) ;
		if (arg[0] != '-')
			continue ;

		// handle any "built in" options (help etc)
		std::string name(arg.substr(arg.find_first_not_of('-'))) ;
		if (handleBuiltins(argc, argv, n, name))
			continue ;

		// check option
		auto entry(mOptions.find(name)) ;
		if (entry == mOptions.end())
		{
			std::cerr << "Invalid option '" << arg << "'" << std::endl ;
			exit(1) ;
		}

		// handle option
		handleOption(argc, argv, n, name, entry->second) ;
	}


}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::AppOptions::handleBuiltins(int argc, const char** argv, int& idx, const std::string& name)
{
	if (name == "help")
	{
		// Show help then stop
		std::cout << mDescription << std::endl << std::endl ;
		std::cout << "OPTIONS" << std::endl ;

		// display builtin help
		DataVariant boolDv(DataVariantType::Bool, "dummy") ;
		helpOption("help", boolDv, "Show help") ;
		std::cout << std::endl ;

		// show options
		for (auto entry : mOptions)
		{
			DataVariant& dv(entry.second->getData()) ;
			helpOption(entry.first, dv, entry.second->getDescription(), entry.second->getUseEnv(), entry.second->getDefault()) ;
		}


		exit(0) ;
	}

	return false ;
}

//-------------------------------------------------------------------------------------------------------------
bool Mplane::AppOptions::handleOption(int argc, const char** argv, int& idx, const std::string& name,
		std::shared_ptr<IAppOptionSpec> optionSpec)
{
	DataVariant& dv(optionSpec->getData()) ;
	switch (dv.getType())
	{
		case DataVariantType::String:
		case DataVariantType::Int:
		case DataVariantType::Float:
		case DataVariantType::Enum:
		{
			if (++idx >= argc)
			{
				std::cerr << "Error: Must specify a value for option '" << name << "'" << std::endl ;
				exit(1) ;
			}

			dv.set(argv[idx]) ;
		}
		break ;

		case DataVariantType::Bool:
		{
			// For a boolean option, specifying it inverts the default value
			bool notVal(false) ;
			DataVariant defVal(DataVariantType::Bool, "default", optionSpec->getDefault()) ;
			if (defVal.isSet())
				notVal = defVal.toBool() ;
			dv.set(!notVal) ;
		}
		break ;

		case DataVariantType::None:
		default:
		{
			std::cerr << "AppOptions invalid DataVariant type for option '" << name << "'" << std::endl ;
			abort() ;
		}
		break ;
	}
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
void Mplane::AppOptions::processEnv()
{
	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;

	for (auto entry : mOptions)
	{
		// set any options to their environment value if they haven't been set
		DataVariant& dv(entry.second->getData()) ;
		if (dv.isSet())
			continue ;

		// check environment variable name is set
		std::string envVar(entry.second->getUseEnv()) ;
		if (envVar.empty())
			continue ;

		// Get the u-boot env var
		if ( bootEnv->isVar(envVar) )
		{
			// set value
			dv.set(bootEnv->getVar(envVar)) ;
			continue ;
		}

		// get the value from the system environment - skip if not set
		char* env(::getenv(envVar.c_str())) ;
		if (env)
		{
			// set value
			dv.set(env) ;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::AppOptions::processDefaults()
{
	for (auto entry : mOptions)
	{
		// set any options to their default value if they haven't been set
		DataVariant& dv(entry.second->getData()) ;
		if (dv.isSet())
			continue ;

		// check default is set
		std::string defaultVal(entry.second->getDefault()) ;
		if (defaultVal.empty())
			continue ;

		// set value
		dv.set(defaultVal) ;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Mplane::AppOptions::helpOption(const std::string& name, const DataVariant& dv, const std::string& description,
		const std::string& envVarName, const std::string& defaultValue)
{
	std::string typeStr(dv.getTypeStr()) ;
	if (dv.getType() == DataVariantType::Bool)
		typeStr = "" ;

	// If this option also has an alternate environment variable setting then show it
	std::string envHelp ;
	if (!envVarName.empty())
	{
		envHelp = " [Env variable: " + envVarName + "]" ;
	}

	// If this has a default then show it
	std::string defaultHelp ;
	if (!defaultValue.empty())
	{
		defaultHelp = " [Default: " + defaultValue + "]" ;
	}

	// Show string
	std::cout << padLeft("  --" + name + " " + typeStr, 30) << " " << description << envHelp << defaultHelp << std::endl ;
}
