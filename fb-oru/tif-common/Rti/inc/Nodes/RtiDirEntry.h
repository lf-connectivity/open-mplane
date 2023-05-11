/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Nodes/RtiDirEntry.h
 * \brief     "Directory" entry for RTI
 *
 *
 * \details   Directory consists of class "directories", containing function/variable function "files". All entries are
 * derived from this common base class
 *
 */


#ifndef RTIDIRENTRY_H_
#define RTIDIRENTRY_H_

#include "IRtiSettings.h"
#include "IRtiMsgParser.h"
#include "DirNode.h"

namespace Mplane {

/**
 * Class containing the information for a single directory entry
 */
struct RtiDirEntry : public DirNode
{
public:
	/**
	 * List of derived class types
	 */
	enum RtiDirEntryType {
		RTIENTRY_BASE,
		RTIENTRY_CLASS,
		RTIENTRY_FUNC,
		RTIENTRY_VAR
	};

    RtiDirEntry( const std::string& pathname, const std::string& comment, DirNode::DirNodeType type,
			IRtiMsgParser& msgParser, IRtiSettings& settings);

    virtual ~RtiDirEntry();

    /**
     * Hook called by the message parsing to process the function
     * @param args	String containing function call arguments
     * @return reply string
     */
    virtual std::string processFunc(const std::string& args) = 0;

    /**
     * Process the help command for this device/class
     * @return help string
     */
    virtual std::string help() = 0;

    /**
     * Process the ls command for this device/class
     * @return ls string
     */
    virtual std::string ls() = 0;

    /**
     * Access the comment
     */
    std::string getComment() const ;

    /**
     * Get the node's type
     * @return type
     */
    RtiDirEntryType getType() const ;

    /**
     * Create a correctly formatted error string (i.e. with STATUS=ERROR etc) using the provided error message
     * @param message
     * @return error status string
     */
    static std::string createErrorStatus(const std::string& message) ;

    /**
     * Create a correctly formatted ok string (i.e. with STATUS=OK etc)
     * @return ok status string
     */
    static std::string createOkStatus() ;

protected:
    /**
     * Used by derived types to set the type accordingly
     * @param type
     */
    void setType(RtiDirEntryType type) ;

    /**
     * Format the information for an ls line into a string
     * @param label		string shown at start of line
     * @param comment	string shown after label
     * @return formatted string
     */
    std::string lsFormat(const std::string& label, const std::string& comment);

    /**
     * Get the width that the label part of an ls string will be set to
     * @return width
     */
    unsigned lsLabelWidth();

    /**
     * Create a help title line
     * @param title
     * @return help string for a title
     */
    std::string helpTitleFormat(const std::string& title) ;

    /**
     * Format a help line
     * @param label		string shown at start of line
     * @param comment	string shown after label
     * @return help string for a title
     */
    std::string helpFormat(const std::string& label, const std::string& comment) ;

    /**
     * Get an indent string that will be indented from the label (label is at indent level 0)
     * @return indent string
     */
    std::string helpFormatIndent(unsigned level);

    /**
     * Wrap ls label string on "," and " " to fit into available space
     * @param label
     * @return
     */
    std::vector<std::string> wrapLabel(const std::string& label) ;
    std::vector<std::string> wrapLabel(const std::string& label, const std::string& wrapStr) ;


protected:
    RtiDirEntryType mType ;			//<! The type of node this is. Low-cost alternative to using RTTI
    std::string mComment;			//<! Optional function comment

    IRtiMsgParser& mMsgParser ;		//<! Ref to message parser
    IRtiSettings& mSettings ;		//<! Ref to settings
};


}
#endif /* RTIDIRENTRY_H_ */
