/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      DirNode.h
 * \brief     "Directory" node
 *
 *
 * \details   A directory node that understands paths. A node marked as "DIRECTORY" can contain other nodes; a node
 * marked as "FILE" cannot. Each node can "change directory" up or down the hierarchy
 *
 */


#ifndef DIRNODE_H_
#define DIRNODE_H_

#include <string>
#include <map>
#include <vector>

namespace Mplane {

class DirNode ;
typedef DirNode* DirNodePtr ;

/**
 * Directory entry maps a name/path to a directory node
 */
class DirEntry {
public:
	/**
	 * Create a node of specified type
	 * @param pathname	Full path to this node
	 * @param node		Directory node
	 */
	DirEntry(const std::string& path, const std::string& name, DirNodePtr node) ;

	virtual ~DirEntry() ;

	/**
	 * Get the full path string
	 * @return path
	 */
	std::string getFullPath() const ;

	/**
	 * Get the path string (just the directory part of the full path)
	 * @return path
	 */
	std::string getPath() const ;

	/**
	 * Get the name string (just the name part of the full path)
	 * @return name
	 */
	std::string getName() const ;

	/**
	 * Get the directory node
	 * @return directory node
	 */
	DirNodePtr getNode() const ;

	/**
	 * Set new directory node
	 * @param node
	 */
	void setNode(DirNodePtr node) ;

	/**
	 * Rename the path segment specified of this entry
	 * @param from
	 * @param to
	 */
	void renamePath(const std::string& from, const std::string& to) ;


private:
	/**
	 * The node
	 */
	DirNodePtr mNode ;

	/**
	 * Directory path to this node
	 */
	std::string mPath ;

	/**
	 * Name of the node
	 */
	std::string mName ;
};


/**
 * The actual directory node holding the data
 */
class DirNode {
public:
	/**
	 * Some useful constants
	 */
	static std::string PATHSEP ;
	static std::string THISDIR ;
	static std::string PREVDIR ;
	static std::string HIDDEN ;

	/**
	 * Nodes can either be simple files (only having it's own data), or a directory which can contain sub-nodes
	 */
	enum DirNodeType {
		DN_DIRECTORY,//!< DN_DIRECTORY
		DN_FILE      //!< DN_FILE
	};

	/**
	 * Create a node of specified type
	 * @param pathname	Full path to this node
	 * @param type		Directory or file
	 */
	DirNode(const std::string& pathname, DirNodeType type) ;

	virtual ~DirNode() ;

	/**
	 * Assuming this node is in a directory tree, adds the new node into the tree. Uses the new node's pathname. If
	 * intervening directories do not exist then they will be created.
	 *
	 * @param node	New node to be inserted
	 * @return true if able to insert node; false otherwise
	 */
	bool add(DirNodePtr node) ;

	/**
	 * If node is a directory then all of it's contents (files, directories) will be removed
	 *
	 * @return true on success; false otherwise
	 */
	bool deleteDirContents() ;

	/**
	 * Returns an error string reporting failure cause
	 * @return an error string if any call has failed. Clears the error string
	 */
	std::string getError() ;

	/**
	 * Make the find search to either match name exactly or do a case insensitive search
	 */
	enum FindType {
		FIND_CASE_SENSITIVE,  //!< FIND_CASE_SENSITIVE
		FIND_CASE_INSENSITIVE,//!< FIND_CASE_INSENSITIVE
	};

	/**
	 * Finds any node type with the given path
	 * @return pointer to the found node or an empty pointer if not found
	 */
	DirNodePtr findNode(const std::string& path, FindType findOption = FIND_CASE_SENSITIVE) ;

	/**
	 * Finds directory node type with the given path
	 * @return pointer to the found node or an empty pointer if not found
	 */
	DirNodePtr findDir(const std::string& path, FindType findOption = FIND_CASE_SENSITIVE) ;

	/**
	 * Finds file node type with the given path
	 * @return pointer to the found node or an empty pointer if not found
	 */
	DirNodePtr findFile(const std::string& path, FindType findOption = FIND_CASE_SENSITIVE) ;

	/**
	 * Change the hidden flag of this node
	 * @param hidden
	 */
	void setHidden(bool hidden) ;

