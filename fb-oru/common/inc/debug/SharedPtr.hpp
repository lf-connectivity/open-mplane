/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      SharedPtr.hpp
 * \brief     Shared pointer
 *
 *
 * \details   A reference counting pointer that uses a specified counter policy. Default is to use the non-thread safe
 * SharedCounter
 */

#ifndef SHAREDPTR_HPP_
#define SHAREDPTR_HPP_

/**
 * @brief Provides a subset of std::SharedPtr
 *
 * Manages the storage of a pointer, providing a limited garbage-collection facility, possibly sharing that
 * management with other objects.
 *
 * Objects of SharedPtr types have the ability of taking ownership of a pointer and share that ownership: once
 * they take ownership, the group of owners of a pointer become responsible for its deletion when the last one of
 * them releases that ownership.
 *
 * SharedPtr objects release ownership on the object they co-own as soon as they themselves are destroyed, or as
 * soon as their value changes by an assignment operation. Once all SharedPtr objects that share ownership over
 * a pointer have released this ownership, the managed object is deleted (normally by calling ::delete, but a
 * different deleter may be specified on construction).
 *
 * SharedPtr objects can only share ownership by copying their value: If two SharedPtr are constructed (or made)
 * from the same (non-SharedPtr) pointer, they will both be owning the pointer without sharing it, causing potential
 * access problems when one of them releases it (deleting its managed object) and leaving the other pointing to an
 * invalid location.
 *
 * Additionally, SharedPtr objects can share ownership over a pointer while at the same time pointing to another object.
 * This ability is known as aliasing (see constructors), and is commonly used to point to member objects while owning
 * the object they belong to. Because of this, a SharedPtr may relate to two pointers:
 *
 *     A stored pointer, which is the pointer it is said to point to, and the one it dereferences with operator*.
 *     An owned pointer (possibly shared), which is the pointer the ownership group is in charge of deleting at
 *     some point, and for which it counts as a use.
 *
 * Generally, the stored pointer and the owned pointer refer to the same object, but alias SharedPtr objects
 * (those constructed with the alias constructor and their copies) may refer to different objects.
 *
 * A SharedPtr that does not own any pointer is called an empty SharedPtr. A SharedPtr that points to no object is
 * called a null SharedPtr and shall not be dereferenced. Notice though that an empty SharedPtr is not necessarily
 * a null SharedPtr, and a null SharedPtr is not necessarily an empty SharedPtr.
 *
 * SharedPtr objects replicate a limited pointer functionality by providing access to the object they point to through
 * operators * and ->. For safety reasons, they do not support pointer arithmetics.
 *
 * The default SharedPtr<T> *is* thread safe. However, for cases where access is known to be within a single thread,
 * specifying the simpler non-thread-safe counter policy in the 2nd template parameter will optimise the pointer.
 *
 * A standard non-thread-safe counter is provided in Mplane::SharedCounter and can be used as:
 *
@code

// A non-thread-safe int pointer
SharedPtr<int, SharedCounter> iptr(new int(10)) ;

++(*iptr) ;

@endcode
 *
 * The default thread-safe counter is provided in Mplane::ThreadsafeCounter (which uses Mplane::Mutex) and can be used as:
 *
@code

// A thread-safe int pointer
SharedPtr<int, ThreadsafeCounter> iptr(new int(10)) ;

++(*iptr) ;

@endcode
 *
 *
 */
template<typename T, typename CountingPolicy = ThreadsafeCounter>
class SharedPtr
{
public:
	/**
	 * element_type	Template parameter (T), the type of the managed object
	 */
	typedef T element_type ;

    /** default constructor (no explicit initialization)
     *
     */
    SharedPtr() :
#ifdef DEBUG_SHARED_PTR
        mDebug(this),
#endif
    	ptr(NULL),
    	counter()
	{
        ptr = NULL;
    }

