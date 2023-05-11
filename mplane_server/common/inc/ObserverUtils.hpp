/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      ObserverUtils.hpp
 * \brief     Utilities and helper classes for the Observer/Subject templates
 *
 *
 * \details
 *
 */

#ifndef OBSERVERUTILS_HPP_
#define OBSERVERUTILS_HPP_

#include <memory>
#include <string>

#include "Observer.hpp"

namespace Mplane {

/**
 * Wrapper class which creates an object that is an Observer of some Subject and
 * which passes any update() on to the parent class which created it
 */
template <typename Tparent, typename Tsubject>
class ObserverWrapper : public Observer<Tsubject> {
 public:
  ObserverWrapper(
      Tparent* parent,
      const std::string& name,
      std::shared_ptr<Tsubject> subject)
      : mParent(parent), mName(name), mSubject(subject) {}

  virtual ~ObserverWrapper() {}

  virtual void
  update(Tsubject& subject) {
    mParent->update(subject);
  }

  virtual const char*
  name() const {
    return mName.c_str();
  }

  virtual std::shared_ptr<Tsubject>
  getSubject() {
    return mSubject;
  }

 private:
  Tparent* mParent;
  std::string mName;
  std::shared_ptr<Tsubject> mSubject;
};

/**
 * Utility template function which creates a shared pointer to an
 * ObserverWrapper object
 * @param parent
 * @param name
 * @param subject
 * @return shared pointer to ObserverWrapper
 */
template <typename Tparent, typename Tsubject>
inline std::shared_ptr<ObserverWrapper<Tparent, Tsubject>>
make_observerWrapper(
    Tparent* parent,
    const std::string& name,
    std::shared_ptr<Tsubject> subject) {
  std::shared_ptr<ObserverWrapper<Tparent, Tsubject>> observer(
      new ObserverWrapper<Tparent, Tsubject>(parent, name, subject));
  return observer;
}

} // namespace Mplane

#endif /* OBSERVERUTILS_HPP_ */
