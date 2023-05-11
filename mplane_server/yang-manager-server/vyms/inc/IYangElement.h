/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      IYangConfig.h
 * \brief     Yang Manger Server configuration virtual interface
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _VYMS_INC_IYANGELEMENT_H_
#define _VYMS_INC_IYANGELEMENT_H_

#include <memory>
#include <string>
#include <vector>

#include "GlobalTypeDefs.h"

namespace Mplane
{
class IYangElement {
 public:
  // Make element factories
  static std::shared_ptr<IYangElement> makeElement(
      std::string type,
      std::string name,
      std::string value,
      std::string access);
  static std::shared_ptr<IYangElement> makeElement(
      std::string type, std::string name, std::string value);
  static std::shared_ptr<IYangElement> makeElement(
      std::string type, std::string name);
  static std::shared_ptr<IYangElement> makeElement(std::string type);

  virtual std::string getType(void) = 0; //!> Get the element type
  virtual std::string getName(void) = 0; //!> Get the element name
  virtual std::string getValue(void) = 0; //!> Get the element value - Used for
                                          //! any leafs or listleaf entries
  virtual std::string getVersion(void) = 0; //!> Get the version - used for
                                            //! modules only.
  virtual std::string getAccess(void) = 0; //!> Get the access permissions of
                                           //! the element. Only used for leafs.

  virtual unsigned int getNumberOfChildElements(
      void) = 0; //!> Get the number of child elements that a parent has. This
                 //! is useful for lists.

  virtual void setVersion(std::string version) = 0; //!> Set the version - used
                                                    //! for modules only.

  virtual std::shared_ptr<IYangElement> getElement(
      std::string type) = 0; // Get element by type only - used for choice
                             // elements
  virtual std::shared_ptr<IYangElement> getElement(
      std::string type,
      std::string name) = 0; // Get element by type and name - used for all
                             // other types where a name and type is known
  virtual std::shared_ptr<IYangElement> getElement(
      std::string type,
      unsigned int number) = 0; // Get element by type and index number - used
                                // for list entries

  virtual void listElements(std::string& list) = 0; //!> List the child elements
                                                    //! of a parent - used for
                                                    //! modules
  virtual void listElements(
      std::string type,
      std::string& list) = 0; //!> List the child elements of a parent by type -
                              //! used for modules

  virtual void addChildElement(
      std::shared_ptr<IYangElement> elementToAdd) = 0; //!> Add a child element
                                                       //! to a parent. You have
                                                       //! to make the element
                                                       //! first.

  virtual void getChildElements(std::vector<std::shared_ptr<IYangElement>>&
                                    childElementVector) = 0; //!> Get child
                                                             //! elements

  virtual ~IYangElement() {}
};
}

#endif /* _VYMS_INC_IYANGELEMENT_H_ */