    /** a converting constructor (from a built-in pointer)
     *
     * @param p
     */
    explicit SharedPtr (T* p) :
#ifdef DEBUG_SHARED_PTR
        mDebug(this),
#endif
		ptr(NULL),
		counter()
    {
        init(p);         // init with ordinary pointer
    }

    /** copy constructor
     *
     * @param sp
     */
    SharedPtr (SharedPtr<T, CountingPolicy> const& sp) :
#ifdef DEBUG_SHARED_PTR
        mDebug(this),
#endif
    	ptr(NULL),
    	counter(sp.counter)
    {
        attach(sp.ptr);      // copy pointer and increment counter
    }

    /** copy constructor
     *
     * @param sp	Existing shared pointer
     * @param newp	Pointer to share
     */
    template <typename U>
    SharedPtr (SharedPtr<U, CountingPolicy> const& sp, T *newp) :
#ifdef DEBUG_SHARED_PTR
        mDebug(this),
#endif
    	ptr(NULL),
    	counter(sp.counter)
    {
        attach(newp);      // copy pointer and increment counter
    }

    template <typename U, typename CP> friend class SharedPtr ;


    /** destructor
     *
     */
    virtual ~SharedPtr()
    {
        detach();        // decrement counter
                         //  (and dispose counter if last owner)
    }

    /** assignment of a built-in pointer
     *
     * @param p
     * @return shared pointer
     */
    SharedPtr<T, CountingPolicy>&
    operator= (T* p)
    {
        // no counting pointer should point to *p yet:
        assert(p != ptr);
        detach();        // decrement counter
                               //  (and dispose counter if last owner)
        init(p);         // init with ordinary pointer
        return *this;
    }

    /** copy assignment (beware of self-assignment)
     *
     * @param sp
     * @return shared pointer
     */
    SharedPtr<T, CountingPolicy>&
    operator= (SharedPtr<T, CountingPolicy> const& sp)
    {
        if (ptr != sp.ptr)
        {
            detach();    // decrement counter
                         //  (and dispose counter if last owner)
            counter=sp.counter;  // assign policy

            attach(sp.ptr);  // copy pointer and increment counter
        }
        return *this;
    }

    /** Dereference object member
     *
     * @return pointer to T
     */
    T* operator-> () const
    {
        return ptr;
    }

    /** Dereference object
     *
     * @return reference to T
     */
    T& operator* () const
    {
        return *ptr;
    }

    /**
     * Returns the number of objects that share ownership over the same pointer as this object (including it)
     */
    const unsigned use_count(void) const
    {
    	return counter._get_count();
    }

    /**
     * Returns the stored pointer.
     *
     * The stored pointer points to the object the unique_ptr object dereferences to, which is generally the
     * same as its owned pointer.
     *
     * The stored pointer (i.e., the pointer returned by this function) may not be the owned pointer (i.e.,
     * the pointer deleted on object destruction) if the SharedPtr object is an alias (i.e., alias-constructed
     * objects and their copies).
     *
     * @return pointer
     */
    T* get() const
    {
    	return ptr ;
    }


    /**
     * Debug: watch this pointer
     *
     * When compiled with DEBUG_SHARED_PTR defined, tells the pointer debugger to print any changes to the
     * reference counter for this pointer.
     */
    void debugWatch()
    {
#ifdef DEBUG_SHARED_PTR
        mDebug.watch(ptr) ;
#endif
    }

    /**
     * Debug: stop watching this pointer
     *
     * When compiled with DEBUG_SHARED_PTR defined, tells the pointer debugger stop watching this pointer.
     */
    void debugNoWatch()
    {
#ifdef DEBUG_SHARED_PTR
        mDebug.noWatch(ptr) ;
#endif
    }

protected:
    // helpers:
    // - init with ordinary pointer (if any)
    void init (T* p)
    {
        if (p != NULL)
        {
            counter.init();
#ifdef DEBUG_SHARED_PTR
            mDebug.init(p, counter._get_count()) ;
#endif
        }
        ptr = p;
    }

