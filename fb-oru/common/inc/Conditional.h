#ifndef _MPLANE_CONDITIONAL_H_
#define _MPLANE_CONDITIONAL_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Conditional.h
 * \brief     A C++ wrapper class for POSIX conditional variable, with supporting mutex
 *
 *
 * \details   A C++ wrapper class for POSIX conditional variable, with supporting mutex
 *
 */

#include <pthread.h>

namespace Mplane
{

/**
 * This class is a wrapper class for the POSIX conditional variable. It provides
 * a mutex that is used to lock access to the conditional data, with various wait
 * and signalling methods that act on the conditional variable.
 *
 * Here is a simple example of how it is used:
 *
 * @code
 * class Queue
 * {
 *     Conditional mCond;
 *     std::queue<Data> queue;
 *
 *     void push(Data const& data)
 *     {
 *         Conditional::Lock lock( &mCond );  // acquire mutex
 *         queue.push(data);                  // put data on queue
 *         mCond.signal();                    // signal conditional wait.
 *     }                                      // release mutex on lock out of scope
 *
 *     void wait_and_pop(Data& popped_value)
 *     {
 *         Conditional::Lock lock( mCond );   // acquire mutex
 *         while( queue.empty() )
 *         {
 *            mCond.wait();                   // release mutex and wait for conditional
 *         }
 *         popped_value=queue.front();
 *         queue.pop();
 *    }                                       // release mutex on lock out of scope
 * }
 * @endcode
 *
 *
 * @brief A wrapper class for pthread condition variables.
 */

class Conditional
{

private:
    /**
     * Our POSIX conditional variable
     */
    pthread_cond_t conditional;

    /**
     * Flag set on signal
     */
    bool condFlag ;

    /**
     * A reference to the mutex used in conjunction with this conditional
     * variable instance.
     */
    pthread_mutex_t mutex;

    /**
     * @note: Standard copy constructors defined but not implemented as conditionals
     * cannot be copied.
     */
    explicit Conditional(const Conditional&);
    Conditional& operator=(const Conditional&);

public:

    /**
     * Member Lock class used as an RAII lock guard for our mutex.
     */
    class Lock;

    /**
     * Method used to acquire and lock the conditional's supporting mutex.
     * @note: Used Conditional::Lock where possible
     */
    void lock(void);

    /**
     * Method used used to unlock the conditional's supporting mutex.
     * @note: Used Conditional::Lock where possible
     */
    void unlock(void);

    /**
     * Unblock at least one thread waiting on this condition variable.
     * Can be called by any thread. It is not a cancellation point.  Does
     * not throw.
     * @return 0 if successful, otherwise the pthread error number.
     */
    int signal();

    /**
     * Unblocks all threads waiting on this condition variable, which
     * acquire the mutex in an order determined by the scheduling policy.
     * Can be called by any thread. It is not a cancellation point.  Does
     * not throw.
     * @return 0 if successful, otherwise the pthread error number.
     */
    int broadcast();

    /**
     * Wait (block) indefinitely until signalled.
     */
    void wait(void);

    /**
      * Conditional wait for signal on millisecond timeout.
      * @param timeout in milliseconds.
      * @return true if signalled, false if timer expired.
      */
    bool wait(unsigned int timeout);

     /**
      * Conditional wait for signal on timespec timeout.
      * @param timeout as a high resolution timespec.
      * @return true if signalled, false if timer expired.
      */
    bool wait(struct timespec *timeout);

    /**
     * Clears out the conditional ensuring the flag is not true (used to ensure any previous signal to this conditional
     * is ignored before starting to wait for a new signal)
     */
    void clear() ;

    /**
     * Initialises the pthread condition variable.
     */
    Conditional();

    /**
     * Destroys the pthread condition variable. It is not a cancellation
     * point.  The destructor does not throw.  Destroying a condition
     * variable on which another thread is currently blocked results in
     * undefined behavior.
     */
    ~Conditional(void);

    /**
     * Used internally to set a millisecond timeout into a time spec
     * structure.
     * @param ts
     * @param millisec
     */
    static void set(struct timespec *ts, unsigned int millisec);

};

/**
 * A Resource Allocation Is Initialisation (RAII) implementation of the Mutex
 * that automatically unlocks the thread when the Lock goes out of scope.
 *
 * Here is a simple example:
 *
 * @code
 *
 * Mutex &threadLock;
 *
 * myUpdateFunction( SomeData &newValue )
 * {
 *     Lock lock( threadLock );   // block until lock acheived
 *
 *     this-> value = newValue;  // thread safe change to class data;
 * }   // lock goes out of scope, destructor releases mutex
 * @endcode
 *
 */
class Conditional::Lock
{
private:
    Conditional& mCond;

    explicit Lock(const Conditional::Lock&);
    Conditional::Lock& operator=(const Conditional::Lock&);
public:

    /**
     * Lock constructor
     * @param conditional reference to a Conditional object.
     */
    explicit Lock(Conditional &conditional);
    ~Lock();
};

}

#endif /* _CONDITIONAL_H_ */
