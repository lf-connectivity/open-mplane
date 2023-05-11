/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      YangElement.h
 * \brief     Yang Element class
 *
 *
 * \details   <multi-line detailed description of file>
 *
 */

#ifndef _INC_YANG_ELEMENT_H_
#define _INC_YANG_ELEMENT_H_

#include <string>
#include <memory>
#include <vector>

#include "IYangConfig.h"

namespace Mplane
{

class YangElement : public IYangElement {
 public:
  YangElement(std::string type); //!> Constructor with just a type.
  YangElement(std::string type, std::string name); //!> Construction with type
                                                   //! and name
  YangElement(
      std::string type,
      std::string name,
      std::string value); //!> Constructor with type, name and value.
  YangElement(
      std::string type,
      std::string name,
      std::string value,
      std::string access); //!> Constructor with type, name and value.

  virtual std::string getType(void); //!> Get the type of the element
  virtual std::string getName(void); //!> Get the name of the element
  virtual std::string getValue(void); //!> Get the value associated with the
                                      //! element
  virtual std::string getVersion(void); //!> Get the version of the element.
                                        //! Only used for modules.
  virtual std::string getAccess(void); //!> Get the access permissions of the
                                       //! element. Only used for leafs.

  virtual unsigned int getNumberOfChildElements(void); //!> Get the number of
                                                       //! child elements that
                                                       //! the parent has

  virtual void setVersion(std::string version); //!> This is only applicable to
                                                //! a module

  virtual std::shared_ptr<IYangElement> getElement(
      std::string type); // Get the element by type only - used for choice cases
  virtual std::shared_ptr<IYangElement> getElement(
      std::string type, std::string name); // Get the element by type and name
  virtual std::shared_ptr<IYangElement> getElement(
      std::string type, unsigned int number); // Get the element by type and
                                              // index number - used for lists

  virtual void listElements(std::string& list); //!> List the child elements
  virtual void listElements(
      std::string type, std::string& list); //!> List the child elements by type
                                            //!- used for modules

  virtual void addChildElement(
      std::shared_ptr<IYangElement> elementToAdd); //!> Add a child element. You
                                                   //! have to make the element
                                                   //! first.

  virtual void getChildElements(
      std::vector<std::shared_ptr<IYangElement>>& childElementVector);

 private:
  std::string elementType; //!> Element type
  std::string elementName; //!> Element name
  std::string elementValue; //!> Element value
  std::string elementVersion; //!> This is only applicable to a module
  std::string elementAccessPermissions; //!> This is only for leafs

  std::vector<std::shared_ptr<IYangElement>> childElements; //!> Vector of
                                                            //! IYangElements
                                                            //! for storing the
                                                            //! child elements.
};
}



#endif /* _VYMS_INC_YANG_ELEMENT_H_ */
