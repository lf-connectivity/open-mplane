/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      FileConfigWriter.cpp
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
#include "Path.h"

#include "FileConfigWriter.h"

using namespace Mplane;

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
FileConfigWriter::FileConfigWriter(const std::map<std::string, std::string> defaults) :
	FileConfigBase(defaults)
{
}

//-------------------------------------------------------------------------------------------------------------
FileConfigWriter::FileConfigWriter(const std::string &path, const std::map<std::string, std::string> defaults) :
	FileConfigBase(path, defaults)
{
}

//-------------------------------------------------------------------------------------------------------------
FileConfigWriter::FileConfigWriter(const FileConfigWriter &rhs) :
	FileConfigBase(rhs)
{
}

//-------------------------------------------------------------------------------------------------------------
FileConfigWriter::FileConfigWriter(const FileConfigBase &rhs) :
	FileConfigBase(rhs)
{
}

//-------------------------------------------------------------------------------------------------------------
FileConfigWriter& FileConfigWriter::operator =(const FileConfigWriter &rhs)
{
	if (&rhs == this)
		return *this ;

	this->FileConfigBase::operator=(rhs) ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
FileConfigWriter& FileConfigWriter::operator =(const FileConfigBase &rhs)
{
	if (&rhs == this)
		return *this ;

	this->FileConfigBase::operator=(rhs) ;
	return *this ;
}

//-------------------------------------------------------------------------------------------------------------
FileConfigWriter::~FileConfigWriter()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::setPath(const std::string &path)
{
	return this->FileConfigBase::setPath(path) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileConfigWriter::filename() const
{
	return this->FileConfigBase::filename() ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::isValid() const
{
	return this->FileConfigBase::isValid() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileConfigWriter::value(const std::string &varname) const
{
	return this->FileConfigBase::value(varname) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::isVariable(const std::string &varname) const
{
	return this->FileConfigBase::isVariable(varname) ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileConfigWriter::value(const std::string &section, const std::string &varname) const
{
	return this->FileConfigBase::value(section, varname) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::isVariable(const std::string &section, const std::string &varname) const
{
	return this->FileConfigBase::isVariable(section, varname) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::isSection(const std::string &section) const
{
	return this->FileConfigBase::isSection(section) ;
}

//-------------------------------------------------------------------------------------------------------------
std::vector<std::string> FileConfigWriter::sections() const
{
	return this->FileConfigBase::sections() ;
}

//-------------------------------------------------------------------------------------------------------------
std::string FileConfigWriter::error()
{
	return this->FileConfigBase::error() ;
}

//-------------------------------------------------------------------------------------------------------------
void FileConfigWriter::show() const
{
	this->FileConfigBase::show() ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::modifyValue(const std::string &varname, const std::string &value)
{
	return this->FileConfigBase::_modifyValue(varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::modifyValue(const std::string &section,
		const std::string &varname, const std::string &value)
{
	return this->FileConfigBase::_modifyValue(section, varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::modifyValue(const std::string &varname, double value)
{
	return this->FileConfigBase::_modifyValue(varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::modifyValue(const std::string &section, const std::string &varname, double value)
{
	return this->FileConfigBase::_modifyValue(section, varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::modifyValue(const std::string &varname, int value)
{
	return this->FileConfigBase::_modifyValue(varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::modifyValue(const std::string &section, const std::string &varname, int value)
{
	return this->FileConfigBase::_modifyValue(section, varname, value) ;
}



//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::setValue(const std::string &varname, const std::string &value)
{
	return this->FileConfigBase::_setValue(varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::setValue(const std::string &section,
		const std::string &varname, const std::string &value)
{
	return this->FileConfigBase::_setValue(section, varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::setValue(const std::string &varname, double value)
{
	return this->FileConfigBase::_setValue(varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::setValue(const std::string &section, const std::string &varname, double value)
{
	return this->FileConfigBase::_setValue(section, varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::setValue(const std::string &varname, int value)
{
	return this->FileConfigBase::_setValue(varname, value) ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::setValue(const std::string &section, const std::string &varname, int value)
{
	return this->FileConfigBase::_setValue(section, varname, value) ;
}


//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::save()
{
	return this->FileConfigBase::_save() ;
}

//-------------------------------------------------------------------------------------------------------------
bool FileConfigWriter::read()
{
	return this->FileConfigBase::_read() ;
}
