/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      HandlerCallback.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include "stringfunc.hpp"
#include "YangParamUtils.h"
#include "SysrepoUtils.h"
#include "YangMgrServer.h"
#include "RadioDatastoreSysrepo.h"

#include "YangHandlerSysrepoUnlogged.h"
#include "YangParamSysrepo.h"

#include "YangHandlerSysrepo/HandlerCallback.h"

using namespace Mplane;

//=============================================================================================================
// CONSTANTS
//=============================================================================================================
const unsigned MAX_LEN = 512;


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
HandlerCallback::HandlerCallback(YangHandlerSysrepoUnlogged *parent,
		GetPathsFunc roFunc, SetValFunc setValFunc,
		ChangeCompleteFunc completeFunc) :
	mParent(parent),
	mRoPathsFunc(roFunc),
	mSetValFunc(setValFunc),
	mChangeCompleteFunc(completeFunc)
{
}

//-------------------------------------------------------------------------------------------------------------
HandlerCallback::~HandlerCallback()
{
}

//-------------------------------------------------------------------------------------------------------------
int HandlerCallback::module_change(sysrepo::S_Session sess,
		const char *module_name, const char *xpath, sr_event_t event,
		uint32_t request_id, void *private_data)
{
	std::string xpathString ;
	if (xpath)
		xpathString = std::string(xpath) ;

	// Handle CHANGE events
	if (event == SR_EV_CHANGE)
	{
		// check pseudo read-only
		int rc = checkPseudoReadOnly(sess, module_name, xpathString) ;
		if (rc != SR_ERR_OK)
			return rc ;

		return handleChangeEvent(sess, module_name, xpathString) ;
	}

	// skip anything else other than DONE events
	if (event != SR_EV_DONE)
	{
		return SR_ERR_OK ;
	}

	// Handle DONE events
	return handleDoneEvent(sess, module_name, xpathString) ;
}

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
int HandlerCallback::checkPseudoReadOnly(sysrepo::S_Session sess,
		const char *module_name, const std::string &xpathString)
{
	std::set<std::string> readOnlyPaths(mRoPathsFunc()) ;
	if (readOnlyPaths.empty())
		return SR_ERR_OK ;

	// look at each change and see if any of the values' paths match the read-only set
	try {
		char change_path[MAX_LEN];
		snprintf(change_path, MAX_LEN, "/%s:*//.", module_name);
		auto it = sess->get_changes_iter(change_path);

		std::string valuePath ;
		while (auto change = sess->get_change_next(it))
		{
			switch(change->oper()) {
			case SR_OP_CREATED:
				if (nullptr != change->new_val()) {
					valuePath = std::string(change->new_val()->xpath()) ;
				}
				break;
			case SR_OP_DELETED:
				if (nullptr != change->old_val()) {
					valuePath = std::string(change->old_val()->xpath()) ;
				}
			break;
			case SR_OP_MODIFIED:
				if (nullptr != change->old_val() && nullptr != change->new_val()) {
					valuePath = std::string(change->old_val()->xpath()) ;
				}
			break;
			case SR_OP_MOVED:
				if (nullptr != change->old_val() && nullptr != change->new_val()) {
					valuePath = std::string(change->old_val()->xpath()) ;
				} else if (nullptr != change->new_val()) {
					valuePath = std::string(change->new_val()->xpath()) ;
				}
			break;
			}

			if (!valuePath.empty())
			{
//				std::cerr << "Checking CHANGE on " << valuePath << std::endl ;
				for (auto path : readOnlyPaths)
				{
//					std::cerr << " + " << path << std::endl ;

					// if the start of this value's xpath matches any of the read-only set then negate the change
					if (startsWith(valuePath, path))
					{
//						std::cerr << " + + MATCH: Reject change (Read Only)" << std::endl ;
						mParent->logInfo("Rejected change (Read Only) - '" + valuePath + "'");
						return SR_ERR_VALIDATION_FAILED ;
					}
				}
			}
		}

	} catch( const std::exception& e ) {
		std::cerr << e.what() << std::endl;
	}

	return SR_ERR_OK ;
}

