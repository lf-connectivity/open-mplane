/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileConfigBase.h
 * \brief     Base class for config file
 *
 *
 * \details   Base class for config file reader and writer classes
 *
 * Config file is of the form:
 *
 * vendor=@VENDOR_CODE@
 * code=@PRODUCT_CODE@
 * name=@BUILD_BOARD@-@BUILD_CUSTOMER@-@BUILD_APPLICATION@-@BUILD_VERSION@#@BUILD_NUMBER@
 * build-Id=1
 *
 * [os]
 * fileName=@OS_PKG_FILENAME@
 * fileVersion=@OS_PKG_VERSION@
 * path=@OS_PKG_FILENAME@
 * checksum=@osMd5@
 * status=valid
 *
 * [app]
 * fileName=@APP_PKG_FILENAME@
 * fileVersion=@BUILD_VERSION@
 * path=@APP_PKG_FILENAME@
 * checksum=@appMd5@
 * status=valid
 *
 * 		In other words, sets of variable=value pairs either at the top of the file (i.e. "global") or contained under a section started by a "[section]"
 * 		section label.
 *
 * 		Variables can be retrieved either from the global namespace or from a section namespace.
 *
 * 		The global variables are available inside all of the sections.
 *
 */


#ifndef INC_FILECONFIGBASE_H_
#define INC_FILECONFIGBASE_H_

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <memory>

namespace Mplane {

/*!
 * \class  FileConfigBase
 * \brief
 * \details
 *
 */
class FileConfigBase {
public:
	FileConfigBase(const std::map<std::string, std::string> defaults = std::map<std::string, std::string>{}) ;
	FileConfigBase(const std::string& path, const std::map<std::string, std::string> defaults = std::map<std::string, std::string>{}) ;
	virtual ~FileConfigBase() ;

	/**
	 * Copy constructor
	 */
	FileConfigBase(const FileConfigBase& rhs) ;

	/**
	 * Assignment operator
	 */
	FileConfigBase& operator=(const FileConfigBase& rhs) ;


	/**
	 * Compare this with another
	 */
	virtual bool isEqual(const FileConfigBase& rhs) const ;

	/**
	 * Compare this with another
	 */
	virtual bool isEqual(std::shared_ptr<FileConfigBase> rhs) const ;

	/**
	 * Clean out any invalid variables. This is only performed if the defaults map has been set. If so, then any variables
	 * not specified in the defaults map will be removed
	 */
	virtual bool clean() ;

	/**
	 * Clean out all variables.
	 */
	virtual bool clear() ;

	/**
	 * Set a file path
	 * @return TRUE if ok; FALSE otherwise (use error() method to get error string)
	 */
	virtual bool setPath(const std::string& path) ;

	/**
	 * get current config file path
	 */
	virtual std::string filename() const ;

	/**
	 * Is the current config valid?
	 */
	virtual bool isValid() const ;

	/**
	 * Get all the values as varname/value pairs. Section varnames will consist of: <section name>/<variable>
	 */
	virtual std::vector<std::pair<std::string, std::string>> values() const ;

	/**
	 * Get the value of the global variable (or a section variable if varname is a path)
	 * @return value string if variable is preset; empty string otherwise
	 */
	virtual std::string value(const std::string& varname) const ;

	/**
	 * is the global variable (or a section variable if varname is a path) available?
	 */
	virtual bool isVariable(const std::string& varname) const ;

	/**
	 * Get the value of the section variable
	 * @return value string if variable is preset; empty string otherwise
	 */
	virtual std::string value(const std::string& section, const std::string& varname) const ;

	/**
	 * is the section variable available?
	 */
	virtual bool isVariable(const std::string& section, const std::string& varname) const ;

	/**
	 * Is this section name valid?
	 */
	virtual bool isSection(const std::string& section) const ;

	/**
	 * Get the list of section names
	 */
	virtual std::vector<std::string> sections() const ;

