/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CallbackORanSoftwareMgr.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_ZCU111_FBC_ORANRRH_INC_CALLBACKORANSOFTWAREMGR_H_
#define YANG_ZCU111_FBC_ORANRRH_INC_CALLBACKORANSOFTWAREMGR_H_

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>

#include <map>
#include <string>
#include <vector>

namespace Mplane {

/*!
 * \class  CallbackORanSoftwareMgr
 * \brief
 * \details
 *
 */
class CallbackORanSoftwareMgr : public sysrepo::Callback {
public:
	CallbackORanSoftwareMgr(const std::string & parentPath) ;
	virtual ~CallbackORanSoftwareMgr() ;

	virtual std::string path() const;

	virtual int oper_get_items(sysrepo::S_Session session, const char *module_name, const char *path, const char *request_xpath,
			uint32_t request_id, libyang::S_Data_Node &parent, void *private_data) override ;

private:
	void processElements(libyang::S_Context ctx, libyang::S_Data_Node parent, libyang::S_Module mod) ;


private:
	std::string mParentPath; //!> XPath to the parent node used while creating tree for read-only params

} ;

}

#endif /* YANG_ZCU111_FBC_ORANRRH_INC_CALLBACKORANSOFTWAREMGR_H_ */
