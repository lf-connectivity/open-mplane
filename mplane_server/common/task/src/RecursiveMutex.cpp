/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      RecursiveMake.cpp
 * \brief     Implementation of simple recursive wrapper class
 *
 *
 * \details   Implementation of simple recursive wrapper class
 *
 */

#ifndef _REENTRANT
#define _REENTRANT
#endif
#define _POSIX_SOURCE

#include "RecursiveMutex.h"

Mplane::RecursiveMutex::RecursiveMutex() {
  pthread_mutexattr_t Attr;
  pthread_mutexattr_init(&Attr);
  pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&mutex, &Attr);
}

Mplane::RecursiveMutex::~RecursiveMutex() { pthread_mutex_destroy(&mutex); }

void
Mplane::RecursiveMutex::lock() {
  pthread_mutex_lock(&mutex);
}

void
Mplane::RecursiveMutex::unlock() {
  pthread_mutex_unlock(&mutex);
}

int
Mplane::RecursiveMutex::trylock() {
  return pthread_mutex_trylock(&mutex);
}

Mplane::RecursiveMutex::Lock::Lock(RecursiveMutex& recursivemutex)
    : mRecursiveMutex(recursivemutex) {
  mRecursiveMutex.lock();
}

Mplane::RecursiveMutex::Lock::~Lock() { mRecursiveMutex.unlock(); }
