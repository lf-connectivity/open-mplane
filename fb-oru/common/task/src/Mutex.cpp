/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Mutex.cpp
 * \brief     Implementation od C++ wrapper class for a basic POSIX thread mutex
 *
 *
 * \details   Implementation od C++ wrapper class for a basic POSIX thread mutex
 *
 */

#ifndef _REENTRANT
#define _REENTRANT
#endif
#define _POSIX_SOURCE

#include "Mutex.h"

Mplane::Mutex::Mutex(): lockState( false )
{
    pthread_mutex_init(&mutex, 0);
}

Mplane::Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex);
}


void Mplane::Mutex::lock()
{
    pthread_mutex_lock(&mutex);
    lockState = true;
}

void Mplane::Mutex::unlock()
{
    lockState = false;
    pthread_mutex_unlock(&mutex);
}

int Mplane::Mutex::trylock()
{
    return pthread_mutex_trylock(&mutex);
}


bool Mplane::Mutex::isLocked()
{
    return lockState;
}

Mplane::Mutex::Lock::Lock(Mutex &mutex):mMutex( mutex )
{
    mMutex.lock();
}

Mplane::Mutex::Lock::~Lock()
{
    mMutex.unlock();
}
