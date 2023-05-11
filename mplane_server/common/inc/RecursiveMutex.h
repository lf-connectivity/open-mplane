#ifndef _RECURSIVEMUTEX_H_
#define _RECURSIVEMUTEX_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RecursiveMutex.h
 * \brief     Defines a recursive mutex class.
 *
 *
 * \details   Defines a recursive mutex class.
 *
 */

#include <pthread.h>

namespace Mplane {

/**
 * Simple POSIX thread recursive mutex wrapper class.
 * This class is to be used with the rest of the POSIX threads library.
 * RecursiveMutex objects can be constructed statically as well as dynamically.
 *
 * @brief A wrapper class for pthread recursive mutexes.
 */
class RecursiveMutex {
 private:
  /**
   * POSIX mutex store
   */
  pthread_mutex_t mutex;

  /**
   * @note: Standard copy constructors defined but not implemented as recursive
   * mutex cannot be copied.
   */
  explicit RecursiveMutex(const RecursiveMutex&);
  RecursiveMutex& operator=(const RecursiveMutex&);

 public:
  class Lock; // in scope Lock implementation

  /**
   * Initialise the standard POSIX mutex
   */
  RecursiveMutex();

  /**
   * Destry the standard POSIC mutex
   */
  ~RecursiveMutex();

  /**
   * Try and lock the mutex and take ownership, this will block the caller
   * until the lock is acquired
   */
  void lock();
  /**
   * Unlock the mutex to allow other threads to acquire the lock
   */
  void unlock();

  /**
   * Tries to lock the mutex and acquire ownership, but returns
   * immediately if it is already locked with value EBUSY.  It is not a
   * cancellation point.  It does not throw.  It is thread safe.
   * @return 0 if successful, otherwise EBUSY.
   * @note With this library implementation, the only pthread error
   * number which could be returned by this method is EBUSY.
   */
  int trylock();
};

/**
 * A Resource Allocation Is Initialisation (RAII) implementation of the
 * RecursiveMutex that automatically unlocks the thread when the Lock goes out
 * of scope.
 *
 * Here is a simple example:
 *
 * @code
 *
 * RecursiveMutex &threadLock;
 *
 * myUpdateFunction( SomeData &newValue )
 * {
 *     RecursiveMutex::Lock lock( threadLock );   // block until lock acheived
 *
 *     this-> value = newValue;  // thread safe change to class data;
 * }   // lock goes out of scope, destructor releases mutex
 * @endcode
 *
 */
class RecursiveMutex::Lock {
 private:
  RecursiveMutex& mRecursiveMutex;

  explicit Lock(const RecursiveMutex::Lock&);
  RecursiveMutex::Lock& operator=(const RecursiveMutex::Lock&);

 public:
  /**
   * Lock constructor
   * @param mutex
   */
  explicit Lock(RecursiveMutex& mutex);
  ~Lock();
};

} // namespace Mplane

#endif /* _RECURSIVEMUTEX_H_ */
