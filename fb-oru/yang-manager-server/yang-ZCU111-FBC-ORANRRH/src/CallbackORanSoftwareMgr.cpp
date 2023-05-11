/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      CallbackORanSoftwareMgr.cpp
 * \brief     <one-line description of file>
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */


//#define BENCHMARK

//=============================================================================================================
// INCLUDE
//=============================================================================================================
#ifdef BENCHMARK
#include <iostream>
#include "Benchmark.h"
#endif

#include "ISoftwareSlotMgr.h"

#include "CallbackORanSoftwareMgr.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

#ifdef BENCHMARK
#define BENCH_START(nm)		Benchmark::getInstance()->start(nm)
#define BENCH_ELAPSED(nm)	Benchmark::getInstance()->elapsed(nm)
#define BENCH_SHOW	std::cerr << "TIMING "
#else
#define BENCH_START(nm)
#define BENCH_ELAPSED(nm)	""
#define BENCH_SHOW			if (0) std::cerr
#endif

//-------------------------------------------------------------------------------------------------------------
CallbackORanSoftwareMgr::CallbackORanSoftwareMgr(const std::string &parentPath) :
	mParentPath(parentPath)
{
	// Ensure software manager is created so that all of it's initialisation is complete before we start interrogating it
	std::shared_ptr<ISoftwareSlotMgr> mgr(ISoftwareSlotMgr::singleton()) ;
	(void)mgr ;
}

//-------------------------------------------------------------------------------------------------------------
CallbackORanSoftwareMgr::~CallbackORanSoftwareMgr()
{
}

//-------------------------------------------------------------------------------------------------------------
std::string CallbackORanSoftwareMgr::path() const
{
	return mParentPath ;
}

//-------------------------------------------------------------------------------------------------------------
int CallbackORanSoftwareMgr::oper_get_items(sysrepo::S_Session session,
		const char *module_name, const char *path, const char *request_xpath,
		uint32_t request_id, libyang::S_Data_Node &parent, void *private_data)
{
	sr_error_t srError = SR_ERR_OK;

	try
	{
		libyang::S_Context ctx = session->get_context();
		libyang::S_Module mod = ctx->get_module(module_name);

		parent.reset(new libyang::Data_Node(ctx, mParentPath.c_str(), nullptr, LYD_ANYDATA_CONSTSTRING, 0));
		processElements(ctx, parent, mod);
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
// PRIVATE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void CallbackORanSoftwareMgr::processElements(libyang::S_Context ctx, libyang::S_Data_Node parent, libyang::S_Module mod)
{
//	module: o-ran-software-management
//	  +--ro software-inventory
//	     +--ro software-slot* [name]
//	        +--ro name             string
//	        +--ro status           enumeration
//	        +--ro active?          boolean
//	        +--ro running?         boolean
//	        +--ro access?          enumeration <READ_WRITE>
//	        +--ro product-code?    -> /ietf-hardware:hardware/ietf-hardware:component/o-ran-hardware:product-code
//	        +--ro vendor-code?     string
//	        +--ro build-id?        string
//	        +--ro build-name?      string
//	        +--ro build-version?   string
//	        +--ro files* [name]
//	           +--ro name          string
//	           +--ro version?      string
//	           +--ro local-path    string
//	           +--ro integrity?    enumeration

BENCH_START("allSlots") ;


	std::shared_ptr<ISoftwareSlotMgr> mgr(ISoftwareSlotMgr::singleton()) ;
	std::vector<std::shared_ptr<ISoftwareSlot>> slots(mgr->slots()) ;

	for (auto slot : slots)
	{
BENCH_START("slot") ;

		std::string statusStr("EMPTY") ;
		if (slot->isAllocated())
		{
			if (slot->isValid())
				statusStr = "VALID" ;
			else
				statusStr = "INVALID" ;
		}
		libyang::S_Data_Node lyslot(new libyang::Data_Node(parent, mod, "software-slot"));

		libyang::S_Data_Node name(new libyang::Data_Node(lyslot, mod, "name", slot->name().c_str()));
		libyang::S_Data_Node status(new libyang::Data_Node(lyslot, mod, "status", statusStr.c_str()));
		libyang::S_Data_Node active(new libyang::Data_Node(lyslot, mod, "active", (slot->isActive() ? "true" : "false") ));
		libyang::S_Data_Node running(new libyang::Data_Node(lyslot, mod, "running", (slot->isRunning() ? "true" : "false") ));
		libyang::S_Data_Node access(new libyang::Data_Node(lyslot, mod, "access", (slot->isReadOnly() ? "READ_ONLY" : "READ_WRITE") ));

BENCH_SHOW << "--- CallbackORanSoftwareMgr::processElements SLOT (common): " << BENCH_ELAPSED("slot") << std::endl ;

		if (!slot->isAllocated())
			continue ;

		auto pkg(slot->package()) ;
		libyang::S_Data_Node product(new libyang::Data_Node(lyslot, mod, "product-code", pkg->productCode().c_str()));
		libyang::S_Data_Node vendor(new libyang::Data_Node(lyslot, mod, "vendor-code", pkg->vendorCode().c_str()));
		libyang::S_Data_Node buildId(new libyang::Data_Node(lyslot, mod, "build-id", pkg->buildId().c_str()));
		libyang::S_Data_Node buildName(new libyang::Data_Node(lyslot, mod, "build-name", pkg->buildName().c_str()));
		libyang::S_Data_Node buildVersion(new libyang::Data_Node(lyslot, mod, "build-version", pkg->buildVersion().c_str()));

		// APP
		{
		libyang::S_Data_Node files(new libyang::Data_Node(lyslot, mod, "files"));

		libyang::S_Data_Node fname(new libyang::Data_Node(files, mod, "name", pkg->appFileName().c_str()));
		libyang::S_Data_Node fversion(new libyang::Data_Node(files, mod, "version", pkg->appFileVersion().c_str()));
		libyang::S_Data_Node fpath(new libyang::Data_Node(files, mod, "local-path", pkg->appPath().c_str()));
		libyang::S_Data_Node fintegrity(new libyang::Data_Node(files, mod, "integrity", (pkg->appIntegrity() ? "OK" : "NOK") ));
		}

BENCH_SHOW << "--- CallbackORanSoftwareMgr::processElements SLOT (app): " << BENCH_ELAPSED("slot") << std::endl ;

		// OS
		{
		libyang::S_Data_Node files(new libyang::Data_Node(lyslot, mod, "files"));

		libyang::S_Data_Node fname(new libyang::Data_Node(files, mod, "name", pkg->osFileName().c_str()));
		libyang::S_Data_Node fversion(new libyang::Data_Node(files, mod, "version", pkg->osFileVersion().c_str()));
		libyang::S_Data_Node fpath(new libyang::Data_Node(files, mod, "local-path", pkg->osPath().c_str()));
		libyang::S_Data_Node fintegrity(new libyang::Data_Node(files, mod, "integrity", (pkg->osIntegrity() ? "OK" : "NOK") ));
		}

BENCH_SHOW << "--- CallbackORanSoftwareMgr::processElements SLOT (os): " << BENCH_ELAPSED("slot") << std::endl ;

BENCH_SHOW << "--- CallbackORanSoftwareMgr::processElements SLOT: " << BENCH_ELAPSED("slot") << std::endl ;

	}


BENCH_SHOW << "=== CallbackORanSoftwareMgr::processElements TOTAL: " << BENCH_ELAPSED("allSlots") << std::endl ;

}