    // - copy pointer and increment counter (if any)
    void attach(T* newp)
    {
        ptr = newp;
        if (newp != NULL)
        {
            counter.increment();
#ifdef DEBUG_SHARED_PTR
            mDebug.attach(ptr, counter._get_count()) ;
#endif
        }
    }

    // - decrement counter (and dispose counter if last owner)
    void detach()
    {
        if (ptr != NULL)
        {
            counter.decrement();
#ifdef DEBUG_SHARED_PTR
            mDebug.detach(ptr, counter._get_count()) ;
#endif

            if (counter.is_zero())
            {
                // dispose counter, if necessary:
                counter.dispose();

                // dispose of the object pointed to:
#ifdef DEBUG_SHARED_PTR
                mDebug.dispose(ptr) ;
#endif
                delete ptr;
            }
        }
    }

// @todo Fix the privileges for the copy constructor template <typename U> SharedPtr (SharedPtr<U, CountingPolicy> const& sp, T *newp)
protected:
    // Debug
#ifdef DEBUG_SHARED_PTR
    SharedPtrDebug mDebug ;
#endif

    T* ptr;      // the object referred to (or NULL if none)
    CountingPolicy counter ;

};

/**
 * Static cast of SharedPtr
 *
Returns a copy of sp of the proper type with its stored pointer casted statically from U* to T*.

If sp is not empty, the returned object shares ownership over sp's resources, increasing by one the use count.

If sp is empty, the returned object is an empty SharedPtr.

The function can only cast types for which the following expression would be valid:

@code
static_cast<T*>(sp.get())
@endcode

 * @param sp shared pointer
 * @return A SharedPtr object that owns the same pointer as sp (if any) and has a shared pointer
 * that points to the same object as sp with a potentially different type.
 */
template<typename T, typename U, typename _CP>
  inline SharedPtr<T, _CP>
  static_pointer_cast(const SharedPtr<U, _CP>& sp)
  { return SharedPtr<T, _CP>(sp, static_cast<T*>(sp.get())); }

/**
 * Const cast of SharedPtr
Returns a copy of sp of the proper type with its stored pointer const casted from U* to T*.

If sp is not empty, the returned object shares ownership over sp's resources, increasing by one the use count.

If sp is empty, the returned object is an empty SharedPtr.

The function can only cast types for which the following expression would be valid:

@code
const_cast<T*>(sp.get())
@endcode

 * @param sp shared pointer
 * @return A SharedPtr object that owns the same pointer as sp (if any) and has a shared pointer
 * that points to the same object as sp with a potentially different type.
 */
template<typename T, typename U, typename _CP>
  inline SharedPtr<T, _CP>
  const_pointer_cast(const SharedPtr<U, _CP>& sp)
  { return SharedPtr<T, _CP>(sp, const_cast<T*>(sp.get())); }

/**
 * Dynamic cast of SharedPtr
Returns a copy of sp of the proper type with its stored pointer casted dynamically from U* to T*.

If sp is not empty, and such a cast would not return a null pointer, the returned object shares ownership over sp's resources, increasing by one the use count.

Otherwise, the returned object is an empty SharedPtr.

The function can only cast types for which the following expression would be valid:

@code
dynamic_cast<T*>(sp.get())
@endcode

 * @param sp shared pointer
 * @return A SharedPtr object that owns the same pointer as sp (if any) and has a shared pointer
 * that points to the same object as sp with a potentially different type.
 */
template<typename T, typename U, typename _CP>
  inline SharedPtr<T, _CP>
  dynamic_pointer_cast(const SharedPtr<U, _CP>& sp)
  { return SharedPtr<T, _CP>(sp, dynamic_cast<T*>(sp.get())); }


#endif /* SHAREDPTR_HPP_ */
