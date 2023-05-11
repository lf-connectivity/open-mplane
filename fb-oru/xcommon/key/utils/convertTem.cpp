/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      convertTem.cpp
 * \brief     Convert old-style ART test model into new CART format
 *
 *
 * \details
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <string>
#include <iostream>
#include <fstream>

#include <memory>

#include "IWaveFile.h"
#include "ByteTransfer.hpp"
#include "IKey.h"

#include "PlaybackWave.h"

using namespace Mplane ;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
#ifdef _MSC_VER
static const std::string PATHSEP("\\");
#else
static const std::string PATHSEP("/");
#endif


//=============================================================================================================
// TYPES
//=============================================================================================================
struct ConvertOptions {
	bool debug ;
	std::string outdir ;
};

//=============================================================================================================
// LOCAL
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
namespace {

	//---------------------------------------------------------------------------------------------------------
	void showHelp()
	{
		std::cout << ""
		"convertTem\n"
		"\n"
		"Usage:\n"
		"	convertTem [options] -d <output directory> <file> [ <file> .. ]\n"
		"\n"
		"Options:\n"
		"	-h                         This help\n"
		"	-d <dir>                   Set the output directory to write file into\n"
		"\n" ;

		exit(0) ;
	}

	//---------------------------------------------------------------------------------------------------------
	std::vector<std::string> getOptions(ConvertOptions& options, int argc, char **argv)
	{
		options.debug = false ;
		options.outdir.clear() ;

		std::vector<std::string> args ;
		for (unsigned idx=1; idx < (unsigned)argc; ++idx)
		{
			std::string arg(argv[idx]) ;
			if (arg[0] == '-')
			{
				// option
				if (arg == "-d")
				{
					if (++idx < (unsigned)argc)
					{
						options.outdir = argv[idx] ;
					}
				}
				else if (arg == "-h")
				{
					showHelp() ;
					exit(0) ;
				}
			}
			else
			{
				args.push_back(arg) ;
			}
		}

		return args ;
	}


	//---------------------------------------------------------------------------------------------------------
	bool readFile(const std::string& path, std::vector<uint8_t>& data)
	{
		std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate) ;
		if (!file)
			return (false);
		std::streamsize size(file.tellg()) ;
		file.seekg(0, std::ios::beg) ;

		data.resize(size) ;
		if (!file.read((char *)data.data(), size))
			return (false);

		return true ;
	}

}



//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// get the options
	ConvertOptions options ;
	std::vector<std::string> args = getOptions(options, argc, argv) ;
	if ((args.size() < 1) || options.outdir.empty())
		showHelp() ;

	// Get global key
	std::shared_ptr<IKey> key(IKey::getGlobalInstance()) ;

	// Process each filename
	for (auto srcfile : args)
	{
		std::vector<uint8_t> data ;

		if (!readFile(srcfile, data))
		{
			std::cerr << "Unable to read " << srcfile << std::endl ;
			::exit(1) ;
		}

		std::string basename(srcfile) ;
		std::size_t pos(basename.find_last_of("\\/")) ;
		if (pos != std::string::npos)
			basename = basename.substr(pos+1) ;

		std::cout << basename << ": " ;

		// replace existing .art extension with something different to show that the file contents are different.
		// I'll arbitrarily pick .ewf (for Encrypted Waveform File). It shouldn't really matter what it is since it's only
		// the GUI and the embedded SW that will see the filename
		pos = basename.find_last_of(".") ;
		if (pos != std::string::npos)
		{
			basename = basename.substr(0, pos) ;
			basename += ".ewf" ;
		}

		// ENCAPSULATE
		PlaybackWave pbWave(key) ;
		if (!pbWave.encapsulate(basename, data, options.outdir+PATHSEP+basename))
		{
			std::cout << "FAIL" << std::endl ;
			std::cerr << "ERROR: " << pbWave.getError() << std::endl ;
			::exit(1) ;
		}
		std::cout << "Done" << std::endl ;
	}

	return 0 ;
}
