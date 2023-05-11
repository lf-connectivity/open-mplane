/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      I2cEnv.cpp
 * \brief
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <iostream>
#include <fstream>

//#include "ILoggable.h"
#include "IBootEnv.h"

using namespace Mplane ;

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

	//---------------------------------------------------------------------------------------------------------
	int handleRead(std::shared_ptr<IBootEnv> bootEnv, const std::vector<std::string>& args)
	{
		std::vector<std::string> vars(args) ;
		if (vars.empty())
		{
			// show all
			std::map<std::string, std::string> env(bootEnv->getVars()) ;
			for (auto entry : env)
				vars.push_back(entry.first) ;
		}

		for (auto var : vars)
		{
			std::string val(bootEnv->getVar(var)) ;
			std::cout << var << "=" << val << std::endl ;
		}

		return 0 ;
	}

	//---------------------------------------------------------------------------------------------------------
	int handleWrite(std::shared_ptr<IBootEnv> bootEnv, const std::vector<std::string>& args)
	{
		std::map<std::string, std::string> settings ;
		std::vector<std::string> names ;
		for (auto varval : args)
		{
			std::size_t pos(varval.find('=')) ;
			if (pos == std::string::npos)
				continue ;

			settings[varval.substr(0, pos)] = varval.substr(pos+1) ;
			names.push_back(varval.substr(0, pos)) ;
		}
		if (settings.empty())
		{
			std::cerr << "Error: Must specify at least one variable=value pair" << std::endl ;
			return 1 ;
		}

		// write new values
		if (!bootEnv->setVar(settings))
		{
			std::cerr << "Error: " << bootEnv->getError() << std::endl ;
			return 1 ;
		}

		// ok, so show the current settings
		bootEnv->read() ;
		handleRead(bootEnv, names) ;

		return 0 ;
	}

	//---------------------------------------------------------------------------------------------------------
	int handleErase(std::shared_ptr<IBootEnv> bootEnv)
	{
		// write new values
		if (!bootEnv->resetVars(std::map<std::string, std::string>{}))
		{
			std::cerr << "Error: " << bootEnv->getError() << std::endl ;
			return 1 ;
		}

		return 0 ;
	}

	//---------------------------------------------------------------------------------------------------------
	int handleLoad(std::shared_ptr<IBootEnv> bootEnv, const std::string& filename)
	{
		std::ifstream file(filename) ;
		if (!file.is_open())
		{
			std::cerr << "Error: Unable to read " << filename << std::endl ;
			return 1 ;
		}

		std::map<std::string, std::string> settings ;
		std::vector<std::string> names ;
		std::string line ;
		while (std::getline(file, line))
		{
			std::size_t pos(line.find('=')) ;
			if (pos == std::string::npos)
				continue ;

			settings[line.substr(0, pos)] = line.substr(pos+1) ;
			names.push_back(line.substr(0, pos)) ;
		}
		file.close() ;

		if (settings.empty())
		{
			std::cerr << "Error: Must specify at least one variable=value pair" << std::endl ;
			return 1 ;
		}

		// write new values
		if (!bootEnv->setVar(settings))
		{
			std::cerr << "Error: " << bootEnv->getError() << std::endl ;
			return 1 ;
		}

		// ok, so show the current settings
		bootEnv->read() ;
		handleRead(bootEnv, names) ;

		return 0 ;
	}

	//---------------------------------------------------------------------------------------------------------
	void help(char* const* argv)
	{
		std::cerr << argv[0] << " [options]" << std::endl ;
		std::cerr << "Options:" << std::endl ;
		std::cerr << " -h                  Help" << std::endl ;
		std::cerr << " -W <var>=<value>    Write variable" << std::endl ;
		std::cerr << " -f <file>           Load values from file" << std::endl ;
		std::cerr << " -x                  Erase all values" << std::endl ;
	}
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main(int argc, char* const* argv)
{
	// Process args
    int c;
    bool debug = false;
    bool doWrite = false ;
    bool doErase = false ;
    std::string filename ;
    while ((c = getopt(argc, argv, "Wdhf:x")) != -1)
    {
		switch (c)
		{
			case 'W':
			doWrite = true;
			break;

			case 'd':
			debug = true;
			break;

			case 'f':
			filename = std::string(optarg) ;
			break ;

			case 'x':
			doErase = true ;
			break ;

			case 'h':
			help(argv) ;
			return 0 ;
			break ;

			default:
			fprintf(stderr, "Invalid option %c\n", c);
			help(argv) ;
			exit(1);
		}
    }


//	if (debug)
//		Mplane::ILoggable::setGroupLogDebugLevel(Mplane::ILoggable::LOG_DEBUG_VERBOSE, "BootEnv") ;

	std::shared_ptr<IBootEnv> bootEnv(IBootEnv::getInstance()) ;

	if (debug)
		std::cout << "Active env : [" << bootEnv->getIndex() << "] " <<
				bootEnv->getDeviceName() << " (" <<
				( bootEnv->isValid() ? "Valid" : "INVALID") << ")" <<
				std::endl ;


    argc -= optind;
    char* const* ap = argv + optind;

    std::vector<std::string> args ;
	for ( ; ap && *ap; ++ap)
	{
		args.push_back(*ap) ;
	}

	// Handle erase
	if (doErase)
	{
		return handleErase(bootEnv) ;
	}

	// Handle read from file
	if (!filename.empty())
	{
		return handleLoad(bootEnv, filename) ;
	}


	// Read/Write
	if (!doWrite)
		return handleRead(bootEnv, args) ;
	else
		return handleWrite(bootEnv, args) ;

	return 0 ;
}