	/**
	 * Get any error and clear it
	 */
	virtual std::string error() ;

	/**
	 * Debug
	 */
	virtual void show() const ;

	/**
	 * Get the value of the global variable (or a section variable if varname is a path) as a double
	 * @return value if variable is preset; 0.0 otherwise
	 */
	virtual double doubleValue(const std::string& varname) const ;

	/**
	 * Get the value of the section variable as a double
	 * @return value if variable is preset; 0.0 otherwise
	 */
	virtual double doubleValue(const std::string& section, const std::string& varname) const ;

	/**
	 * Get the value of the global variable (or a section variable if varname is a path) as an int
	 * @return value if variable is preset; 0 otherwise
	 */
	virtual int intValue(const std::string& varname) const ;

	/**
	 * Get the value of the section variable as an int
	 * @return value if variable is preset; 0 otherwise
	 */
	virtual int intValue(const std::string& section, const std::string& varname) const ;




protected:
	void applyDefaults() ;
	bool setError(const std::string& error) ;
	bool _read() ;
	std::string find(const std::string& varname, bool& found) const ;
	std::string find(const std::string& section, const std::string& varname, bool& found) const ;
	bool nameIsPath(const std::string& varname, std::string& section, std::string& sectionVarname) const ;
	std::string toPath(const std::string& section, const std::string& varname) const ;

	bool _modifyValue(const std::string& varname, const std::string& value) ;
	bool _modifyValue(const std::string& section, const std::string& varname, const std::string& value) ;
	bool _modifyValue(const std::string& varname, double value) ;
	bool _modifyValue(const std::string& section, const std::string& varname, double value) ;
	bool _modifyValue(const std::string& varname, int value) ;
	bool _modifyValue(const std::string& section, const std::string& varname, int value) ;

	bool _setValue(const std::string& varname, const std::string& value) ;
	bool _setValue(const std::string& section, const std::string& varname, const std::string& value) ;
	bool _setValue(const std::string& varname, double value) ;
	bool _setValue(const std::string& section, const std::string& varname, double value) ;
	bool _setValue(const std::string& varname, int value) ;
	bool _setValue(const std::string& section, const std::string& varname, int value) ;

	bool _save() ;

private:
	std::string mPath ;
	bool mValid ;
	std::string mError ;
	std::map<std::string, std::string> mGlobals ;
	std::map<std::string, std::map<std::string, std::string>> mSections ;
	std::map<std::string, std::string> mDefaults ;
} ;

/**
 * Compare this with another config
 */
inline bool operator==(const FileConfigBase& lhs, const FileConfigBase& rhs)
{
	return lhs.isEqual(rhs) ;
}

inline bool operator==(std::shared_ptr<FileConfigBase> lhs, std::shared_ptr<FileConfigBase> rhs)
{
	return lhs->isEqual(rhs) ;
}

inline bool operator==(std::shared_ptr<FileConfigBase> lhs, const FileConfigBase& rhs)
{
	return lhs->isEqual(rhs) ;
}

inline bool operator==(const FileConfigBase& lhs, std::shared_ptr<FileConfigBase> rhs)
{
	return lhs.isEqual(rhs) ;
}


inline bool operator!=(const FileConfigBase& lhs, const FileConfigBase& rhs)
{
	return !(lhs == rhs) ;
}

inline bool operator!=(std::shared_ptr<FileConfigBase> lhs, std::shared_ptr<FileConfigBase> rhs)
{
	return !(lhs == rhs) ;
}

inline bool operator!=(std::shared_ptr<FileConfigBase> lhs, const FileConfigBase& rhs)
{
	return !(lhs == rhs) ;
}

inline bool operator!=(const FileConfigBase& lhs, std::shared_ptr<FileConfigBase> rhs)
{
	return !(lhs == rhs) ;
}

}

#endif /* INC_FILECONFIGBASE_H_ */
