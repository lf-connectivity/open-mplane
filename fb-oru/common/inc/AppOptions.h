/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      AppOptions.h
 * \brief     Applications options
 *
 *
 * \details
 *
 */


#ifndef AppOptions_H_
#define AppOptions_H_

#include <map>
#include "IAppOptions.h"

namespace Mplane {

class AppOptionSpec : public IAppOptionSpec
{
public:
	virtual ~AppOptionSpec() ;

	/**
	 * Get the option specification data entry
	 * @return DatVariant for this entry
	 */
	virtual DataVariant& getData() override ;

	/**
	 * Get the environment variable name to use for setting this option
	 * @return environment variable name or empty string
	 */
	virtual std::string getUseEnv() const override ;

	/**
	 * Get the default value for this option
	 * @return default value or empty string
	 */
	virtual std::string getDefault() const override ;

	/**
	 * Get the description for this option
	 * @return description
	 */
	virtual std::string getDescription() const override ;

protected:
	AppOptionSpec(const std::string& name, const DataVariantType::Type& type,
			const std::string& description, const std::string& defaultValue, const std::string& useEnvVar) ;

private:
	std::string mUseEnvVar ;
	std::string mDefault ;
	std::string mDescription ;
	DataVariant mDataVariant ;
};

class AppOptions : public IAppOptions
{
public:
	virtual ~AppOptions() ;


	/**
	 * Get the option given by the name
	 * @param name
	 * @return DataVariant containing the option named
	 */
	virtual const DataVariant getOption(const std::string& name) const override ;

protected:
	AppOptions(int argc, const char** argv,
			const std::string& applicationDescription,
			const std::vector< std::shared_ptr<IAppOptionSpec> >& optionsSpecification) ;

protected:
	virtual void processOptions(int argc, const char** argv) ;
	virtual void processCmdline(int argc, const char** argv);
	virtual bool handleBuiltins(int argc, const char** argv, int& idx, const std::string& name);
	virtual bool handleOption(int argc, const char** argv, int& idx, const std::string& name, std::shared_ptr<IAppOptionSpec> optionSpec);
	virtual void processEnv();
	virtual void processDefaults();

	void helpOption(const std::string& name, const DataVariant& dv, const std::string& description,
			const std::string& envVarName = "", const std::string& defaultValue = "") ;

private:
	std::string mDescription ;
	std::map< std::string, std::shared_ptr<IAppOptionSpec> > mOptions ;
} ;

}

#endif /* AppOptions_H_ */
