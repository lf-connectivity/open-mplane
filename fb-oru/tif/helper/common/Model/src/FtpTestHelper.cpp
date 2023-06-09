/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FtpTestHelper.cpp
 * \brief     Test helper for common
 *
 *
 * \details   Auto-generated by gentool. Contains test interface definitions. Please add your own
 * code between the %%--> and <--%% comment lines (any code outside these comments will be discarded
 * next time the generate tool is run)
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "RtiKeyword.h"
#include "FtpTestHelper.h"

// Add any specific includes here %%-->
#include <cstdlib>
#include <string>
// <--%%


using namespace Mplane ;

// Add any statics, types, prototypes etc here %%-->

// <--%%



//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<FtpTestHelper> FtpTestHelper::getInstance()
{
	static std::shared_ptr<FtpTestHelper> instance(std::make_shared<FtpTestHelper>()) ;
	return instance ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FtpTestHelper::FtpTestHelper()
// Insert additional inheritance constructors here : %%-->

// <--%%
{
	// Insert your code here : %%-->

	// <--%%
}

//-------------------------------------------------------------------------------------------------------------
FtpTestHelper::~FtpTestHelper()
{
	// Insert your code here : %%-->

	// <--%%
}


//-------------------------------------------------------------------------------------------------------------
void FtpTestHelper::put( IRtiMsgParser& msgParser, DataVariantList *callList, DataVariantList *returnList )
{
	// Called with:
	// * STRING user
	// * STRING pwd
	// * STRING server
	// * STRING filePath
	// Returns:
	// * ENUM(OK:ERROR) Status=OK
	// * [STRING Info]
	// * [STRING Message]
	//

	// Insert your code here : %%-->

	std::string cmd;
	std::string user = callList->find("user")->toString();
	std::string pwd = callList->find("pwd")->toString();
	std::string server = callList->find("server")->toString();
	std::string filePath = callList->find("filePath")->toString();

	auto found = filePath.find_last_of('/');
	std::string fileName = filePath.substr(found + 1);

	// Create the PTP start command and redirect output to a file
	cmd = "ftpput -u " +  user + " -p " + pwd + " " + server + " " + fileName + " " + filePath;

	int processReturn = system(cmd.c_str());

	// Check to see if the command was successful
	if (processReturn != 0)
	{
		// set an error
		returnList->find(RtiKeyword::STATUS_VAR)->set( RtiKeyword::StatusERROR );
		returnList->find(RtiKeyword::MESSAGE_VAR)->set("File transfer failed") ;
		return ;
	}
	// <--%%
}










// Add any statics, private methods etc here %%-->


// <--%%
