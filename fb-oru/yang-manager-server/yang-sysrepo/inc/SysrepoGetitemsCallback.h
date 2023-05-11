/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SysrepoGetitemsCallback.h
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


#ifndef YANG_SYSREPO_INC_SYSREPOGETITEMSCALLBACK_H_
#define YANG_SYSREPO_INC_SYSREPOGETITEMSCALLBACK_H_

#include <sysrepo-cpp/Connection.hpp>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Sysrepo.hpp>

#include <map>
#include <string>
#include <vector>

#include "LeafContainer.h"

namespace Mplane {

/*!
 * \class  SysrepoGetitemsCallback
 * \brief
 * \details
 *
 */
class SysrepoGetitemsCallback : public sysrepo::Callback, public LeafContainer {
public:
	SysrepoGetitemsCallback(const std::string & parentPath) ;
	virtual ~SysrepoGetitemsCallback() ;

	virtual std::string path() const;

	virtual int oper_get_items(sysrepo::S_Session session, const char *module_name, const char *path, const char *request_xpath,
			uint32_t request_id, libyang::S_Data_Node &parent, void *private_data) override ;

private:
	void processElements(libyang::S_Context ctx, libyang::S_Data_Node parent, libyang::S_Module mod,
			const ILeafContainer* element, unsigned level=0) ;

	// Given a node name of the form: "o-ran-hardware:product-code" returns "o-ran-hardware". If name has no ':' then returns
	// empty string
	static std::string nodeModule(const std::string& name) ;

	// Given a node name of the form: "o-ran-hardware:product-code" returns "product-code". If name has no ':' then returns
	// name string
	static std::string nodeName(const std::string& name) ;

private:
	std::string mParentPath; //!> XPath to the parent node used while creating tree for read-only params
} ;

}

#endif /* YANG_SYSREPO_INC_SYSREPOGETITEMSCALLBACK_H_ */
