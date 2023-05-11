/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Conditional.cpp
 * \brief     Implementation of Conditional wrapper for POSIX threads conditional
 *
 *
 * \details   Implementation of Conditional wrapper for POSIX threads conditional
 *
 */

#ifndef _REENTRANT
#define _REENTRANT
#endif
#define _POSIX_SOURCE

#include "Conditional.h"
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>

#include <iostream>

using namespace std;

Mplane::Conditional::Conditional() :
	condFlag(false)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&conditional, NULL);
}

Mplane::Conditional::~Conditional(void)
{
    pthread_cond_destroy(&conditional);
}


void Mplane::Conditional::lock(void)
{
    pthread_mutex_lock(&mutex);;
}

void Mplane::Conditional::unlock(void)
{
    pthread_mutex_unlock(&mutex);
}

int Mplane::Conditional::signal()
{
	// mutex expected to be locked by caller
	condFlag = true ;
    return pthread_cond_signal(&conditional);
}

int Mplane::Conditional::broadcast()
{
	// mutex expected to be locked by caller
	condFlag = true ;
    return pthread_cond_broadcast(&conditional);
}

void Mplane::Conditional::wait(void)
{
	lock() ;
	while (!condFlag)
	{
		pthread_cond_wait(&conditional, &mutex);
	}

	// Ensure flag is cleared for next time
	condFlag = false ;
	unlock() ;
}

bool Mplane::Conditional::wait(unsigned int timeout)
{
    struct timespec ts;
    set(&ts, timeout);
    return wait(&ts);
}

bool Mplane::Conditional::wait(struct timespec* timeout)
{
    assert(timeout != NULL);

    int stat = 0 ;

	lock() ;
	while (!condFlag && (stat != ETIMEDOUT))
	{
		stat = pthread_cond_timedwait(&conditional, &mutex, timeout) ;
	}

	// Ensure flag is cleared for next time
	condFlag = false ;
	unlock() ;

	if(stat == ETIMEDOUT)
        return false;

    return true;
}

void Mplane::Conditional::set(struct timespec *ts, unsigned int msec)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ts->tv_sec = tv.tv_sec;
    ts->tv_nsec = tv.tv_usec * 1000l;
    ts->tv_sec += msec / 1000;
    ts->tv_nsec += (msec % 1000) * 1000000l;
    while(ts->tv_nsec >= 1000000000l) {
        ++ts->tv_sec;
        ts->tv_nsec -= 1000000000l;
    }
}

Mplane::Conditional::Lock::Lock(Conditional &conditional):mCond( conditional )
{
    mCond.lock();
}

Mplane::Conditional::Lock::~Lock()
{
    mCond.unlock();
}

void Mplane::Conditional::clear()
{
	lock() ;
	// Ensure flag is cleared for next time
	condFlag = false ;
	unlock() ;
}
