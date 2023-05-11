#ifndef _COMMON_OBSERVER_H_
#define _COMMON_OBSERVER_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Observer.hpp
 * \brief     Template classes for Observer/Subject pattern
 *
 *
 * \details   Template classes for Observer/Subject pattern
 *
 */

#include <vector>
#include <algorithm>
#include "Mutex.h"
#include "GlobalTypeDefs.h"
#include <memory>

namespace Mplane
{

class SubjectObserverNull {};

/**
 This template class provides an implementation that allows an object to be the
 observer of another class that extends the Mplane::Subject template.

 For examples of how this class is used see the design document:

 @ref observer_subject_template

 */
template<class T, typename D = SubjectObserverNull>
class Observer
{
public:
    /**
     * Constructor
     */
    Observer()
    {
    }
    /**
     * Virtual destructor
     */
    virtual ~Observer()
    {
    }
    /**
     * The callback method used by the corresponding Mplane::Subject implementation
     * to notify the observer of any change in the subject data. The default implementation
     * here must be overridden by the observer.
     *
     * @param subject
     */
    virtual void update(T& subject) {};
    /**
     * This is an alternative callback method that allows the subject matter
     * provider to supply additional data that relates to the subject type.
     * This default implementation must be overridden by the observer.
     * @param subject
     * @param data
     */
    virtual void update(T& subject, D data) {}
    /**
     * A method used to get the name of the observer
     */
    virtual const char* name() const = 0;
};

/**
 This template class provides an implementation of subject class that can be extended
 to provide subject change notification to any attached Mplane::Observer based classes.

 This class uses it's own Mutex to support thread safe access to its Observer list.

 For examples of a subject implementation see the design documentation:

 @ref observer_subject_template

 */
template<class T, typename D = SubjectObserverNull>
class Subject
{
public:
    /**
     * Constructor
     */
    Subject():
        mutex ( std::shared_ptr<Mutex> ( new Mutex() ) )
    {
    }
    /**
     * Destructor, removes all attached observers from the list.
     */
    virtual ~Subject()
    {
        detachAll();
    }

    /**
     * Method called by a critical observer to attach to the subject. This function is not
     * virtual as it is not expected to be overridden.
     *
     * Critical observers are notified first when being notified via their update() method.
     *
     * Typically, there should only be one critical observer in this design pattern, but no restriction is made
     * in this implementation and the critical observer is placed at the front of the list, thus taking precedence over
     * any other critical observer that might have attached already.
     *
     * @param observer
     */
    void attachCritical(Observer<T,D> &observer)
    {
        // Ensure no duplication.
        Mutex::Lock lock( *mutex ) ;

        auto it( std::find(observers.begin(), observers.end(), &observer) ) ;
        if (it == observers.end())
        {
            // The critical observer is put at the front of the observer list
            observers.insert(observers.begin(), &observer);
        }
    }

    /**
     * Method called by observers to attach to the subject. This function is not
     * virtual as it is not expected to be overridden.
     * @param observer
     */
    void attach(Observer<T,D> &observer)
    {
        // Ensure no duplication.
        Mutex::Lock lock( *mutex ) ;

        auto it( std::find(observers.begin(), observers.end(), &observer) ) ;
        if (it == observers.end())
        {
            observers.push_back(&observer);
        }
    }

    /**
     * Method called by an attached observer to removed itself from the
     * list of observers.This function is not virtual
     * as it is not expected to be overridden.
     *
     * @param observer
     */
    void detach(Observer<T,D> &observer)
    {
        Mutex::Lock lock( *mutex ) ;

        auto it( std::find(observers.begin(), observers.end(), &observer) ) ;
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }

    /**
     * Method called by the subject destructor to detach all observers from the subject.
     */
    void detachAll()
    {
        observers.clear();
    }

    /**
     * Method called by the final implementation of the Subject to notify all the
     * attached observers through their update method.
     */
    void notify()
    {
        Mutex::Lock lock( *mutex ) ;
        for (auto observer : observers)
        {
        	observer->update(*(dynamic_cast<T *>(this)));
        }
    }

    void notify(D data)
    {
        Mutex::Lock lock( *mutex ) ;
        for (auto observer : observers)
        {
        	observer->update(*(dynamic_cast<T *>(this)), data);
        }
    }

    UINT32 getNumObservers()
    {
        return observers.size();
    }

    /**
     * A method used to get the name of the observer
     */
    const char* getObsName(UINT32 index) const
    {
        if (index < observers.size())
        {
            return (*observers[index]).name();
        }
        return "NULL";
    }

private:
    /**
     * Maintains the list of attached observers.
     */
    std::vector<Observer<T,D> *> observers;

    /**
     * Mutex used to ensure thread safe access for attaching, detaching
     * and updating observers.
     */
    std::shared_ptr<Mutex> mutex;
};

}  // end namespace Mplane

#endif /* _COMMON_OBSERVER_H_ */
