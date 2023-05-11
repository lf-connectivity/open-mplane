/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SysrepoGetitemsCallback.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <exception>
#include <string>

#include "SysrepoGetitemsCallback.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
SysrepoGetitemsCallback::SysrepoGetitemsCallback(const std::string &parentPath)
: 	sysrepo::Callback()
, LeafContainer()
, mParentPath(parentPath)
{
}

//-------------------------------------------------------------------------------------------------------------
SysrepoGetitemsCallback::~SysrepoGetitemsCallback()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string SysrepoGetitemsCallback::path() const
{
	return mParentPath;
}

//-------------------------------------------------------------------------------------------------------------
int SysrepoGetitemsCallback::oper_get_items(sysrepo::S_Session session,
		const char *module_name, const char *path, const char *request_xpath,
		uint32_t request_id, libyang::S_Data_Node &parent, void *private_data)
{
	sr_error_t srError = SR_ERR_OK;

	//std::cout << "\n\n ========== CALLBACK CALLED TO PROVIDE \"" << mParentPath.c_str() << "\" DATA ==========\n" << std::endl;

	try
	{
		libyang::S_Context ctx = session->get_context();
		libyang::S_Module mod = ctx->get_module(module_name);

		parent.reset(new libyang::Data_Node(ctx, mParentPath.c_str(), nullptr, LYD_ANYDATA_CONSTSTRING, 0));
		processElements(ctx, parent, mod, this);
	}
	catch (std::exception &exception)
	{
		std::string exceptionStr = exception.what();
		std::cerr << "[error] libyang exception: oper_get_items() - " << mParentPath.c_str() << std::endl;
		std::cerr << "[error] " << exceptionStr << std::endl;
		srError = SR_ERR_INTERNAL;
	}

	return srError;
}

//=============================================================================================================
// PROTECTED
//=============================================================================================================

//=============================================================================================================
// PRIVATE
//=============================================================================================================

//#define DISP_ELES(instruction)  instruction
#define DISP_ELES(instruction)

//-------------------------------------------------------------------------------------------------------------
void SysrepoGetitemsCallback::processElements(libyang::S_Context ctx, libyang::S_Data_Node parent, libyang::S_Module mod,
		const ILeafContainer *elementContainer, unsigned level)
{
	DISP_ELES(std::string levelStr(level, '+'));

	for (auto element : elementContainer->contents())
	{
		try
		{
			std::string name(element->name());
			libyang::S_Module module(mod);
			std::string moduleName(nodeModule(name));
			if (!moduleName.empty())
			{
				// Augmented element, so switch to that module
				name = nodeName(name);
				module = ctx->get_module(moduleName.c_str());
			}

			if (element->isContainer())
			{
				DISP_ELES(std::cerr << levelStr << "is container " << element->name() << ":" << std::endl);

				// container - container, list or choice
				libyang::S_Data_Node container(new libyang::Data_Node(parent, module, name.c_str()));
				processElements(ctx, container, module, element.get(), level + 1);
				DISP_ELES(std::cerr << "Process Eleents(ctor) done" << std::endl);
				continue;
			}

			DISP_ELES(std::cerr << levelStr << "leaf" << element->name() << " = " << element->value() << std::endl);
			// leaf
			libyang::S_Data_Node leaf(new libyang::Data_Node(parent, module, name.c_str(), element->value().c_str()));
		}
		catch (std::exception &exception)
		{
			std::string exceptionStr = exception.what();
			std::cerr << "[error] libyang exception: processElements() - " << mParentPath.c_str() << std::endl;
			std::cerr << "[error] " << exceptionStr << std::endl;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
std::string SysrepoGetitemsCallback::nodeModule(const std::string &name)
{
	std::size_t pos(name.find(":"));
	if (pos == std::string::npos)
		return "";

	return name.substr(0, pos);
}

//-------------------------------------------------------------------------------------------------------------
std::string SysrepoGetitemsCallback::nodeName(const std::string &name)
{
	std::size_t pos(name.find(":"));
	if (pos == std::string::npos)
		return name;

	return name.substr(pos + 1);
}