//-------------------------------------------------------------------------------------------------------------
int HandlerCallback::handleChangeEvent(sysrepo::S_Session sess,
		const char *module_name, const std::string &xpathString)
{
	std::shared_ptr<YangParams> params(std::make_shared<YangParams>()) ;
	std::shared_ptr<YangParams> deletedParams(std::make_shared<YangParams>()) ;

	// look at each change and see if any of the values' paths match the read-only set
	try {
		char change_path[MAX_LEN];
		snprintf(change_path, MAX_LEN, "/%s:*//.", module_name);
		auto it = sess->get_changes_iter(change_path);

		std::shared_ptr<YangParam> param ;
		while (auto change = sess->get_change_next(it))
		{
			switch(change->oper()) {
			case SR_OP_CREATED:
				if (nullptr != change->new_val())
					param = std::make_shared<YangParamSysrepo>(change->new_val()) ;
				break;
			case SR_OP_DELETED:
				if (nullptr != change->old_val())
					param = std::make_shared<YangParamSysrepo>(change->old_val()) ;
			break;
			case SR_OP_MODIFIED:
				if (nullptr != change->new_val())
					param = std::make_shared<YangParamSysrepo>(change->new_val()) ;
			break;
			case SR_OP_MOVED:
				if (nullptr != change->new_val())
					param = std::make_shared<YangParamSysrepo>(change->new_val()) ;
			break;
			}

			if (param)
			{
				// skip container etc
				std::string error ;
				if (!YangParamUtils::toString(param, error).empty())
				{
					// If operation is not delete, then add the params to the modified list
					if (change->oper() != SR_OP_DELETED)
					{
						params->addParam(param) ;
					}
					// Else add it to the deleted parameter list
					else
					{
						deletedParams->addParam(param) ;
					}
				}
			}
		}

		// now get parent to validate these changes
		if (params->getNumParams() > 0)
		{
			return mParent->validate(params, deletedParams) ;
		}

	} catch( const std::exception& e ) {
		std::cerr << e.what() << std::endl;
	}
	return SR_ERR_OK ;

//	return SR_ERR_VALIDATION_FAILED ;
}



//-------------------------------------------------------------------------------------------------------------
int HandlerCallback::handleDoneEvent(sysrepo::S_Session sess,
		const char *module_name, const std::string &xpathString)
{
	try {
		char change_path[MAX_LEN];
		snprintf(change_path, MAX_LEN, "/%s:*//.", module_name);
		auto it = sess->get_changes_iter(change_path);

		while (auto change = sess->get_change_next(it))
		{
			switch(change->oper()) {
			case SR_OP_CREATED:
				if (nullptr != change->new_val()) {
//					std::cout <<"CREATED: ";
//					std::cout << change->new_val()->to_string();
					mParent->valueChange(xpathString, std::shared_ptr<YangParam>(),
						   std::make_shared<YangParamSysrepo>(change->new_val())) ;
					mSetValFunc(change->new_val()) ;
				}
				break;
			case SR_OP_DELETED:
				if (nullptr != change->old_val()) {
//					std::cout << "DELETED: ";
//					std::cout << change->old_val()->to_string();,
					mParent->paramDelete(xpathString, std::make_shared<YangParamSysrepo>(change->old_val()));
				}
			break;
			case SR_OP_MODIFIED:
				if (nullptr != change->old_val() && nullptr != change->new_val()) {
//					std::cout << "MODIFIED: ";
//					std::cout << "old value ";
//					std::cout << change->old_val()->to_string();
//					std::cout << "new value ";
//					std::cout << change->new_val()->to_string();
					mParent->valueChange(xpathString, std::make_shared<YangParamSysrepo>(change->old_val()),
						   std::make_shared<YangParamSysrepo>(change->new_val())) ;
					mSetValFunc(change->new_val()) ;
				}
			break;
			case SR_OP_MOVED:
				if (nullptr != change->old_val() && nullptr != change->new_val()) {
//					std::cout << "MOVED: ";
//					std::cout << change->new_val()->xpath();
//					std::cout << " after ";
//					std::cout << change->old_val()->xpath();
					mParent->valueChange(xpathString, std::make_shared<YangParamSysrepo>(change->old_val()),
						   std::make_shared<YangParamSysrepo>(change->new_val())) ;
					mSetValFunc(change->new_val()) ;

				} else if (nullptr != change->new_val()) {
//					std::cout << "MOVED: ";
//					std::cout << change->new_val()->xpath();
					mParent->valueChange(xpathString, std::shared_ptr<YangParam>(),
						   std::make_shared<YangParamSysrepo>(change->new_val())) ;
					mSetValFunc(change->new_val()) ;
				}
			break;
			}
		}

		// finished changes
		mChangeCompleteFunc() ;

	} catch( const std::exception& e ) {
		std::cerr << e.what() << std::endl;
	}
	return SR_ERR_OK;
}