	/**
	 * Rename this node. Also updates the full tree contents (from this node downwards) renaming
	 * all paths which contain this node name
	 * @param name
	 */
	void rename(const std::string& name) ;

	/**
	 * Get the full path string
	 * @return path
	 */
	std::string getFullPath() const ;

	/**
	 * Get the path string
	 * @return path
	 */
	std::string getPath() const ;

	/**
	 * Get the name string
	 * @return name
	 */
	std::string getName() const ;


	/**
	 * Is this a directory
	 * @return true if is directory
	 */
	bool isDir() const ;

	/**
	 * Is this a hidden element
	 * @return true if is hidden
	 */
	bool isHidden() const ;

	/**
	 * Is this the root directory
	 * @return true if is directory
	 */
	bool isRootDir() const ;

	/**
	 * Get the directory contents as a vector of directory nodes (excluding any hidden entries)
	 * @return directory nodes vector
	 */
	std::vector< DirNodePtr > getDir() ;

	/**
	 * Get the complete directory contents as a vector of directory nodes (including any hidden entries)
	 * @return directory nodes vector
	 */
	std::vector< DirNodePtr > getDirAll() ;

	/**
	 * Show contents
	 */
	void show() const ;

	/**
	 * Show detailed contents (for debug)
	 */
	void showDetails() const ;

	/**
	 * Sets/clears the global "show hidden dirs" flag
	 * @param showHidden
	 */
	static void setShowHidden(bool showHidden) ;

private:
	// Directory contents types
	typedef std::map< std::string, DirEntry* > DirContentsType ;
	typedef DirContentsType::iterator DirContentsIterator ;
	typedef DirContentsType::const_iterator DirContentsConstIterator ;

	/**
	 * Walk up the tree to the root node, or error if unable to from this node
	 * @return root node or NULL on error
	 */
	DirNodePtr getRoot() ;

	/**
	 * Find the name in the directory
	 * @param dir	DirNode from which to search
	 * @param name
	 * @param findOption	Sets whether to match case sensitive or insensitive
	 * @return iterator pointing to entry if founf; end() otherwise
	 */
	DirContentsIterator dirFind(DirNodePtr dir, const std::string& name, FindType findOption = FIND_CASE_SENSITIVE) ;

	/**
	 * Recursively rename the path segment specified
	 * @param from
	 * @param to
	 */
	void renamePaths(const std::string& from, const std::string& to) ;

	/**
	 * Extract the directory path from the full pathname
	 *
	 * EXAMPLE: "/carrier/test1" would give "/carrier/"
	 *
	 * @param fullpath
	 * @return directory path
	 */
	static std::string path(const std::string& fullpath) ;

	/**
	 * Get the file/directory name from the full pathname
	 *
	 * EXAMPLE: "/carrier/test1" would give "test1"
	 *
	 * @param fullpath
	 * @return name
	 */
	static std::string name(const std::string& fullpath) ;

	/**
	 * Split a directory path into directory names
	 *
	 * @param path
	 * @return vector of directory names
	 */
	static std::vector< std::string > splitpath(const std::string& path) ;

	/**
	 * Determines whether this node is hidden from the full pathname
	 *
	 * EXAMPLE: "/carrier/.test1" would give true
	 *
	 * @param fullpath
	 * @return true if hidden
	 */
	static bool hidden(const std::string& fullpath) ;

	static bool isThisDir(const std::string& path) ;
	static bool isPrevDir(const std::string& path) ;

private:
	/**
	 * The node type
	 */
	DirNodeType mType ;

	/**
	 * Hidden attribute - when set this element is not normally accessible
	 */
	bool mHidden ;

	/**
	 * Directory path to this node
	 */
	std::string mPath ;

	/**
	 * Name of the node
	 */
	std::string mName ;

	/**
	 * Error string set if any call fails.
	 */
	std::string mError ;

	/**
	 * Directory nodes can contain other nodes
	 */
	DirContentsType mDirContents ;

	/**
	 * Flag used to determine whether hidden dirs and their contents are accessible
	 */
	static bool mShowHidden ;
};

}
#endif /* DIRNODE_H_ */
