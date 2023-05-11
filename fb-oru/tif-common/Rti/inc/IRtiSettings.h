#ifndef _IRTISETTINGS_H_
#define _IRTISETTINGS_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IRtiSettings.h
 * \brief     Interface to RTI settings
 *
 *
 * \details   Interface to RTI settings
 *
 */

#include <string>
#include <vector>
#include <memory>
#include "DataVariant.h"

namespace Mplane {

/**
 * Class for accessing and modifying the settings
 */
class IRtiSettings
{
public:
    virtual ~IRtiSettings() {};

    /**
     * Is this setting a valid name
     * @param name	Setting name
     * @return true if setting name is valid
     */
    virtual bool has(const std::string& name) const = 0 ;

    /**
     * Get the setting value
     * @param name	Setting name
     * @return the setting value
     */
    virtual std::shared_ptr<DataVariant> get(const std::string& name) const = 0 ;

    /**
     * Get the setting value
     * @param name	Setting name
     * @return the setting value
     */
    virtual std::string getComment(const std::string& name) const = 0 ;

    /**
     * Change the setting value
     * @param name	Setting name
     * @param value	string containing the new value
     * @return true if able to set the value; false otherwise
     */
    virtual bool set(const std::string& name, const std::string& value) = 0 ;

    /**
     * Returns an iterator that points at the start of the settings list
     * @return iterator at start of list
     */
    virtual std::vector< std::shared_ptr<DataVariant> >::const_iterator begin(void) const = 0 ;

    /**
     * Returns an iterator that points at the end of the settings list
     * @return iterator at end of list
     */
    virtual std::vector< std::shared_ptr<DataVariant> >::const_iterator end(void) const = 0 ;

};

/**
 * Class for defining the settings
 */
class IRtiSettingsCreator : public IRtiSettings
{
public:
    virtual ~IRtiSettingsCreator() {};

protected:
    /**
     * Define a setting value so it can be accessed
     * @param name	Name of setting
     * @param type	Setting type
     * @param value	Initial value
     * @param comment	Comment on this setting variable
     * @return true if able to define setting; false otherwise
     */
    virtual bool define(const std::string& name, const DataVariantType::Type& type, const std::string& value,
    		const std::string& comment) = 0 ;
};


}
#endif /* _IRTISETTINGS_H_ */
