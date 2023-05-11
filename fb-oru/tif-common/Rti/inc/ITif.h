/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ITif.h
 * \brief     Virtual interface to TIF
 *
 *
 * \details   Interface provides a means of injecting TIF directories into the tree once the initial base tree is created
 *
 */


#ifndef ITIF_H_
#define ITIF_H_

#include <memory>
#include <string>

#include "SocketServer.h"
#include "IRtiMsgParser.h"
#include "IRtiSettings.h"

namespace Mplane {

class ITif ;

/**
 * \class ITifEntry
 */
class ITifEntry {
public:
	ITifEntry() {}
	virtual ~ITifEntry() {}

	/**
	 * Called by ITif::inject() to get this object to add it's entries
	 * @param tif
	 * @return true if ok
	 */
	virtual bool registerEntry(ITif* tif) =0 ;
};

/*!
 * \class ITif
 * Virtual interface to a single TIF interface
 */
class ITif {
public:
	ITif() {}
	virtual ~ITif() {}

	/**
	 * Inject the directory(s) provided by this entity
	 * @return true if ok
	 */
	virtual bool doInject(std::shared_ptr<ITifEntry> entry) =0 ;

	/**
	 * Hide the directory at the given path if present in the tree
	 * @param dir
	 * @return true if found; false otherwise
	 */
	virtual bool doHideDir(const std::string& dir) =0 ;

	/**
	 * Un-Hide the directory at the given path if present in the tree
	 * @param dir
	 * @return true if found; false otherwise
	 */
	virtual bool doUnhideDir(const std::string& dir) =0 ;

	/**
	 * Rename the directory at the given path (if present in the tree)
	 * @param dir		Path to directory node (e.g. "/rx/adc")
	 * @param newName	New name of leaf directory (e.g. "ADC")
	 * @return true if found; false otherwise
	 */
	virtual bool doRename(const std::string& dir, const std::string& newName) =0 ;

} ;


/*!
 * \class ITifControl
 * Virtual interface to the master controller (which creates the instances of the TIFs)
 */
class ITifControl : public virtual ITif {
public:
	ITifControl() {}
	virtual ~ITifControl() {}

	/**
	 * Singleton
	 */
	static std::shared_ptr<ITifControl> getInstance() ;

	/**
	 * Get a usable ITif instance
	 */
	static std::shared_ptr<ITif> getITif() ;

	/**
	 * Inject the directory(s) provided by this entity
	 * @return true if ok
	 */
	static bool inject(std::shared_ptr<ITifEntry> entry) ;

	/**
	 * Hide the directory at the given path if present in the tree. If 'hide' is not specified then this does nothing.
	 * This interface then allows the method to be called with a #define set either to 'true' or blank - if blank then
	 * this is a no op
	 * @param dir
	 * @return true if found; false otherwise
	 */
	static bool hideDir(const std::string& dir, bool hide = false) ;

	/**
	 * Rename the directory at the given path (if present in the tree). If 'newName' is not specified then this does nothing.
	 * This interface then allows the method to be called with a #define set either to a string or blank - if blank then
	 * this is a no op
	 * @param dir		Path to directory node (e.g. "/rx/adc")
	 * @param newName	New name of leaf directory (e.g. "ADC")
	 * @return true if found; false otherwise
	 */
	static bool rename(const std::string& dir, const std::string& newName = "") ;

	/**
	 * Adds a new server to the TIF control such that connections can also be made to TIF via this new interface
	 * @param server	Created by the caller
	 * @return true if added ok
	 */
	static bool addServer(std::shared_ptr<SocketServer> server) ;

	/**
	 * Get the priority of the TIF task - used when creating new servers
	 */
	static unsigned getTaskPriority() ;


	// Special sentinel values
	static std::shared_ptr<IRtiMsgParser> NULL_MSG_PARSER ;
	static std::shared_ptr<IRtiSettings> NULL_SETTINGS ;

} ;



}

//=============================================================================================================
// MACROS
//=============================================================================================================

// Convenience macro which uses the build config tif settings to set up TIF for a build feature
#define TIF_BUILD_SETTINGS(nm, path) \
{\
	if (!ITifControl::hideDir(path, TIF_FEAT_##nm##_HIDE))\
		return false ;\
\
	if (!ITifControl::rename(path, TIF_FEAT_##nm##_NAME))\
		return false ;\
}

#endif /* ITIF_H_ */
