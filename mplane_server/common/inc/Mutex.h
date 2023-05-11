#ifndef _MUTEX_H_
#define _MUTEX_H_

/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mutex.h
 * \brief     A C++ wrapper class for a basic POSIX thread mutex
 *
 *
 * \details   A C++ wrapper class for a basic POSIX thread mutex
 *
 */

#include <pthread.h>

namespace Mplane {

/**
 * Simple POSIX thread Mutex wrapper class.
 * This class is to be used with the rest of the POSIX threads library.
 * Mutex objects can be constructed statically as well as dynamically.
 *
 * @brief A wrapper class for pthread mutexes.
 */
class Mutex {
 private:
  /**
   * POSIX mutex store
   */
  pthread_mutex_t mutex;
  /**
   * Used to report the mutex state
   */
  bool lockState;

  /**
   * @note: Standard copy constructors defined but not implemented as mutex
   * cannot be copied.
   */
  Mutex(const Mutex&);
  Mutex& operator=(const Mutex&);

 public:
  friend class Conditional;

  class Lock;

  /**
   * Initialise the standard POSIX mutex
   */
  Mutex();

  /**
   * Destroy the standard POSIX mutex
   */
  ~Mutex();

  /**
   * Lock the mutex, this will block the caller until the lock is acquired
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

  /**
   * Method used to return the lock status.
   * @return
   */
  bool isLocked();
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
class Mutex::Lock {
 private:
  Mutex& mMutex;

  explicit Lock(const Mutex::Lock&);
  Mutex::Lock& operator=(const Mutex::Lock&);

 public:
  friend class Conditional;

  /**
   * Lock constructor
   * @param mutex
   */
  explicit Lock(Mutex& mutex);
  ~Lock();
};

} // namespace Mplane

#endif /* _MUTEX_H_ */
