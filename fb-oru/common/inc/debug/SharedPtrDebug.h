/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SharedPtrDebug.h
 * \brief     Shared pointer debug helper class
 *
 *
 * \details   A helper object that prints out useful debug information about the reference count of a watched
 * pointer. The watch is set using method watch(). This class is intended only for use by SharedPtr
 */

#ifndef SHAREDPTRDEBUG_HPP_
#define SHAREDPTRDEBUG_HPP_

#include <iostream>

namespace Mplane {


class SharedPtrDebug
{
public:
    /** default constructor
     *
     */
    SharedPtrDebug(const void* sp) ;

    /** destructor
     *
     */
    virtual ~SharedPtrDebug() ;

    /**
     * Called by SharedPtr inside it's init() method
     * @param p		the pointer
     * @param count	current reference count
     */
    void init (const void* p, unsigned count) ;

    /**
     * Called by SharedPtr inside it's attach() method
     * @param p		the pointer
     * @param count	current reference count
     */
    void attach(const void* p, unsigned count) ;

    /**
     * Called by SharedPtr inside it's detach() method
     * @param p		the pointer
     * @param count	current reference count
     */
    void detach(const void* p, unsigned count) ;

    /**
     * Called by SharedPtr inside it's detach() method when the reference count reaches 0
     * @param p		the pointer
     */
    void dispose(const void* p) ;


    /**
     * Called by SharedPtr inside it's debugWatch() method to set the pointer to watch
     * @param p		the pointer
     */
    void watch(const void* p) ;

    /**
     * Called by SharedPtr inside it's debugNoWatch() method to clear the pointer watch
     * @param p		the pointer
     */
    void noWatch(const void* p) ;


private:
    static const void* mWatch ;

    volatile int mDummy ;
    const void* mSp ;
};

}
#endif /* SHAREDPTRDEBUG_HPP_ */
